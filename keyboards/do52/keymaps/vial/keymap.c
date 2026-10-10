#include <stdlib.h>
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#ifdef PS2_MOUSE_ENABLE
#    include "ps2_mouse.h"
#endif

/* The OS keyboard layout is assumed to be JIS (Japanese). */

enum layers { _BASE, _SYM, _NAV, _MOUSE, _GAME };

/* Right stick: layer selection, identical on every layer */
#define RS_SYM  OSL(_SYM)
#define RS_NAV  TO(_NAV)
#define RS_BASE TO(_BASE)
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
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC,     JP_AT,   JP_LBRC, JP_RBRC, JP_YEN,  JP_PIPE, _______,
    _______, JP_AMPR, JP_QUOT, JP_GRV,  JP_TILD, JP_CIRC,     JP_ASTR, JP_LPRN, JP_RPRN, JP_EQL,  JP_PLUS, _______,
    _______, CW_TOGG, XXXXXXX, XXXXXXX, JP_BSLS, XXXXXXX,     JP_UNDS, JP_LCBR, JP_RCBR, JP_LABK, JP_RABK, _______,
    _______, _______,                   _______, _______,     _______, _______,                   _______, _______,
    _______, _______, _______, _______, _______,              RS_SYM,  RS_GAME, XXXXXXX, RS_NAV,  RS_BASE
  ),
  [_NAV] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_PSCR, KC_HOME, KC_UP,   KC_END,  KC_PGUP,     JP_ASTR, KC_7,    KC_8,    KC_9,    JP_MINS, KC_BSPC,
    _______, JP_HENK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,     JP_SLSH, KC_4,    KC_5,    KC_6,    JP_PLUS, KC_ENT,
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
 * Auto mouse layer: _MOUSE turns on once the TrackPoint has moved at least
 * AUTO_MOUSE_THRESHOLD counts (movements more than AUTO_MOUSE_IDLE_RESET ms
 * apart are not added up). It turns off AUTO_MOUSE_TIMEOUT ms after the last
 * movement or mouse key, or as soon as a non-modifier right-half key that is
 * transparent on _MOUSE is pressed. Left-half keys never turn it off.
 * Not used while _GAME is on.
 */
#define AUTO_MOUSE_THRESHOLD  8
#define AUTO_MOUSE_IDLE_RESET 150
#define AUTO_MOUSE_TIMEOUT    600

static bool     auto_mouse_on;
static uint8_t  mouse_keys_held;
static uint16_t auto_mouse_timer;

static void auto_mouse_off(void) {
    auto_mouse_on = false;
    layer_off(_MOUSE);
}

#ifdef PS2_MOUSE_ENABLE
void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    static uint16_t travel;
    static uint16_t last_move;

    if (layer_state_is(_GAME)) {
        return;
    }
    if (!auto_mouse_on) {
        if (timer_elapsed(last_move) > AUTO_MOUSE_IDLE_RESET) {
            travel = 0;
        }
        last_move = timer_read();
        travel += abs(mouse_report->x) + abs(mouse_report->y);
        if (travel < AUTO_MOUSE_THRESHOLD) {
            return;
        }
        travel        = 0;
        auto_mouse_on = true;
        layer_on(_MOUSE);
    }
    auto_mouse_timer = timer_read();
}
#endif

void housekeeping_task_user(void) {
    if (auto_mouse_on && !mouse_keys_held && timer_elapsed(auto_mouse_timer) > AUTO_MOUSE_TIMEOUT) {
        auto_mouse_off();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_TO(keycode) && record->event.pressed) {
        reset_oneshot_layer();
    }

    switch (keycode) {
        case QK_MOUSE_BUTTON_1 ... QK_MOUSE_BUTTON_8:
        case QK_MOUSE_WHEEL_UP ... QK_MOUSE_WHEEL_RIGHT:
            if (record->event.pressed) {
                mouse_keys_held++;
            } else if (mouse_keys_held) {
                mouse_keys_held--;
            }
            auto_mouse_timer = timer_read();
            return true;
    }

    if (auto_mouse_on && record->event.pressed && record->event.key.row >= MATRIX_ROWS / 2 && keymap_key_to_keycode(_MOUSE, record->event.key) == KC_TRNS && !IS_MODIFIER_KEYCODE(keycode)) {
        auto_mouse_off();
    }
    return true;
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
