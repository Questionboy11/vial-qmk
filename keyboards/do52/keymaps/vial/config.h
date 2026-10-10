#pragma once

#define VIAL_KEYBOARD_UID {0x81, 0x7B, 0xCA, 0x52, 0x10, 0xB2, 0xA9, 0xDD}

/* Esc + 1 */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

/* Base, Symbol, Nav/Num, Mouse, Game */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Max interval (ms) between the two taps that lock the symbol one-shot layer */
#define TAPPING_TERM 200

/* Tap the symbol one-shot key twice to stay on the symbol layer */
#define ONESHOT_TAP_TOGGLE 2
