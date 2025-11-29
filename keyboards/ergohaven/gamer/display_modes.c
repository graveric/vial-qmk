#include "display.h"
#include "qp.h"
#include "ergohaven_ruen.h"
#include "hid.h"
#include "ergohaven.h"
#include "ergohaven_symbols.h"
#include "ergohaven_display.h"
#include "lvgl_helpers.h"

extern const eh_screen_t eh_screen_layout;

/* Screen splash */

static lv_obj_t *screen_splash2;

LV_IMG_DECLARE(anim_on_00);
LV_IMG_DECLARE(anim_on_01);
LV_IMG_DECLARE(anim_on_02);
LV_IMG_DECLARE(anim_on_03);
LV_IMG_DECLARE(anim_on_04);
LV_IMG_DECLARE(anim_on_05);
LV_IMG_DECLARE(anim_on_06);
LV_IMG_DECLARE(anim_on_07);
LV_IMG_DECLARE(anim_on_08);
LV_IMG_DECLARE(anim_on_09);
LV_IMG_DECLARE(anim_on_10);

static const lv_img_dsc_t * anim_on[] = {
    &anim_on_00,
    &anim_on_01,
    &anim_on_02,
    &anim_on_03,
    &anim_on_04,
    &anim_on_05,
    &anim_on_06,
    &anim_on_07,
    &anim_on_08,
    &anim_on_09,
    &anim_on_10,
    &anim_on_10,
};

void splash2_screen_init(void) {
    screen_splash2 = lv_obj_create(NULL);
    lv_obj_add_style(screen_splash2, &style_screen, 0);
    use_flex_column(screen_splash2);

    lv_obj_t * anim = lv_animimg_create(screen_splash2);

    lv_animimg_set_src(anim, (lv_img_dsc_t**)anim_on, sizeof(anim_on)/sizeof(anim_on[0]));
    lv_animimg_set_duration(anim, 1500);
    lv_animimg_set_repeat_count(anim, 1);

    lv_obj_align(anim, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_top(anim, 0, 0);
    lv_obj_set_style_pad_bottom(anim, 0, 0);
    lv_animimg_start(anim);
}

void splash2_screen_load(void) {
    lv_scr_load(screen_splash2);
}

void splash2_screen_housekeep(void) {
    lv_scr_load(screen_splash2);
}

const eh_screen_t eh_screen_splash2 = {
    .init      = splash2_screen_init,
    .load      = splash2_screen_load,
    .housekeep = splash2_screen_housekeep,
};

static uint32_t screen_timer = 0;

typedef enum {
    SCREEN_OFF = -1,
    SCREEN_SPLASH,
    SCREEN_LAYOUT,
    SCREEN_VOLUME,
    SCREEN_HOME,
} screen_t;

static screen_t screen_state        = SCREEN_OFF;
static screen_t change_screen_state = SCREEN_OFF;

eh_screen_t current_screen;

void display_init_screens_kb(void) {
    eh_screen_splash2.init();
    eh_screen_layout.init();
    eh_screen_home.init();
    eh_screen_volume.init();
    current_screen      = eh_screen_splash2;
    change_screen_state = SCREEN_SPLASH;
    screen_state        = SCREEN_SPLASH;
    current_screen.load();
    display_turn_on();
    screen_timer = timer_read32();
}

void display_housekeeping_task(void) {
    if (!is_display_enabled()) return;

    static uint8_t prev_layer = 0;
    uint8_t        layer      = get_current_layer();
    if (layer != prev_layer) {
        prev_layer          = layer;
        change_screen_state = SCREEN_LAYOUT;
        return;
    }

    hid_data_t *hid_data   = get_hid_data();
    bool        hid_active = is_hid_active();
    if (hid_active && hid_data->hid_changed) {
        if (hid_data->volume_changed) {
            change_screen_state = SCREEN_VOLUME;
            screen_timer        = timer_read32();
        }
        if (hid_data->media_artist_changed) {
            change_screen_state = SCREEN_HOME;
        }
        if (hid_data->media_title_changed) {
            change_screen_state = SCREEN_HOME;
        }
    }

    if (screen_state == change_screen_state) {
        uint32_t screen_elapsed   = timer_elapsed32(screen_timer);
        uint32_t activity_elapsed = last_input_activity_elapsed();

        switch (screen_state) {
            case SCREEN_SPLASH:
                if (screen_elapsed > EH_DISPLAY_TIMEOUT_SPLASH_SCREEN) {
                    change_screen_state = SCREEN_LAYOUT;
                }
                break;

            case SCREEN_LAYOUT:
                if (hid_active && activity_elapsed > EH_DISPLAY_TIMEOUT_ACTIVITY) {
                    change_screen_state = SCREEN_HOME;
                } else if (activity_elapsed > EH_TIMEOUT) {
                    change_screen_state = SCREEN_OFF;
                }
                break;

            case SCREEN_HOME:
                if (!hid_active) {
                    change_screen_state = SCREEN_LAYOUT;
                } else if (activity_elapsed > EH_TIMEOUT && screen_elapsed > EH_DISPLAY_TIMEOUT_ACTIVITY) {
                    change_screen_state = SCREEN_OFF;
                }
                break;

            case SCREEN_VOLUME:
                if (screen_elapsed > EH_DISPLAY_TIMEOUT_VOLUME_SCREEN) {
                    change_screen_state = SCREEN_HOME;
                }
                break;

            case SCREEN_OFF:
                if (activity_elapsed < EH_TIMEOUT) {
                    change_screen_state = SCREEN_LAYOUT;
                }
                break;
        }
    }

    if (change_screen_state != screen_state) {
        screen_timer = timer_read32();
        screen_state = change_screen_state;
        switch (screen_state) {
            case SCREEN_SPLASH:
                current_screen = eh_screen_splash2;
                display_turn_on();
                break;
            case SCREEN_HOME:
                current_screen = eh_screen_home;
                display_turn_on();
                break;
            case SCREEN_LAYOUT:
                current_screen = eh_screen_layout;
                display_turn_on();
                break;
            case SCREEN_VOLUME:
                current_screen = eh_screen_volume;
                display_turn_on();
                break;
            case SCREEN_OFF:
                display_turn_off();
                break;
        }
        current_screen.load();
        return;
    }

    current_screen.housekeep();
}
