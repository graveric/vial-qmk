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

LV_IMG_DECLARE(anim_01);
LV_IMG_DECLARE(anim_02);
LV_IMG_DECLARE(anim_03);
LV_IMG_DECLARE(anim_04);
LV_IMG_DECLARE(anim_05);
LV_IMG_DECLARE(anim_06);
LV_IMG_DECLARE(anim_07);
LV_IMG_DECLARE(anim_08);
LV_IMG_DECLARE(anim_09);
LV_IMG_DECLARE(anim_10);
LV_IMG_DECLARE(anim_11);
LV_IMG_DECLARE(anim_12);
LV_IMG_DECLARE(anim_13);
LV_IMG_DECLARE(anim_14);
LV_IMG_DECLARE(anim_15);
LV_IMG_DECLARE(anim_16);
LV_IMG_DECLARE(anim_17);
LV_IMG_DECLARE(anim_18);

static const lv_img_dsc_t *anim_on[] = {
    &anim_01, &anim_02, &anim_03, &anim_04, &anim_05, &anim_06, &anim_07, &anim_08, &anim_09, &anim_10, //
    &anim_11, &anim_12, &anim_13, &anim_14, &anim_15, &anim_16, &anim_17, &anim_18                      //
};

static lv_obj_t *anim_start;
static uint32_t  anim_timer = 0;
static int32_t   anim_index = 0;

void splash2_screen_init(void) {
    screen_splash2 = lv_obj_create(NULL);
    lv_obj_add_style(screen_splash2, &style_screen, 0);
    use_flex_column(screen_splash2);

    anim_start = lv_img_create(screen_splash2);
    lv_img_set_src(anim_start, anim_on[0]);

    lv_obj_align(anim_start, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_top(anim_start, 0, 0);
    lv_obj_set_style_pad_bottom(anim_start, 0, 0);
}

void splash2_screen_load(void) {
    lv_scr_load(screen_splash2);
    anim_timer = 0;
    anim_index = 0;
}

void splash2_screen_housekeep(void) {
    bool    loop  = anim_index >= 11;
    int32_t delay = loop ? 200 : 100;

    if (timer_elapsed32(anim_timer) > delay) {
        dprintf("set src %ld\n", anim_index);
        lv_img_set_src(anim_start, anim_on[anim_index]);

        if (!loop)
            anim_index += 1;
        else
            anim_index = (anim_index - 11 + 1) % 7 + 11;
        anim_timer = timer_read32();
    }
}

const eh_screen_t eh_screen_splash2 = {
    .init      = splash2_screen_init,
    .load      = splash2_screen_load,
    .housekeep = splash2_screen_housekeep,
};

/* Screen idle */

static lv_obj_t *screen_idle;
lv_obj_t        *anim_idle;

static const lv_img_dsc_t *anim_idle_array[] = {
    &anim_13, &anim_14, &anim_15, &anim_16, &anim_17, &anim_12,
};

void idle_screen_init(void) {
    screen_idle = lv_obj_create(NULL);
    lv_obj_add_style(screen_idle, &style_screen, 0);
    use_flex_column(screen_idle);

    anim_idle = lv_animimg_create(screen_idle);

    lv_animimg_set_src(anim_idle, (lv_img_dsc_t **)anim_idle_array, sizeof(anim_idle_array) / sizeof(anim_idle_array[0]));
    lv_animimg_set_duration(anim_idle, 2000);
    lv_animimg_set_repeat_count(anim_idle, LV_ANIM_REPEAT_INFINITE);

    lv_obj_align(anim_idle, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_top(anim_idle, 0, 0);
    lv_obj_set_style_pad_bottom(anim_idle, 0, 0);
}

void idle_screen_load(void) {
    lv_scr_load(screen_idle);
    lv_animimg_start(anim_idle);
}

void idle_screen_housekeep(void) {}

const eh_screen_t eh_screen_idle = {
    .init      = idle_screen_init,
    .load      = idle_screen_load,
    .housekeep = idle_screen_housekeep,
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
    eh_screen_idle.init();
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
                if (activity_elapsed < 100) {
                    change_screen_state = SCREEN_LAYOUT;
                } else if (activity_elapsed > EH_TIMEOUT) {
                    change_screen_state = SCREEN_OFF;
                }
                break;

            case SCREEN_LAYOUT:
                if (hid_active && activity_elapsed > EH_DISPLAY_TIMEOUT_ACTIVITY) {
                    change_screen_state = SCREEN_HOME;
                } else if (activity_elapsed > EH_TIMEOUT) {
                    change_screen_state = SCREEN_OFF;
                } else if (activity_elapsed > 10000) {
                    change_screen_state = SCREEN_SPLASH;
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
