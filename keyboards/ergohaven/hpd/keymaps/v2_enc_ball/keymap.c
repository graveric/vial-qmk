#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "src/eh_pointing.h"
#include "src/eh_ruen.h"

#define _RUS 1
#define _NAVI 2
#define _SYM1 3
#define _SYM2 4
#define _UNI 5
#define _SHCUT 6
#define _KHRN 7
#define _FDIN 8
#define _ADJST 9
#define _MICE 10

enum hpd_keycodes {
  GR_DOT = SAFE_RANGE,
  GR_COMMA, 
  GR_MINUS, 
  GR_SLASH, 
  GR_INCH, 
  GR_UNDER, //0x7e45
  GR_ALT1, 
  GR_ALT2, 
  GR_SBR, //0x7e48
  GR_CBR,
  GR_PR,  //0x7e4a
  SW_TAB, //0x7e4b
  SW_WIN //0x7e4c
};

bool sw_win_active = false;
bool sw_tab_active = false; 

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
KC_ESC,   KC_J,     KC_Y,     KC_A,     KC_U,     GR_MINUS,                                             KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                             KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                             KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                             KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                    KC_PGDN,  KC_PGUP,  KC_LCTL,  LOWER,    KC_LALT,  KC_SPACE,           KC_ENT,   KC_RGUI,  RAISE,    KC_RCTL,  KC_LBRC,  KC_RBRC,
                                                                      KC_MUTE,            KC_MUTE
    ),

    [_LOWER] = LAYOUT(
KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                                            KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
KC_VOLU,  KC_MNXT,  KC_HOME,  KC_UP,    KC_END,   KC_INS,                                           _______,  KC_7,     KC_8,     KC_9,     _______,  _______,
KC_MUTE,  KC_MPLY,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_ENT,                                           _______,  KC_4,     KC_5,     KC_6,     _______,  _______,
KC_VOLD,  KC_MPRV,  PREVWRD,  _______,  NEXTWRD,  KC_DEL,                                           KC_PSCR,  KC_1,     KC_2,     KC_3,     _______,  _______,
                    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  KC_0,     _______,
                                                                      _______,            _______
    ),

    [_RAISE] = LAYOUT(
_______,  _______,  KC_AT,    KC_DLR,   KC_HASH,  _______,                                          _______,  _______,  KC_CIRC,  _______,  _______,  _______,
_______,  _______,  KC_LT,    KC_EQL,   KC_GT,    KC_GRV,                                           _______,  KC_LBRC,  KC_UNDS,  KC_RBRC,  _______,  _______,
_______,  KC_BSLS,  KC_LPRN,  KC_MINS,  KC_RPRN,  KC_PLUS,                                          KC_PERC,  KC_LCBR,  KC_SCLN,  KC_RCBR,  KC_EXLM,  _______,
_______,  _______,  KC_ASTR,  KC_COLN,  KC_SLSH,  _______,                                          _______,  KC_PIPE,  KC_TILD,  KC_AMPR,  _______,  _______,
                    _______,  _______,  _______,  _______,  _______,  _______,          _______,    _______,  _______,  _______,  _______,  _______,
                                                                      _______,          _______
    ),

    [_ADJUST] = LAYOUT(
_______,  _______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,  _______,
_______,  _______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,  _______,
_______,  _______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,  _______,
_______,  _______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,  _______,
                    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
                                                                      _______,            _______
    ),

    [_FOUR] = LAYOUT(
_______,  _______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,  _______,
_______,  _______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,  _______,
_______,  EH_SCR,   KC_BTN3,  KC_BTN2,  KC_BTN1,  EH_SNP,                                           EH_SNP,   KC_BTN1,  KC_BTN2,  KC_BTN3,  EH_SCR,   _______,
_______,  _______,  _______,  _______,  _______,  EH_TXT,                                           EH_TXT,   _______,  _______,  _______,  _______,  _______,
                    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
                                                                      _______,            _______
    ),
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, //
    [1] = {ENCODER_CCW_CW(_______, _______)}, //
    [2] = {ENCODER_CCW_CW(_______, _______)}, //
    [3] = {ENCODER_CCW_CW(_______, _______)}, //
    [4] = {ENCODER_CCW_CW(_______, _______)}, //
};
#endif

// Implements cmd-tab like behaviour on a single key. On first tap of trigger
// cmdish is held and tabish is tapped -- cmdish then remains held until some
// other key is hit or released. For example:
//
//     trigger, trigger, a -> cmd down, tab, tab, cmd up, a
//     nav down, trigger, nav up -> nav down, cmd down, tab, cmd up, nav up
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t reverse_key,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active
        && keycode != reverse_key
        && keycode != KC_LEFT
        && keycode != KC_RIGHT
    ) {
        unregister_code(cmdish);
        *active = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN, KC_LSFT,
        keycode, record
    );
    update_swapper(
        &sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, KC_LSFT,
        keycode, record
    );

    switch (keycode) {
        case GR_INCH:
            if (record->event.pressed) {
                bool ruon = (get_cur_lang() == LANG_RU);
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом '
                    if (ruon) {
                        tap_code16(RSA(KC_2));
                    } else {
                        send_string("'");  
                    }
                } else {
                    if (ruon) {
                        tap_code16(RALT(KC_2));
                    } else {
                        send_string("\"");
                    }
                }
                set_mods(cur_mods_c);            
            }
            return false;
        case GR_UNDER:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    // ->
                    tap_code(KC_MINUS);
                    tap_code16(RALT(LSFT(KC_L)));

                } else {
                    send_string("_");
                }
                set_mods(cur_mods_c);            
            }
            return false;                    
        case GR_MINUS:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом +
                    send_string("+");                    
                } else {
                    send_string("-");
                }
                set_mods(cur_mods_c);      
            }
            return false;
        case GR_SLASH:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом *
                    send_string("*"); 
                } else {
                    tap_code16(get_cur_lang() == LANG_EN ? KC_SLASH : LSFT(KC_BSLS));
                }
                set_mods(cur_mods_c);            
            }
            //is_arcane = false;
            return false;            
        case GR_COMMA:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом просто запятая
                    tap_code16(RALT(LSFT(KC_5)));
                } else {
                    if (get_cur_lang() == LANG_RU) {
                        send_string("?");
                    } else {
                        tap_code(KC_COMMA);
                    }
                    tap_code(KC_SPC);
                }
                set_mods(cur_mods_c);
            }
            return false;
        case GR_DOT:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {                    
                    // с шифтом `
                    tap_code16(RALT(KC_GRV));                    
                } else {
                    // .
                    if (get_cur_lang() == LANG_RU) {
                        tap_code(KC_SLASH);
                    } else {
                        tap_code(KC_DOT);
                    }
                }
                set_mods(cur_mods_c);
            }
            return false;

        case GR_SBR:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом 
                    tap_code16(RALT(KC_RBRC));
                } else {
                    tap_code16(RALT(KC_LBRC));
                }
                set_mods(cur_mods_c);
            }
            return false;  
        case GR_CBR:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом 
                    tap_code16(RALT(LSFT(KC_RBRC)));
                } else {
                    tap_code16(RALT(LSFT(KC_LBRC)));
                }
                set_mods(cur_mods_c);
            }
            return false; 
        case GR_PR:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом 
                    tap_code16(KC_RPRN);
                } else {
                    tap_code16(KC_LPRN);
                }
                set_mods(cur_mods_c);
            }
            return false;

        default:
            return true;    
    }  

}