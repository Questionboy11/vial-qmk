#include <stdlib.h>
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

/* The OS keyboard layout is assumed to be JIS (Japanese). */

enum layers { _BASE, _SYM, _NAV, _MOUSE, _GAME };

enum custom_keycodes {
    RS_BASE = QK_KB_0,
};

/* Right stick: layer selection, identical on every layer */
#define RS_SYM  OSL(_SYM)
#define RS_NAV  TO(_NAV)
#define RS_GAME TO(_GAME)

/* Keys are listed left to right. Each stick is: up, left, center, right, down */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, KC_RSFT,
    KC_LGUI, KC_LALT,                   JP_ZKHK, KC_SPC,      KC_ENT,  KC_BSPC,                   KC_DEL,  KC_RCTL,
    KC_UP,   KC_LEFT, XXXXXXX, KC_RGHT, KC_DOWN,              RS_SYM,  RS_GAME, XXXXXXX, RS_NAV,  RS_BASE
  ),
  [_SYM] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC,     JP_AT,   JP_LBRC, JP_RBRC, JP_YEN,  JP_PIPE, KC_F12,
    _______, JP_AMPR, JP_QUOT, JP_GRV,  JP_TILD, JP_CIRC,     JP_ASTR, JP_LPRN, JP_RPRN, JP_EQL,  JP_PLUS, _______,
    _______, CW_TOGG, XXXXXXX, XXXXXXX, JP_BSLS, XXXXXXX,     JP_UNDS, JP_LCBR, JP_RCBR, JP_LABK, JP_RABK, _______,
    _______, _______,                   _______, _______,     _______, _______,                   _______, _______,
    _______, _______, _______, _______, _______,              RS_SYM,  RS_GAME, XXXXXXX, RS_NAV,  RS_BASE
  ),
  [_NAV] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_PSCR, KC_HOME, KC_UP,   KC_END,  KC_PGUP,     JP_ASTR, KC_7,    KC_8,    KC_9,    JP_MINS, _______,
    _______, JP_HENK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,     JP_SLSH, KC_4,    KC_5,    KC_6,    JP_PLUS, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_0,    KC_1,    KC_2,    KC_3,    JP_DOT,  _______,
    _______, _______,                   _______, _______,     _______, _______,                   _______, _______,
    KC_PGUP, KC_HOME, XXXXXXX, KC_END,  KC_PGDN,              RS_SYM,  RS_GAME, XXXXXXX, RS_NAV,  RS_BASE
  ),
  [_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, MS_WHLU, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, MS_BTN1, MS_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, MS_WHLD, _______, _______, _______,
    _______, _______,                   _______, _______,     _______, _______,                   _______, _______,
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______
  ),
  [_GAME] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, KC_RSFT,
    KC_LGUI, KC_LALT,                   JP_ZKHK, KC_SPC,      KC_ENT,  KC_BSPC,                   KC_DEL,  KC_RCTL,
    KC_UP,   KC_LEFT, XXXXXXX, KC_RGHT, KC_DOWN,              RS_SYM,  RS_GAME, XXXXXXX, RS_NAV,  RS_BASE
  )
};

/*
 * Right stick DOWN (RS_BASE):
 * - Single tap: return to _BASE (turns off _MOUSE and resets one-shot layer)
 * - Double tap or Hold (>= TAPPING_TERM): toggle _MOUSE layer on/off
 */
static bool     rs_base_held;
static bool     rs_base_pending;
static uint16_t rs_base_timer;

static void rs_base_to_base(void) {
    reset_oneshot_layer();
    layer_off(_MOUSE);
    layer_move(_BASE);
}

static void rs_base_toggle_mouse(void) {
    layer_invert(_MOUSE);
}

void housekeeping_task_user(void) {
    if (rs_base_held && timer_elapsed(rs_base_timer) >= TAPPING_TERM) {
        /* Long press detected -> toggle mouse mode immediately */
        rs_base_held    = false;
        rs_base_pending = false;
        rs_base_toggle_mouse();
    } else if (!rs_base_held && rs_base_pending && timer_elapsed(rs_base_timer) >= TAPPING_TERM) {
        /* Single tap confirmed -> return to base layer */
        rs_base_pending = false;
        rs_base_to_base();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_TO(keycode) && record->event.pressed) {
        reset_oneshot_layer();
    }

    if (keycode == RS_BASE) {
        if (record->event.pressed) {
            if (rs_base_pending && timer_elapsed(rs_base_timer) < TAPPING_TERM) {
                /* Double tap detected -> toggle mouse mode */
                rs_base_pending = false;
                rs_base_held    = false;
                rs_base_toggle_mouse();
            } else {
                rs_base_held  = true;
                rs_base_timer = timer_read();
            }
        } else {
            if (rs_base_held) {
                /* Released before TAPPING_TERM -> wait for possible 2nd tap */
                rs_base_held    = false;
                rs_base_pending = true;
                rs_base_timer   = timer_read();
            }
        }
        return false;
    }

    /* If another key is pressed while waiting for a 2nd tap, resolve single tap immediately */
    if (rs_base_pending && record->event.pressed) {
        rs_base_pending = false;
        rs_base_to_base();
    }

    return true;
}

/*
 * State notifications for the PC-side layer indicator (tools/do52_layer_indicator):
 * F13 base, F14 symbol one-shot, F15 symbol locked, F16 nav, F17 game,
 * F18/F19 mouse layer on/off, F20/F21 Caps Word on/off.
 */
static void notify_host(uint16_t keycode) {
    if (is_keyboard_master()) {
        tap_code(keycode);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    static uint16_t last_layer_code = KC_F13;
    static bool     last_mouse;

    const layer_state_t mouse_bit = (layer_state_t)1 << _MOUSE;
    uint16_t            layer_code;
    switch (get_highest_layer(state & ~mouse_bit)) {
        case _SYM:
            layer_code = (get_oneshot_layer_state() & ONESHOT_TOGGLED) ? KC_F15 : KC_F14;
            break;
        case _NAV:
            layer_code = KC_F16;
            break;
        case _GAME:
            layer_code = KC_F17;
            break;
        default:
            layer_code = KC_F13;
            break;
    }
    if (layer_code != last_layer_code) {
        last_layer_code = layer_code;
        notify_host(layer_code);
    }

    bool mouse = state & mouse_bit;
    if (mouse != last_mouse) {
        last_mouse = mouse;
        notify_host(mouse ? KC_F18 : KC_F19);
    }
    return state;
}

void caps_word_set_user(bool active) {
    notify_host(active ? KC_F20 : KC_F21);
}

/* Caps Word for a JIS host: "-" must not be shifted (Shift + "-" is "=" on JIS). */
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case JP_UNDS:
            return true;
        default:
            return false;
    }
}