# This file intentionally left blank
# BOARD = BLACKPILL_STM32_F401

# OPT_DEFS += -DBOOTLOADER_TINYUF2
# BOOTLOADER_TYPE = tinyuf2
# STM32_BOOTLOADER_ADDRESS = 0x1FFF0000
LTO_ENABLE = no

# FIRMWARE_FORMAT = uf2

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
# RGBLIGHT_ENABLE = yes
# RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
