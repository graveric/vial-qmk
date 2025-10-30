#include "ergohaven_settings.h"
#include <eeconfig.h>
#include <debug.h>

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
