#pragma once

/* key matrix size (片側 6行 x 6列 = 左右計12行) */
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

/* Key matrix pins (DO52Pro: B5がトラックポイント/マウスボタン拡張行) */
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

/* 安全対策: 左手最上段・最左キー(Esc)長押しでUSB挿入時にブートローダー起動 */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

/* Pointing device (Trackpoint) 有効設定 */
#define POINTING_DEVICE_ENABLE

/* Vial specific options */
#define VIAL_KEYBOARD_UID {0xFA, 0x1B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70, 0x81}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }