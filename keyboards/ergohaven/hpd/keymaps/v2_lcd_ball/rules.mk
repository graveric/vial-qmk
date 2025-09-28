VIAL_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3389

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
BACKLIGHT_ENABLE = yes
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm

RAW_ENABLE = yes

SRC += keyboards/ergohaven/ergohaven_pointing.c

SRC += keyboards/ergohaven/ergohaven_display.c
SRC += keyboards/ergohaven/lvgl_helpers.c
SRC += keyboards/ergohaven/ergohaven_symbols_20.c
SRC += keyboards/ergohaven/ergohaven_symbols_28.c
SRC += keyboards/ergohaven/ergohaven_logo.c
SRC += keyboards/ergohaven/ergohaven_display_modes.c

SRC += keyboards/ergohaven/ergohaven_main.c
SRC += keyboards/ergohaven/ergohaven_ruen.c
SRC += keyboards/ergohaven/hid.c
SRC += keyboards/ergohaven/ergohaven_pointing.c
