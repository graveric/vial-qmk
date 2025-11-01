#pragma once

#include <stdint.h>
#include <stdbool.h>

void init_kb_settings(void);

uint8_t kb_config_ruen_toggle_mode(void);

bool kb_config_ruen_mac_layout(void);

void kb_config_update_ruen_toggle_mode(uint8_t mode);

void kb_config_update_ruen_mac_layout(bool mac_layout);

const char* layer_name(uint8_t layer);
