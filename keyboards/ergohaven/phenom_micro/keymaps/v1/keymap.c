#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "src/eh_ruen.h"
#include "src/eh_pointing.h"
#include "vial.h"



// clang-format off
// phenom-micro-layout-v0.0.17: keep User keycodes inside Vial's USER00..USER63 range.

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

/*static uint16_t last_keys[2] = {KC_NO, KC_NO};
static uint8_t last_mods = 0;
static bool is_arcane = false;*/


bool sw_win_active = false;
bool sw_tab_active = false; 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
KC_J,     KC_Y,     KC_A,     KC_U,     GR_MINUS,                                          KC_Q,     KC_G,     KC_N,     KC_F,     KC_K,
KC_H,     KC_I,     KC_O,     KC_E,     GR_DOT,                                            KC_P,     KC_D,     KC_R,     KC_S,     KC_M, 
KC_X,     GR_UNDER, GR_INCH,  GR_COMMA, GR_SLASH,                                          KC_B,     KC_C,     KC_L,     KC_W,     KC_V,
          LCTL_T(KC_BTN2),   KC_BTN1, KC_LSFT,    LT(_NAVI, KC_SPC), LT(_SHCUT, KC_TAB),           LT(_SYM2, KC_ESC), LT(_SYM1, KC_T),   KC_RSFT,     KC_LALT,  KC_LCTL,
                                                            KC_MUTE,            KC_MUTE
    ),
    
    [_RUS] = LAYOUT(
KC_A,     KC_E,     KC_F,     KC_DOT,   GR_MINUS,                                          KC_I,     KC_V,     KC_Y,     KC_R,     KC_P,
KC_Z,     KC_B, LCTL_T(KC_J), KC_T,     GR_DOT,                                            KC_U,     KC_N, LCTL_T(KC_H), KC_D,     KC_X, 
KC_Q,     KC_S,     KC_M,     GR_COMMA, KC_GRV,                                            KC_COMMA, KC_L,     KC_K,     KC_G,     KC_SEMICOLON,
          _______,   _______, _______,  _______, _______,                                  _______,  LT(_SYM1, KC_C),    _______,  _______,  _______,
                                                            KC_MUTE,            KC_MUTE
    ),    

    [_NAVI] = LAYOUT(
LSFT(KC_DEL), LSFT(KC_HOME), LSFT(KC_UP), LSFT(KC_END), LSFT(LCTL(KC_HOME)),              LCTL(KC_HOME),     KC_HOME,     KC_UP,     KC_END,     KC_PGUP,
LSFT(LCTL(KC_K)), KC_LEFT, KC_DOWN, KC_RIGHT, LSFT(LCTL(KC_END)),                         LCTL(KC_END),      KC_LEFT,     KC_DOWN,   KC_RIGHT,   KC_PGDN,
MO(_KHRN),  _______,   _______,  KC_DEL,  SW_TAB,                                         KC_ENTER,  KC_BSPC,   LCTL(KC_BSPC),  KC_INS,  LT(_KHRN, KC_PSCR),
          KC_LSFT,  KC_LCTL,  _______,  _______,  _______,                                KC_LALT,   MO(_UNI), LT(KC_ESC, _UNI),  KC_LCTL,  KC_RSFT,
                                                            _______,            _______
    ),

    [_SYM1] = LAYOUT(
KC_BSLS,    RALT(KC_E), RALT(KC_F), RALT(KC_COMMA), RALT(KC_DOT),               LSFT(KC_1),  RALT(KC_1),       RALT(KC_Y),       RALT(KC_R),  RALT(KC_BSLS),
RALT(KC_H), RALT(KC_B), RALT(KC_J), KC_LPRN,        KC_RPRN,                    RALT(KC_U),  RALT(LSFT(KC_8)), RALT(LSFT(KC_7)), RALT(KC_7),  LSFT(KC_5),
RALT(KC_6), RALT(KC_S), RALT(KC_L), KC_EQL,         RALT(LSFT(KC_L)),           LSFT(KC_3),  RALT(KC_4),       _______,          LSFT(KC_2),  RALT(LSFT(KC_GRV)),
        KC_VOLU,  KC_VOLD,  LT(_UNI, KC_TAB), LT(_UNI, KC_SPC),  _______,      _______,  _______,  _______,  KC_MPRV,  KC_MNXT,
                                                            _______,            _______
    ),
    
    [_SYM2] = LAYOUT(
KC_F10,         KC_F9,         KC_F4,         KC_F3,         GR_MINUS,          GR_SBR,        KC_7,         KC_8,         KC_9,         RALT(KC_3),
LGUI_T(KC_F11), LALT_T(KC_F8), LCTL_T(KC_F5), LSFT_T(KC_F2), RALT(LSFT(KC_C)),   KC_0,          RSFT_T(KC_1), LCTL_T(KC_2), LALT_T(KC_3), LGUI_T(KC_EQL),
KC_F12,         KC_F7,         KC_F6,         KC_F1,         GR_SLASH,          RALT(KC_SCLN), KC_4,         KC_5,         KC_6,         RALT(LSFT(KC_5)),
          KC_VOLU,  KC_VOLD, _______,  _______,   _______,                      _______,  _______,  _______,  KC_MPRV,  KC_MNXT,
                                                            _______,            _______
    ),

    [_UNI] = LAYOUT(
KC_LALT,          RALT(KC_8), RALT(KC_G),  RALT(KC_X), RALT(KC_I),                    RALT(KC_D),     RALT(KC_A),   RALT(KC_N),          RALT(KC_M),           RALT(KC_V),
RALT(LSFT(KC_M)), RALT(KC_I), RALT(KC_C),  KC_LSFT,    RALT(LSFT(KC_6)),              RALT(KC_MINUS), KC_LSFT,      RALT(LSFT(KC_SCLN)), RALT(LSFT(KC_MINUS)), RALT(KC_5),
KC_LCTL,          RALT(KC_Q), RALT(KC_O) , RALT(KC_Z), RALT(LSFT(KC_3)),              KC_ENTER,       KC_BSPC,      KC_DEL,              RALT(KC_SLASH),       RALT(KC_EQL),
          _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______,
                                                            _______,            _______
    ),   
    
    [_SHCUT] = LAYOUT(
LCTL(KC_W),       LCTL(KC_Q), LCTL(LSFT(KC_I)),   LCTL(LSFT(KC_R)), LCTL(KC_T),      LCTL(KC_MINUS),  LCTL(KC_D), LCTL(KC_N),             LCTL(LSFT(KC_M)),  LCTL(KC_KP_MINUS),
LCTL(LSFT(KC_K)), LCTL(KC_L), LCTL(KC_O),         LCTL(KC_A),       LCTL(KC_F),      LCTL(KC_EQL),    LCTL(KC_P), LCTL(LALT(LSFT(KC_E))), LCTL(KC_COMMA),    LCTL(KC_KP_PLUS),
LALT(KC_F8),      LALT(KC_Z), LCTL(KC_G),         LCTL(KC_R),       LCTL(KC_H),      LCTL(KC_B),      LCTL(KC_I), LCTL(KC_U),             LCTL(LSFT(KC_X)),  LCTL(KC_M),
          _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______,
                                                            _______,            _______
    ),

    [_KHRN] = LAYOUT(
LGUI(LALT(KC_Q)), LGUI(LALT(KC_O)), LGUI(LSFT(KC_K)), LGUI(LALT(KC_R)), LGUI(LALT(KC_T)),       LGUI(KC_F),          LSFT(LALT(KC_F8)), LSFT(LALT(KC_F9)), LSFT(LALT(KC_F10)), LSFT(LALT(KC_F11)),
LGUI(LALT(KC_C)), LGUI(LSFT(KC_H)), LGUI(LSFT(KC_J)), LGUI(LSFT(KC_L)), LGUI(LALT(KC_Y)),       LGUI(LSFT(KC_UP)),   LCTL(KC_F1),       LCTL(KC_F2),       LCTL(KC_F3),        LCTL(KC_F4),
_______,          LGUI(LCTL(KC_K)), LGUI(LCTL(KC_H)), LGUI(LCTL(KC_L)), LGUI(KC_D),             LGUI(LSFT(KC_DOWN)), LGUI(KC_M),        LALT(KC_F3),       LGUI(LSFT(KC_A)),   _______,
          LGUI(KC_K),  LGUI(KC_J),  _______,  _______,   _______,                                _______,  _______,  LGUI(KC_ENTER),  LGUI(LALT(KC_F)),  LGUI(LSFT(KC_J)),
                                                            _______,            _______
    ),         

    [_FDIN] = LAYOUT(
_______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,
          _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______,
                                                            _______,            _______
    ),

    [_ADJST] = LAYOUT(
_______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,
          _______,  _______,  _______,  _______,   _______,                                _______,  _______,  _______,  _______,  _______,
                                                            _______,            _______
    ),

    [_MICE] = LAYOUT(
_______,  _______,  _______,  _______,  _______,                                          _______,  _______,  _______,  _______,  _______,
_______, KC_BTN3,  KC_BTN2,  KC_BTN1,  EH_SNP,                                       EH_SNP,   KC_BTN1,  KC_BTN2,  KC_BTN3,  _______,
_______,  _______,  _______,  _______,  EH_TXT,                                           EH_TXT,   _______,  _______,  _______,  _______,
          _______,  _______,  _______,  _______,  _______,                                _______,  _______,  _______,  _______,  _______,
                                                            _______,            _______
    )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RUS]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_NAVI]  = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
    [_SYM1] = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
    [_SYM2]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
    [_UNI]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},    
    [_SHCUT]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
    [_KHRN]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
    [_FDIN]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},    
    [_ADJST]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},    
    [_MICE]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},    
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
        && keycode != KC_UP
        && keycode != KC_DOWN
    ) {
        unregister_code(cmdish);
        *active = false;
    }
}

/*void send_arcane(const char *string, uint16_t code2, uint16_t code1) {
    //is_arcane = true;
    send_string(string);
    last_keys[0] = code1;
    last_keys[1] = code2;
}

void send_arcane_key(uint16_t code) {
    //is_arcane = true;
    tap_code16(code);
    last_keys[1] = last_keys[0];
    last_keys[0] = code;   
}

void get_arcane_bi_left(void) {
    bool ruon = (get_cur_lang() == LANG_RU);
    switch (last_keys[0]) {
        case KC_Z:
            if (ruon) { //я
                send_arcane_key(KC_Z); //я
                break;
            }
            send_arcane_key(KC_L);
            break;        
        case KC_J:
            if (ruon) { //о
                send_arcane_key(KC_J); //o
                break;
            }
            send_arcane_key(KC_J);
            break;
        case KC_Y:
            if (ruon) { //н
                send_arcane_key(KC_H); //р
                break;
            }
            send_arcane_key(KC_Y);
            break;
        case KC_A:
            if (ruon) { //ф
                send_arcane_key(KC_A); //ф
                break;
            }
            send_arcane_key(KC_A);
            break;
        case KC_U:
            if (ruon) { //г
                send_arcane_key(KC_L); //д
                break;
            }
            send_arcane_key(KC_U);
            break;
        case KC_QUOT:
            if (ruon) { //э
                send_arcane_key(KC_QUOT); //
                break;
            }
            send_arcane_key(KC_QUOT);
            break;
        case KC_DQUO:
            if (ruon) { //Э
                send_arcane_key(S(KC_DQUO)); //
                break;
            }
            send_arcane_key(KC_DQUO);
            break;            
        case KC_MINUS:
            if (ruon) {
                send_arcane_key(KC_MINUS);
                break;
            }
            send_arcane_key(KC_MINUS);
            break;
        case KC_EXLM:
            send_arcane_key(KC_EQL);
            break;
        case KC_LPRN:
            send_arcane_key(KC_LPRN);
            break;
        case KC_PLUS: 
            send_arcane_key(KC_PLUS);
            break;
        case KC_Q:
            if (ruon) { //й
                send_arcane_key(KC_Q); //й
                break;
            }
            send_arcane_key(KC_U);
            break;
        case KC_T:
            if (ruon) { //е
                send_arcane_key(KC_T); //e
                break;
            }
            send_arcane_key(KC_R);
            break;
        case KC_G:
            if (ruon) { //п
                send_arcane_key(KC_Y); //н
                break;
            }
            send_arcane_key(KC_H);
            break;
        case KC_LEFT_BRACKET:
            if (ruon) { //х
                send_arcane_key(KC_H); //р
                break;
            }
            send_arcane_key(KC_RIGHT_BRACKET);
            break;
        case KC_LCBR:
            if (ruon) { //Х
                send_arcane_key(S(KC_H)); //р
                break;
            }
            send_arcane_key(KC_RCBR);
            break;            
        case KC_N:
            if (ruon) { //т
                send_arcane_key(KC_V); //м
                break;
            }
            send_arcane_key(KC_L);
            break;
        case KC_F:
            if (ruon) { //а
                send_arcane_key(KC_F); //а
                break;
            }
            send_arcane_key(KC_W);
            break;
        case KC_K:
            if (ruon) { //л
                send_arcane_key(KC_Y); //н
                break;
            }
            send_arcane("ing", KC_N, KC_G);
            break;
        case KC_H:
            if (ruon) { //р
                send_arcane_key(KC_Y); //н
                break;
            }
            send_arcane_key(KC_H);
            break;
        case KC_I:
            if (ruon) { //ш
                send_arcane_key(KC_N); //т
                break;
            }
            send_arcane_key(KC_I);
            break;
        case KC_O:
            if (ruon) { //щ
                send_arcane_key(KC_Y); //н
                break;
            }
            send_arcane_key(KC_O);
            break;
        case KC_E:
            if (ruon) { //y
                send_arcane_key(KC_E); //у
                break;
            }
            send_arcane_key(KC_E);
            break;
        case KC_DOT:
            if (ruon) { //ю
                send_arcane_key(KC_DOT);   
                break;
            }            
            send_arcane_key(KC_DOT);
            break;
        case KC_SEMICOLON:
            if (ruon) { //ж
                send_arcane_key(KC_X); //ч
                break;
            }            
            send_arcane_key(KC_SEMICOLON);
            break;
        case KC_COLON:
            if (ruon) { //Ж
                send_arcane_key(S(KC_X)); //Ч
                break;
            }            
            send_arcane_key(KC_COLON);
            break;
        case KC_P:
            if (ruon) { //з
                send_arcane_key(KC_SEMICOLON); //ж
                break;
            }
            send_arcane_key(KC_B);
            break;
        case KC_D:
            if (ruon) { //в
                send_arcane_key(KC_R); //к
                break;
            }
            send_arcane_key(KC_G);
            break;
        case KC_R:
            if (ruon) { //к
                send_arcane_key(KC_G); //п
                break;
            }
            send_arcane_key(KC_N);
            break;
        case KC_S:
            if (ruon) { //ы
                send_arcane_key(KC_S); //ы
                break;
            }
            send_arcane_key(KC_W);
            break;
        case KC_M:
            if (ruon) { //ь
                send_arcane_key(KC_M); //ь
                break;
            }
            send_arcane_key(KC_V);
            break;
        case KC_X:
            if (ruon) { //ч
                send_arcane_key(KC_SEMICOLON); //ж
                break;
            }
            send_arcane_key(KC_X );
            break;
        case KC_LT:
            if (ruon) { //Б
                send_arcane_key(LSFT(KC_O)); //Щ
                break;
            }
            send_arcane_key(KC_LT);
            break;
        case KC_GT:
            if (ruon) { //Ю
                send_arcane_key(KC_GT); //Ю
                break;
            }
            send_arcane_key(KC_GT);
            break;
        case KC_COMMA:
            if (ruon) { //б
                send_arcane_key(KC_O); //щ
                break;
            }
            send_arcane_key(KC_COMMA);
            break;           
        case KC_SLASH:
            if (ruon) { //.
                send_arcane_key(KC_SLASH);
                break;
            }
            send_arcane_key(KC_ASTR);
            break;            
        case KC_B:
            if (ruon) { //и
                send_arcane_key(KC_B); //и
                break;
            }
            send_arcane_key(KC_R);
            break;
        case KC_C:
            if (ruon) { //т
                send_arcane_key(KC_N);
                break;
            }
            send_arcane_key(KC_K);
            break;
        case KC_L:
            if (ruon) { //д
                send_arcane_key(KC_Y); //н
                break;
            }
            send_arcane_key(KC_N);
            break;
        case KC_W:
            if (ruon) { //ц
                send_arcane_key(KC_V); //м
                break;
            }
            send_arcane_key(KC_S);
            break;
        case KC_V:
            if (ruon) { //м
                send_arcane_key(KC_COMMA); //б
                break;
            }
            send_arcane_key(KC_M);
            break;
        default:
            uint8_t cur_mods_c = get_mods();
            uint8_t one_mods_c = get_oneshot_mods();
            clear_oneshot_mods();
            clear_mods();
            set_mods(last_mods);
            tap_code16(last_keys[0]);
            set_mods(cur_mods_c);
            set_oneshot_mods(one_mods_c);
            break;    
    }
}    

void get_arcane_bi_right(void) {
    bool ruon = (get_cur_lang() == LANG_RU);
    switch (last_keys[0]) {
        case KC_Z:
            if (ruon) { //я
                send_arcane_key(KC_Q); //й
                break;
            }
            send_arcane_key(KC_Z);
            break;        
        case KC_J:
            if (ruon) { //о
                send_arcane_key(KC_F); //а
                break;
            }
            send_arcane_key(KC_U);
            break;
        case KC_Y:
            if (ruon) { //н
                send_arcane_key(KC_Y); //р
                break;
            }
            send_arcane_key(KC_I);
            break;
        case KC_A:
            if (ruon) { //ф
                send_arcane_key(KC_Z); //я
                break;
            }
            send_arcane_key(KC_O);
            break;
        case KC_U:
            if (ruon) { //г
                send_arcane_key(KC_U); //г
                break;
            }
            send_arcane_key(KC_E);
            break;
        case KC_QUOT:
            if (ruon) { //э
                send_arcane_key(KC_F); //a
                break;
            }
            send_arcane_key(KC_QUOT);
            break;
        case KC_DQUO:
            if (ruon) { //Э
                send_arcane_key(S(KC_F)); //А
                break;
            }
            send_arcane_key(KC_DQUO);
            break;            
        case KC_MINUS:
            if (ruon) {
                send_arcane_key(KC_SPACE);
                break;
            }
            send_arcane_key(KC_GT);
            break;
        case KC_EXLM:
            send_arcane("!!", KC_EXLM, KC_EXLM);
            break;            
        case KC_LPRN:
            send_arcane_key(KC_RPRN);
            break;
        case KC_PLUS: 
            send_arcane_key(KC_SPACE);
            break;
        case KC_Q:
            if (ruon) { //й
                send_arcane_key(KC_A); //ф
                break;
            }
            send_arcane_key(KC_Q);
            break;
        case KC_T:
            if (ruon) { //е
                send_arcane_key(KC_DOT); //ю
                break;
            }
            send_arcane_key(KC_H);
            break;
        case KC_G:
            if (ruon) { //п
                send_arcane_key(KC_G); //п
                break;
            }
            send_arcane_key(KC_G);
            break;
        case KC_LEFT_BRACKET:
            if (ruon) { //х
                send_arcane_key(KC_LEFT_BRACKET); //х
                break;
            }
            send_arcane_key(KC_LEFT_BRACKET);
            break;
        case KC_LCBR:
            if (ruon) { //Х
                send_arcane_key(KC_LCBR); //Х
                break;
            }
            send_arcane_key(KC_LCBR);
            break;            
        case KC_N:
            if (ruon) { //т
                send_arcane_key(KC_N); //т
                break;
            }
            send_arcane_key(KC_N);
            break;
        case KC_F:
            if (ruon) { //а
                send_arcane_key(KC_J); //о
                break;
            }
            send_arcane_key(KC_F);
            break;
        case KC_K:
            if (ruon) { //л
                send_arcane_key(KC_K); //л
                break;
            }
            send_arcane_key(KC_K);
            break;
        case KC_H:
            if (ruon) { //р
                send_arcane_key(KC_H); //р
                break;
            }
            send_arcane_key(KC_Y);
            break;
        case KC_I:
            if (ruon) { //ш
                send_arcane_key(KC_I); //ш
                break;
            }
            send_arcane_key(KC_Y);
            break;
        case KC_O:
            if (ruon) { //щ
                send_arcane_key(KC_O); //щ
                break;
            }
            send_arcane_key(KC_A);
            break;
        case KC_E:
            if (ruon) { //y
                send_arcane_key(KC_B); //и
                break;
            }
            send_arcane_key(KC_U);
            break;
        case KC_DOT:
            if (ruon) { //ю
                send_arcane("? ", KC_COMMA, KC_SPACE); //запятая с пробелом   
                break;
            }            
            send_arcane_key(KC_SPACE);
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case KC_SEMICOLON:
            if (ruon) { //ж
                send_arcane_key(KC_SEMICOLON); //ж
                break;
            }            
            send_arcane_key(KC_RPRN); //;)
            break;
        case KC_COLON:
            if (ruon) { //Ж
                send_arcane_key(S(KC_COLON)); //Ж
                break;
            }            
            send_arcane_key(KC_RPRN); //:)
            break;
        case KC_P:
            if (ruon) { //з
                send_arcane_key(KC_P); //з
                break;
            }
            send_arcane_key(KC_P);
            break;
        case KC_D:
            if (ruon) { //в
                send_arcane_key(KC_D); //в
                break;
            }
            send_arcane_key(KC_D);
            break;
        case KC_R:
            if (ruon) { //к
                send_arcane_key(KC_R); //к
                break;
            }
            send_arcane_key(KC_R);
            break;
        case KC_S:
            if (ruon) { //ы
                send_arcane_key(KC_B); //и
                break;
            }
            send_arcane_key(KC_S);
            break;
        case KC_M:
            if (ruon) { //ь
                send_arcane_key(KC_DOT); //ю
                break;
            }
            send_arcane_key(KC_M);
            break;
        case KC_X:
            if (ruon) { //ч
                send_arcane_key(KC_X); //ч
                break;
            }
            send_arcane_key(KC_H);
            break;
        case KC_LT:
            if (ruon) { //Б
                send_arcane_key(KC_LT); //Б
                break;
            }
            send_arcane_key(KC_GT);
            break;
        case KC_GT:
            if (ruon) { //Ю
                send_arcane("? ", KC_QUES, KC_SPACE);
                break;
            }
            send_arcane_key(KC_EQL);
            break;
        case KC_COMMA:
            if (ruon) { //б
                send_arcane_key(KC_COMMA); //б
                break;
            }
            send_arcane_key(KC_SPACE);
            break;           
        case KC_SLASH:
            if (ruon) { //.
                send_arcane_key(KC_SPACE);
                set_oneshot_mods(MOD_BIT(KC_LSFT));
                break;
            }
            send_arcane_key(KC_ASTR);
            break;
        case KC_ASTR:
            send_arcane_key(KC_SLASH);
            break;
        case KC_B:
            if (ruon) { //и
                send_arcane_key(KC_E); //y
                break;
            }
            send_arcane_key(KC_B);
            break;
        case KC_C:
            if (ruon) { //ъ
                send_arcane_key(KC_RBRC);
                break;
            }
            send_arcane_key(KC_C);
            break;
        case KC_L:
            if (ruon) { //д
                send_arcane_key(KC_L); //д
                break;
            }
            send_arcane_key(KC_L);
            break;
        case KC_W:
            if (ruon) { //ц
                send_arcane_key(KC_W); //ц
                break;
            }
            send_arcane_key(KC_W);
            break;
        case KC_V:
            if (ruon) { //м
                send_arcane_key(KC_V); //м
                break;
            }
            send_arcane_key(KC_V);
            break;
        default:
            uint8_t cur_mods_c = get_mods();
            uint8_t one_mods_c = get_oneshot_mods();
            clear_oneshot_mods();
            clear_mods();
            set_mods(last_mods);
            tap_code16(last_keys[0]);
            set_mods(cur_mods_c);
            set_oneshot_mods(one_mods_c);
            break;    
    }
}*/

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


/*void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {// && !is_arcane) {
        last_keys[1] = last_keys[0];
        last_keys[0] = keycode & 0xFF;
        is_arcane = false;
    }
}*/


/*
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _NAVI:
        set_pointing_mode(POINTING_MODE_TEXT);
        break;
    case _SYM1:
        set_pointing_mode(POINTING_MODE_TEXT);
        break;        
    case _SHCUT:
        set_pointing_mode(POINTING_MODE_TEXT);
        break;
    default: 
        set_pointing_mode(POINTING_MODE_NORMAL);
        break;
    }
  return state;
}*/


/*
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        phenom_micro_hrm_hold_pending_except(keycode);
    }
    return true;
}  */

/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int8_t index = phenom_micro_hrm_index(keycode);
    if (index < 0) {
        return true;
    }

    phenom_micro_hrm_state_t *state = &phenom_micro_hrm_states[index];
    if (record->event.pressed) {
        state->timer   = timer_read();
        state->mod     = phenom_micro_hrms[index].mod;
        if (keycode == HRM_GUI_SCR && record->event.key.row >= MATRIX_ROWS / 2) {
            state->mod = MOD_BIT(KC_RIGHT_GUI);
        }
        state->pressed = true;
        state->held    = false;
    } else {
        if (state->held) {
            unregister_mods(state->mod);
        } else if (phenom_micro_hrms[index].tap_keycode != KC_NO) {
            vial_keycode_tap(phenom_micro_hrms[index].tap_keycode);
        }
        state->pressed = false;
        state->held    = false;
    }
    return false;
}*/

/*void matrix_scan_user(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(phenom_micro_hrms); ++i) {
        if (phenom_micro_hrm_states[i].pressed && timer_elapsed(phenom_micro_hrm_states[i].timer) >= TAPPING_TERM) {
            phenom_micro_hrm_hold(i);
        }
    }
}*/
