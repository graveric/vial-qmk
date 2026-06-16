static uint16_t last_keys[2] = {KC_NO, KC_NO};
static uint8_t last_mods = 0;
static bool is_arcane = false;   
/*enum phenom_micro_keycodes {
    HRM_GUI_SCR   = EH_PRINFO,
    HRM_RGUI_EXLM = EH_RSRV1,
    HRM_LALT_LPRN = EH_RSRV5,
    HRM_LCTL_RPRN,
    HRM_RCTL_LCBR,
    HRM_RALT_RCBR,
};

typedef struct {
    uint16_t keycode;
    uint16_t tap_keycode;
    uint8_t  mod;
} phenom_micro_hrm_t;

typedef struct {
    uint16_t timer;
    uint8_t  mod;
    bool     pressed;
    bool     held;
} phenom_micro_hrm_state_t;

static const phenom_micro_hrm_t phenom_micro_hrms[] = {
    {HRM_GUI_SCR,   EH_SCR,   MOD_BIT(KC_LEFT_GUI)},
    {HRM_RGUI_EXLM, KC_EXLM,  MOD_BIT(KC_RIGHT_GUI)},
    {HRM_LALT_LPRN, KC_LPRN,  MOD_BIT(KC_LEFT_ALT)},
    {HRM_LCTL_RPRN, KC_RPRN,  MOD_BIT(KC_LEFT_CTRL)},
    {HRM_RCTL_LCBR, KC_LCBR,  MOD_BIT(KC_RIGHT_CTRL)},
    {HRM_RALT_RCBR, KC_RCBR,  MOD_BIT(KC_RIGHT_ALT)},
};

static phenom_micro_hrm_state_t phenom_micro_hrm_states[ARRAY_SIZE(phenom_micro_hrms)];

static int8_t phenom_micro_hrm_index(uint16_t keycode) {
    for (uint8_t i = 0; i < ARRAY_SIZE(phenom_micro_hrms); ++i) {
        if (phenom_micro_hrms[i].keycode == keycode) {
            return i;
        }
    }
    return -1;
}

static void phenom_micro_hrm_hold(uint8_t index) {
    phenom_micro_hrm_state_t *state = &phenom_micro_hrm_states[index];
    if (state->pressed && !state->held) {
        register_mods(state->mod);
        state->held = true;
    }
}

static void phenom_micro_hrm_hold_pending_except(uint16_t keycode) {
    for (uint8_t i = 0; i < ARRAY_SIZE(phenom_micro_hrms); ++i) {
        if (phenom_micro_hrms[i].keycode != keycode) {
            phenom_micro_hrm_hold(i);
        }
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
