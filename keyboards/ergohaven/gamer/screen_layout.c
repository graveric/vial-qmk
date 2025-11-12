#include "ergohaven_display.h"
#include "ergohaven_keycode_str.h"
#include "lvgl_helpers.h"
#include "ergohaven.h"
#include "ergohaven_settings.h"

LV_FONT_DECLARE(ergohaven_symbols_18);
LV_FONT_DECLARE(ergohaven_symbols_28);

__attribute__((weak)) void kb_settings_init_layer_labels(void) {
    static const char *PROGMEM default_layer_names[] = {
        "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN",
    };
    for (int i = 0; i < DYNAMIC_KEYMAP_LAYER_COUNT; ++i) {
        eeconfig_update_kb_datablock(default_layer_names[i], 4 + i * LAYER_LABEL_SIZE, LAYER_LABEL_SIZE);
    }
}

uint16_t get_keycode(int layer, int row, int col) {
    uint16_t keycode = dynamic_keymap_get_keycode(layer, row, col);
    if (keycode == KC_TRANSPARENT) keycode = dynamic_keymap_get_keycode(0, row, col);
    return keycode;
}

uint16_t get_encoder_keycode(int layer, int encoder, bool clockwise) {
    uint16_t keycode = dynamic_keymap_get_encoder(layer, encoder, clockwise);
    if (keycode == KC_TRANSPARENT) keycode = dynamic_keymap_get_encoder(0, encoder, clockwise);
    return keycode;
}

/* Screen layout */

static lv_obj_t *screen_layout;

static lv_obj_t *key_labels[29];
static lv_obj_t *label_layer_small;

void screen_layout_init(void) {
    screen_layout = lv_obj_create(NULL);
    lv_obj_add_style(screen_layout, &style_screen, 0);
    use_flex_column(screen_layout);
    lv_obj_set_scrollbar_mode(screen_layout, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *cont = lv_obj_create(screen_layout);
    lv_obj_set_size(cont, 240, 230);
    // lv_obj_center(cont);
    lv_obj_set_style_pad_top(cont, 5, 0);
    lv_obj_set_style_pad_bottom(cont, 5, 0);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    int32_t v = 0;
    lv_obj_set_style_pad_row(cont, v, 0);
    lv_obj_set_style_pad_column(cont, v, 0);
    lv_obj_add_style(cont, &style_container, 0);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    for (uint32_t i = 0; i < 29; i++) {
        if (i == 0) {
            lv_obj_t *obj = lv_obj_create(cont);
            lv_obj_set_size(obj, 20, 45);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_add_style(obj, &style_screen, 0);
            lv_obj_set_style_border_opa(obj, 0, 0);
        }
        lv_obj_t *obj = lv_obj_create(cont);
        lv_obj_set_size(obj, 40, 45);
        lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_style(obj, &style_screen, 0);
        lv_obj_set_style_border_width(obj, 1, 0);

        key_labels[i] = lv_label_create(obj);
        lv_obj_center(key_labels[i]);
        lv_obj_set_style_text_font(key_labels[i], &ergohaven_symbols_28, LV_PART_MAIN);
        lv_obj_set_style_text_align(key_labels[i], LV_TEXT_ALIGN_CENTER, 0);
        lv_label_set_text(key_labels[i], "");
    }

    label_layer_small = lv_label_create(screen_layout);
    lv_label_set_text(label_layer_small, "");
    lv_obj_set_style_pad_top(label_layer_small, 0, 0);
    lv_obj_set_style_pad_bottom(label_layer_small, 0, 0);
    // lv_obj_set_style_text_color(label_layer_small, accent_color_blue, 0);
    lv_obj_set_style_text_font(label_layer_small, &ergohaven_symbols_28, LV_PART_MAIN);
}

static uint8_t prev_layer         = 255;
static int     update_label_index = 0;

void screen_layout_load(void) {
    prev_layer         = 255;
    update_label_index = 0;
    lv_scr_load(screen_layout);
}

size_t utf8len(const char *s) {
    size_t len = 0;
    for (; *s; ++s)
        if ((*s & 0xC0) != 0x80) ++len;
    return len;
}

void screen_layout_housekeep(void) {
    uint8_t layer = get_current_layer();
    if (layer != prev_layer) {
        prev_layer = layer;
        lv_label_set_text(label_layer_small, get_layer_label(layer));
        update_label_index = 0;
        return;
    }

    if (update_label_index >= 29) return;

    const uint8_t TABLE[29][2] = {
        {0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0},         //
        {0, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}, //
        {1, 5}, {2, 4}, {2, 3}, {2, 2}, {2, 1}, {2, 0}, //
        {2, 5}, {3, 4}, {3, 3}, {3, 2}, {3, 1}, {3, 0}, //
        {3, 5}, {4, 5}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, //
    };

    uint16_t keycode = KC_TRANSPARENT;
    keycode          = get_keycode(layer, TABLE[update_label_index][0], TABLE[update_label_index][1]);
    const char *text = keycode_to_str(keycode);
    int         len  = utf8len(text);
    if (len <= 2)
        lv_obj_set_style_text_font(key_labels[update_label_index], &ergohaven_symbols_28, LV_PART_MAIN);
    else
        lv_obj_set_style_text_font(key_labels[update_label_index], &ergohaven_symbols_18, LV_PART_MAIN);

    lv_label_set_text(key_labels[update_label_index], text);
    update_label_index += 1;
}

const eh_screen_t eh_screen_layout = {
    .init      = screen_layout_init,
    .load      = screen_layout_load,
    .housekeep = screen_layout_housekeep,
};
