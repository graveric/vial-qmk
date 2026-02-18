#include "src/display/eh_display.h"
#include <lvgl.h>

#include "ergohaven.h"
#include "src/display/lvgl_helpers.h"

static lv_obj_t *screen_splash;

LV_IMG_DECLARE(vk_on);

void splash_screen_init(void) {
    screen_splash = lv_obj_create(NULL);
    lv_obj_add_style(screen_splash, &style_screen, 0);
    use_flex_column(screen_splash);

    lv_obj_t *img = lv_img_create(screen_splash);
    lv_img_set_src(img, &vk_on);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_top(img, 10, 0);
    lv_obj_set_style_pad_bottom(img, 10, 0);
}

void splash_screen_load(void) {
    lv_scr_load(screen_splash);
}

void splash_screen_housekeep(void) {
}

const eh_screen_t eh_screen_splash = {
    .init      = splash_screen_init,
    .load      = splash_screen_load,
    .housekeep = splash_screen_housekeep,
};
