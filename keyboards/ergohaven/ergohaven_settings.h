#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef union {
    uint32_t raw;
    struct {
        uint8_t ruen_toggle_mode : 2;
        bool    ruen_mac_layout : 1;
    };
} kb_config_t;

extern kb_config_t kb_config;

void init_kb_settings(void);

void kb_config_update_ruen_toggle_mode(uint8_t mode);

void kb_config_update_ruen_mac_layout(bool mac_layout);
