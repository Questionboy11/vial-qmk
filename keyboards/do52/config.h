#pragma once

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Key matrix pins (DO52 Pro Micro standard) */
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

/* Vial specific options */
#define VIAL_KEYBOARD_UID {0xFA, 0x1B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70, 0x81}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }