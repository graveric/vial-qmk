#include QMK_KEYBOARD_H
#include "ergohaven.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    QK_BOOT,  KC_1,    KC_2,    KC_3,     KC_4,
    KC_ESC,   KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,
    KC_TAB,   KC_A,    KC_S,    KC_D,     KC_F,     KC_G,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,  KC_LBRC,
    KC_LGUI, KC_LALT,  KC_LCTL, LOWER,    KC_SPC,   KC_SPC
  ),
};
