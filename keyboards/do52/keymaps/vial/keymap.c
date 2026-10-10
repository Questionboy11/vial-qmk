#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#ifdef PS2_MOUSE_ENABLE
#    include "ps2_mouse.h"
#endif

/* The OS keyboard layout is assumed to be JIS (Japanese). */

enum layers { _BASE, _SYM, _NAV, _MOUSE, _GAME };

#define SYM_EIS LT(_SYM, KC_LNG2)
#define SPC_SFT LSFT_T(KC_SPC)
#define NAV_ENT LT(_NAV, KC_ENT)
#define MS_KANA LT(_MOUSE, KC_LNG1)

#define BR_BACK A(KC_LEFT)
#define BR_FWD  A(KC_RGHT)
#define TAB_PRV C(S(KC_TAB))
#define TAB_NXT C(KC_TAB)

/* Keys are listed left to right. Each D-pad is: up, left, center, right, down */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, KC_RSFT,
    KC_LGUI, KC_LALT,                   SYM_EIS, SPC_SFT,     NAV_ENT, MS_KANA,                   KC_DEL,  KC_RCTL,
    KC_UP,   KC_LEFT, KC_ENT,  KC_RGHT, KC_DOWN,              MS_WHLU, MS_BTN1, MS_BTN3, MS_BTN2, MS_WHLD
  ),
  [_SYM] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC,     JP_AT,   JP_LBRC, JP_RBRC, JP_YEN,  JP_PIPE, _______,
    _______, JP_AMPR, JP_QUOT, JP_GRV,  JP_TILD, JP_CIRC,     JP_ASTR, JP_LPRN, JP_RPRN, JP_EQL,  JP_PLUS, _______,
    _______, CW_TOGG, XXXXXXX, XXXXXXX, JP_BSLS, XXXXXXX,     JP_UNDS, JP_LCBR, JP_RCBR, JP_LABK, JP_RABK, _______,
    _______, _______,                   _______, _______,     _______, _______,                   _______, _______,
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______
  ),
  [_NAV] = LAYOUT(
    TG(_GAME), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_PSCR, KC_HOME, KC_UP,   KC_END,  KC_PGUP,     JP_ASTR, KC_7,    KC_8,    KC_9,    JP_MINS, _______,
    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,     JP_SLSH, KC_4,    KC_5,    KC_6,    JP_PLUS, KC_ENT,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, JP_HENK, XXXXXXX,     KC_0,    KC_1,    KC_2,    KC_3,    JP_DOT,  _______,
    _______, _______,                   _______, _______,     _______, _______,                   _______, _______,
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______
  ),
  [_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
    _______, BR_BACK, C(KC_W), BR_FWD,  TAB_PRV, TAB_NXT,     _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
    _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),     _______, _______, _______, _______, _______, _______,
    _______, _______,                   _______, _______,     MS_BTN1, MS_BTN2,                   _______, _______,
    _______, _______, _______, _______, _______,              MS_WHLU, MS_BTN1, MS_BTN3, MS_BTN2, MS_WHLD
  ),
  [_GAME] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT,                   KC_LNG2, KC_SPC,      KC_ENT,  KC_LNG1,                   KC_DEL,  TG(_GAME),
    KC_UP,   KC_LEFT, KC_ENT,  KC_RGHT, KC_DOWN,              MS_WHLU, MS_BTN1, MS_BTN3, MS_BTN2, MS_WHLD
  )
};

/*
 * Auto mouse layer: moving the TrackPoint turns on _MOUSE, which turns off again
 * AUTO_MOUSE_TIMEOUT ms after the last movement or click, or as soon as a
 * non-modifier key that is transparent on _MOUSE is pressed. Not used while
 * _GAME is on.
 */
#define AUTO_MOUSE_TIMEOUT 600

static bool     auto_mouse_on;
static bool     mouse_layer_held;
static uint8_t  mouse_buttons_held;
static uint16_t auto_mouse_timer;

static void auto_mouse_off(void) {
    auto_mouse_on = false;
    if (!mouse_layer_held) {
        layer_off(_MOUSE);
    }
}

#ifdef PS2_MOUSE_ENABLE
void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (layer_state_is(_GAME)) {
        return;
    }
    auto_mouse_on = true;
    layer_on(_MOUSE);
    auto_mouse_timer = timer_read();
}
#endif

void housekeeping_task_user(void) {
    if (auto_mouse_on && !mouse_buttons_held && timer_elapsed(auto_mouse_timer) > AUTO_MOUSE_TIMEOUT) {
        auto_mouse_off();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MS_KANA:
            if (record->tap.count == 0) {
                mouse_layer_held = record->event.pressed;
            }
            return true;
        case QK_MOUSE_BUTTON_1 ... QK_MOUSE_BUTTON_8:
            if (record->event.pressed) {
                mouse_buttons_held++;
            } else if (mouse_buttons_held) {
                mouse_buttons_held--;
            }
            auto_mouse_timer = timer_read();
            return true;
    }

    if (auto_mouse_on && record->event.pressed && keymap_key_to_keycode(_MOUSE, record->event.key) == KC_TRNS) {
        bool is_mod = IS_MODIFIER_KEYCODE(keycode) || (IS_QK_MOD_TAP(keycode) && record->tap.count == 0);
        if (!is_mod) {
            auto_mouse_off();
        }
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
