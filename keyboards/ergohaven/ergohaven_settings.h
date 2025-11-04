#pragma once

#include <stdint.h>
#include <stdbool.h>

#define LAYER_LABEL_SIZE 16

void kb_settings_init(void);

__attribute__((weak)) void kb_settings_init_layer_labels(void);

uint8_t kb_settings_ruen_toggle_mode(void);

bool kb_settings_ruen_mac_layout(void);

void kb_settings_ruen_toggle_mode_set(uint8_t mode);

void kb_settings_ruen_mac_layout_set(bool mac_layout);

const char *layer_name(uint8_t layer);
