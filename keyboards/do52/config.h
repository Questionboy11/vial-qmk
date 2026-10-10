#pragma once

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

/* Key matrix pins */
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

/* 安全対策: Escキー長押しでブートローダー起動 */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

/* Pointing device (Trackpoint) */
#define POINTING_DEVICE_ENABLE