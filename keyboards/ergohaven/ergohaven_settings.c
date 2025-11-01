#include "ergohaven_settings.h"
#include "ergohaven_ruen.h"
#include <eeconfig.h>
#include <debug.h>
#include <qmk_settings.h>

kb_config_t kb_config;

void kb_config_update(kb_config_t new_config) {
    if (new_config.raw != kb_config.raw) {
        kb_config = new_config;
        dprintf("kb_config_update %ld \n", kb_config.raw);
        eeconfig_update_kb_datablock(&kb_config, 0, sizeof(kb_config_t));
    }
}

void kb_config_update_ruen_toggle_mode(uint8_t mode) {
    kb_config_t new_config      = kb_config;
    new_config.ruen_toggle_mode = mode;
    kb_config_update(new_config);
}

void kb_config_update_ruen_mac_layout(bool mac_layout) {
    kb_config_t new_config     = kb_config;
    new_config.ruen_mac_layout = mac_layout;
    kb_config_update(new_config);
}

void init_kb_settings(void) {
    eeconfig_read_kb_datablock(&kb_config, 0, sizeof(kb_config_t));
    dprintf("eeconfig_read_kb_datablock %ld \n", kb_config.raw);
}

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
