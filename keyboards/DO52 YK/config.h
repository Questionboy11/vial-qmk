#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEA6
#define PRODUCT_ID      0x0A54
#define DEVICE_VER      0x0001
#define MANUFACTURER    Salicylic_Acid
#define PRODUCT         DO52 YK

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Split Keyboard specific options */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

/* Vial specific options */
#define VIAL_KEYBOARD_UID {0xFA, 0x1B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70, 0x81}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
