#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "qmk_settings.h"
#include "ergohaven_ruen.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                        KC_MUTE,
      QK_BOOT, KC_8,       KC_9,
      KC_4, KC_5,       KC_6,
      KC_1, KC_2,       KC_3,
      KC_0, LAYER_PREV, LAYER_NEXT
  ),
  [1] = LAYOUT(
                        _______,
      KC_HOME, KC_INS,  KC_END,
      PREVWRD, KC_UP,   NEXTWRD,
      KC_LEFT, KC_DOWN, KC_RIGHT,
      KC_DEL,  _______, _______
  ),
  [2] = LAYOUT(
                        KC_BTN3,
      C(KC_X), C(KC_C), C(KC_V),
      KC_BTN1, KC_MS_U, KC_BTN2,
      KC_MS_L, KC_MS_D, KC_MS_R,
      KC_PSCR, _______, _______
  ),
  [3] = LAYOUT(
                        KC_MUTE,
      KC_BRID, KC_CPNL, KC_BRIU,
      KC_MYCM, KC_WSCH, KC_MAIL,
      KC_MPRV, KC_MPLY, KC_MNXT,
      KC_CALC, _______, _______
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [1] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
  [2] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

#define DECLARE_SETTING_NOTIFY(id, _get, _set, _notify)  { .qsid=id, .get=_get, .set=_set, .notify=_notify }
#define DECLARE_SETTING(id, _get, _set) DECLARE_SETTING_NOTIFY(id, _get, _set, NULL)
#define DECLARE_STATIC_SETTING_NOTIFY(id, field, notify_)  { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field), .get=eeprom_settings_get, .set=eeprom_settings_set, .notify=notify_ }
#define DECLARE_STATIC_SETTING(id, field) DECLARE_STATIC_SETTING_NOTIFY(id, field, NULL)
#define DECLARE_STATIC_BITSETTING(id, field, bit_) { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field), .bit=bit_, .get=eeprom_settings_getbit, .set=eeprom_settings_setbit }

static int ruen_toggle_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz) {
    uint8_t mode = get_ruen_toggle_mode();
    if (maxsz < sizeof(mode))
        return -1;
    memcpy(setting, &mode, sizeof(mode));
    return 0;
}

static int ruen_toggle_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz) {
    uint8_t mode;
    if (maxsz < sizeof(mode))
        return -1;
    memcpy(&mode, setting, sizeof(mode));
    set_ruen_toggle_mode(mode);
    return 0;
}

static int ruen_macos_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz) {
    bool mac = get_ruen_mac_layout();
    if (maxsz < sizeof(mac))
        return -1;
    memcpy(setting, &mac, sizeof(mac));
    return 0;
}

static int ruen_macos_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz) {
    bool mac;
    if (maxsz < sizeof(mac))
        return -1;
    memcpy(&mac, setting, sizeof(mac));
    set_ruen_mac_layout(mac);
    return 0;
}

static int layer_name_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz) {
    // bool mac = get_ruen_mac_layout();
    // if (maxsz < sizeof(mac))
    //     return -1;
    // memcpy(setting, &mac, sizeof(mac));
    sprintf(setting, "Test");
    return 0;
}

static int layer_name_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz) {
    // bool mac;
    // if (maxsz < sizeof(mac))
        // return -1;
    // memcpy(&mac, setting, sizeof(mac));
    // set_ruen_mac_layout(mac);
    dprintf("layer_name_set %d %s\n", proto->qsid - 200, (const char*)setting);

    return 0;
}

qmk_settings_proto_t kb_protos[KB_SETTINGS_NPROTOS] PROGMEM = {
   DECLARE_SETTING(100, ruen_toggle_get, ruen_toggle_set),
   DECLARE_SETTING(101, ruen_macos_get, ruen_macos_set),
   DECLARE_SETTING(200, layer_name_get, layer_name_set),
   DECLARE_SETTING(201, layer_name_get, layer_name_set),
   DECLARE_SETTING(202, layer_name_get, layer_name_set),
   DECLARE_SETTING(203, layer_name_get, layer_name_set),
   DECLARE_SETTING(204, layer_name_get, layer_name_set),
   DECLARE_SETTING(205, layer_name_get, layer_name_set),
   DECLARE_SETTING(206, layer_name_get, layer_name_set),
   DECLARE_SETTING(207, layer_name_get, layer_name_set),
   DECLARE_SETTING(208, layer_name_get, layer_name_set),
   DECLARE_SETTING(209, layer_name_get, layer_name_set),
   DECLARE_SETTING(210, layer_name_get, layer_name_set),
   DECLARE_SETTING(211, layer_name_get, layer_name_set),
   DECLARE_SETTING(212, layer_name_get, layer_name_set),
   DECLARE_SETTING(213, layer_name_get, layer_name_set),
   DECLARE_SETTING(214, layer_name_get, layer_name_set),
   DECLARE_SETTING(215, layer_name_get, layer_name_set),
};
