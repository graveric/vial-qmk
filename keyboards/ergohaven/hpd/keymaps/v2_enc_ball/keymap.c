#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "src/eh_ruen.h"
#include "src/eh_pointing.h"
#include "vial.h"

#define _RUS 1
#define _NAVI 2
#define _NUM 3
#define _SYM 4
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
KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                             KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
KC_ESC,   KC_J,     KC_Y,     KC_A,     KC_U,     GR_MINUS,                                         KC_Q,     KC_G,     KC_N,     KC_F,     KC_K,     KC_BSLS,
KC_TAB,   KC_H,     KC_I,     KC_O,     KC_E,     GR_DOT,                                           KC_P,     KC_D,     KC_R,     KC_S,     KC_M,   KC_QUOT,
KC_LSFT,  KC_X,     GR_UNDER, GR_INCH,  GR_COMMA, GR_SLASH,                                         KC_B,     KC_C,     KC_L,     KC_W,     KC_V,  KC_RSFT,
LCTL_T(KC_BTN2),   KC_BTN1, KC_LSFT,    LT(_NAVI, KC_SPC), LT(_SHCUT, KC_TAB),  _______,            _______,   LT(_NUM, KC_ESC), LT(_SYM, KC_T),   KC_RSFT,     KC_LALT,  KC_LCTL,
                                                                      KC_MUTE,            KC_MUTE
    ),

    [_RUS] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, KC_A,     KC_E,     KC_F,     KC_DOT,   GR_MINUS,                                          KC_I,     KC_V,     KC_Y,     KC_R,     KC_P, _______, 
_______, KC_Z,     KC_B, LCTL_T(KC_J), KC_T,     GR_DOT,                                            KC_U,     KC_N, LCTL_T(KC_H), KC_D,     KC_X, _______, 
_______, KC_Q,     KC_S,     KC_M,     GR_COMMA, KC_GRV,                                            KC_COMMA, KC_L,     KC_K,     KC_G,     KC_SEMICOLON, _______, 
          _______,   _______, _______,  _______, _______, _______,                           _______,  _______,  LT(_SYM, KC_C),    _______,  _______,  _______,
                                                            KC_MUTE,            KC_MUTE
    ),    

    [_NAVI] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, LSFT(KC_DEL), LSFT(KC_HOME), LSFT(KC_UP), LSFT(KC_END), LSFT(LCTL(KC_HOME)),              LCTL(KC_HOME),     KC_HOME,     KC_UP,     KC_END,     KC_PGUP, _______, 
_______, LSFT(LCTL(KC_K)), KC_LEFT, KC_DOWN, KC_RIGHT, LSFT(LCTL(KC_END)),                         LCTL(KC_END),      KC_LEFT,     KC_DOWN,   KC_RIGHT,   KC_PGDN, _______, 
_______, MO(_KHRN),  _______,   _______,  KC_DEL,  SW_TAB,                                         KC_ENTER,  KC_BSPC,   LCTL(KC_BSPC),  KC_INS,  LT(_KHRN, KC_PSCR), _______, 
          KC_LSFT,  KC_LCTL,  _______,  _______,  _______, _______,                             _______, KC_LCTL,   MO(_UNI), KC_LSFT,  KC_LCTL,  KC_RSFT,
                                                            _______,            _______
    ),

    [_NUM] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, KC_F9,         KC_F8,         KC_F4,         KC_F3,          GR_MINUS,          RALT(KC_X),        KC_F5,         KC_F6,         KC_F7,         KC_F10, _______, 
_______, LGUI_T(KC_8), LALT_T(KC_7), LCTL_T(KC_6), LSFT_T(KC_0),      GR_DOT,            KC_EQL,          RSFT_T(KC_1), LCTL_T(KC_2), LALT_T(KC_3), LGUI_T(KC_4), _______, 
_______, KC_F11,        RALT(KC_3),    KC_9,          KC_F12,         GR_SLASH,          RALT(KC_MINUS), KC_F2,         KC_5,         RALT(LSFT(KC_3)),         KC_F1, _______, 
          KC_VOLU,  KC_VOLD, RALT(KC_5),  LT(_SYM, KC_SPC),  RALT(LSFT(KC_6)),  _______,                    _______, _______,  _______,  _______,  KC_MPRV,  KC_MNXT,
                                                            _______,            _______
    ),

    [_SYM] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, KC_BSLS,    _______,  KC_LPRN, KC_RPRN, GR_MINUS,               LSFT(KC_1),  RALT(KC_1),       RALT(KC_MINUS),       RALT(LSFT(KC_MINUS)),  RALT(KC_BSLS), _______, 
_______, _______,  RALT(KC_L), KC_EQL, RALT(LSFT(KC_L)), GR_DOT,          LSFT(KC_2),  RALT(LSFT(KC_8)), RALT(LSFT(KC_7)), RALT(KC_7),  LSFT(KC_5), _______, 
_______, RALT(KC_6), _______,  LSFT(KC_EQL), LSFT(KC_8), GR_SLASH,       LSFT(KC_3),  RALT(KC_4),       RALT(KC_COMMA),          RALT(KC_DOT),  RALT(LSFT(KC_GRV)), _______, 
        KC_VOLU,  KC_VOLD,  KC_LSFT, LT(_UNI, KC_SPC),  KC_LCTL, _______, _______,  _______,  _______,  _______,  KC_MPRV,  KC_MNXT,
                                                            _______,            _______
    ),
    


    [_UNI] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, RALT(KC_Q),       RALT(KC_E), RALT(KC_F),  RALT(KC_P), RALT(KC_I),                    RALT(KC_D),     RALT(KC_A),   RALT(KC_Y),          RALT(KC_R),           RALT(KC_V), _______, 
_______, RALT(KC_H),       RALT(KC_B), RALT(KC_J),  KC_LSFT,    RALT(LSFT(KC_6)),              RALT(KC_U),     KC_LSFT,      RALT(KC_C),          RALT(KC_W),           RALT(KC_K), _______, 
_______, RALT(KC_QUOT),    RALT(KC_S), RALT(KC_O) , RALT(KC_Z), RALT(LSFT(KC_3)),              RALT(KC_G),     KC_BSPC,      RALT(KC_8),          RALT(KC_SLASH),       RALT(KC_EQL), _______, 
          _______,  _______,  _______,  _______,   _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,
                                                            _______,            _______
    ),   
    
    [_SHCUT] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, LSFT(KC_DEL),     LCTL(KC_W), LCTL(LSFT(KC_I)),   LCTL(LSFT(KC_R)), LCTL(KC_T),      LCTL(KC_MINUS),  LCTL(KC_D), LCTL(KC_N),             LCTL(LSFT(KC_M)),  LCTL(KC_KP_MINUS), _______, 
_______, LCTL(LSFT(KC_K)), LCTL(KC_L), LCTL(KC_O),         LCTL(KC_A),       LCTL(KC_F),      LCTL(KC_EQL),    LCTL(KC_P), LCTL(LALT(LSFT(KC_E))), LCTL(KC_COMMA),    LCTL(KC_KP_PLUS), _______, 
_______, LALT(KC_F8),      LALT(KC_Z), LCTL(KC_G),         LCTL(KC_R),       LCTL(KC_H),      LCTL(KC_B),      LCTL(KC_I), LCTL(KC_U),             LCTL(LSFT(KC_X)),  LCTL(KC_Q), _______, 
          _______, _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______, _______, 
                                                            _______,            _______
    ),

    [_KHRN] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, LGUI(LALT(KC_Q)), LGUI(LALT(KC_O)), LGUI(LSFT(KC_K)), LGUI(LALT(KC_R)), LGUI(LALT(KC_T)),       LGUI(KC_F),          LSFT(LALT(KC_F8)), LSFT(LALT(KC_F9)), LSFT(LALT(KC_F10)), LSFT(LALT(KC_F11)), _______, 
_______, LGUI(LALT(KC_C)), LGUI(LSFT(KC_H)), LGUI(LSFT(KC_J)), LGUI(LSFT(KC_L)), LGUI(LALT(KC_Y)),       LGUI(LSFT(KC_UP)),   LCTL(KC_F1),       LCTL(KC_F2),       LCTL(KC_F3),        LCTL(KC_F4), _______, 
_______, _______,          LGUI(LCTL(KC_K)), LGUI(LCTL(KC_H)), LGUI(LCTL(KC_L)), LGUI(KC_D),             LGUI(LSFT(KC_DOWN)), LGUI(KC_M),        LALT(KC_F3),       LGUI(LSFT(KC_A)),   _______, _______, 
          _______, LGUI(KC_K),  LGUI(KC_J),  _______,  _______,   _______,                                _______, _______,  _______,  LGUI(KC_ENTER),  LGUI(LALT(KC_F)),  LGUI(LSFT(KC_J)),
                                                            _______,            _______
    ),         

    [_FDIN] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
          _______, _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______, _______, 
                                                            _______,            _______
    ),

    [_ADJST] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
          _______, _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______, _______, 
                                                            _______,            _______
    ),

    [_MICE] = LAYOUT(
_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, 
_______,_______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______, _______,
_______,_______, KC_BTN3,  KC_BTN2,  KC_BTN1,  EH_SNP,                                       EH_SNP,   KC_BTN1,  KC_BTN2,  KC_BTN3,  _______, _______,
_______,_______,  _______,  _______,  _______,  EH_TXT,                                           EH_TXT,   _______,  _______,  _______,  _______, _______,
          _______, _______,  _______,  _______,  _______,  _______,                                _______,  _______,  _______,  _______,  _______, _______,
                                                            _______,            _______
    )
};

// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RUS]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, 
    [_NAVI]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_NUM] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_SYM]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_UNI]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_SHCUT]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_KHRN]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FDIN]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_ADJST]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_MICE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

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
        && keycode != KC_UP
        && keycode != KC_DOWN
    ) {
        unregister_code(cmdish);
        *active = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //static uint16_t alt1_timer;
    // static uint16_t alt2_timer;
    
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
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_QUOT;                    
                } else {
                    if (ruon) {
                        tap_code16(RALT(KC_2));
                    } else {
                        send_string("\"");
                    }
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_DQUO;
                }
                set_mods(cur_mods_c);            
            }
            //is_arcane = false;
            return false;
        case GR_UNDER:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом ` - убрали
                    /*last_keys[1] = last_keys[0];
                    last_keys[0] = KC_GRV;
                    tap_code16(RALT(KC_GRV));*/
                    
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_DOT;
                    tap_code(KC_MINUS);
                    tap_code16(RALT(LSFT(KC_L)));

                } else {
                    send_string("_");
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_UNDS;
                }
                set_mods(cur_mods_c);            
            }
            //is_arcane = false;
            return false;                    
        case GR_MINUS:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом +
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_PLUS;                    
                    send_string("+");                    
                } else {
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_MINUS;
                    send_string("-");
                }
                set_mods(cur_mods_c);      
            }
            //is_arcane = false;
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
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_ASTR;
                } else {
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_SLASH;                            
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
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_COMMA;
                    tap_code16(RALT(LSFT(KC_5)));
                } else {
                    if (get_cur_lang() == LANG_RU) {
                        send_string("?");
                    } else {
                        tap_code(KC_COMMA);
                    }
                    tap_code(KC_SPC);
                    //last_keys[1] = KC_COMMA;
                    //last_keys[0] = KC_SPACE;
                }
                set_mods(cur_mods_c);
            }
            //is_arcane = false;
            return false;
        case GR_DOT:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом точка и shift - убрали
                    /*last_keys[1] = KC_DOT;
                    last_keys[0] = KC_SPACE;
                    if (get_cur_lang() == LANG_RU) {
                        tap_code(KC_SLASH);
                    } else {
                        tap_code(KC_DOT);
                    }
                    tap_code(KC_SPACE);
                    set_oneshot_mods(MOD_BIT(KC_LSFT));*/
                    
                    // с шифтом `
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_GRV;
                    tap_code16(RALT(KC_GRV));                    
                } else {
                    // .
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_DOT;
                    if (get_cur_lang() == LANG_RU) {
                        tap_code(KC_SLASH);
                        //last_keys[0] = KC_SLASH;
                    } else {
                        tap_code(KC_DOT);
                    }
                }
                set_mods(cur_mods_c);
            }
            //is_arcane = false;
            return false;
        /*case GR_ALT1:
            if (record->event.pressed) {
                //alt1_timer = timer_read();
                is_arcane = true;
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
                //if (timer_elapsed(alt1_timer) < 120) {
                if (is_arcane) {
                    get_arcane_bi_left();
                }
                //}
            }
            return false;  
        case GR_ALT2:
            if (record->event.pressed) {
                //имитируем shift_t
                //alt2_timer = timer_read();
                is_arcane = true;
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
                //if (timer_elapsed(alt2_timer) < 120) {
                if (is_arcane) {
                    get_arcane_bi_right();
                }
                //}
            }
            return false; */
        case GR_SBR:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом 
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_RBRC;
                    tap_code16(RALT(KC_RBRC));
                } else {
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_LBRC;
                    tap_code16(RALT(KC_LBRC));
                }
                set_mods(cur_mods_c);
            }
            //is_arcane = false;
            return false;  
        case GR_CBR:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом 
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_RBRC;
                    tap_code16(RALT(LSFT(KC_RBRC)));
                } else {
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_LBRC;
                    tap_code16(RALT(LSFT(KC_LBRC)));
                }
                set_mods(cur_mods_c);
            }
            //is_arcane = false;
            return false; 
        case GR_PR:
            if (record->event.pressed) {
                uint8_t cur_mods_c = get_mods();
                uint8_t mods_c = cur_mods_c | get_oneshot_mods();
                clear_oneshot_mods();
                clear_mods();
                if (mods_c & MOD_MASK_SHIFT) {
                    //с шифтом 
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_RPRN;
                    tap_code16(KC_RPRN);
                } else {
                    //last_keys[1] = last_keys[0];
                    //last_keys[0] = KC_LPRN;
                    tap_code16(KC_LPRN);
                }
                set_mods(cur_mods_c);
            }
            //is_arcane = false;
            return false;
        /*case GR_BREST:
            if (record->event.pressed) {
                set_split_pointing_side_mode(SPLIT_POINTING_SIDE_LEFT, POINTING_MODE_SCROLL);
                set_split_pointing_side_mode(SPLIT_POINTING_SIDE_RIGHT, POINTING_MODE_NORMAL);                
            }
            is_arcane = false;*/
        default:
            return true;    
    }
}
