#include "action_layer.h"
#include "config.h"
#include "rgblight_list.h"
#include QMK_KEYBOARD_H
#include "keycode.h"
#include "process_tap_dance.h"
#include "quantum_keycodes.h"
#include "rgblight.h"
#include "rgblight_modes.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

bool caps = false;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SHIFT_ENTER,
};

enum {
    TD_CTRL_ESC,
    TD_RESET,
    TD_UNDERGLOW,
};

void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        reset_keyboard();
        reset_tap_dance(state);
    }
}

void tap_rgb(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) rgblight_toggle();
    else if (state->count > 1) rgblight_step();
}


qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ctrl twice for caps lock
    [TD_CTRL_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_LCTRL, KC_ESC),
    // reset to flash tap 3 times to activate 
    [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
    [TD_UNDERGLOW] = ACTION_TAP_DANCE_FN(tap_rgb),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |En/Sf |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | GUI  | Alt  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TD(TD_UNDERGLOW), \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLASH, \
  TD(TD_CTRL_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHIFT_ENTER, \
  ADJUST,  KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | MSB1 | MSUP | MSB2 |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | MSL  | MSDN | MSR  |      |      |      |  _   |  +   |  {   |  }   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
  _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Grv  |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |      |  Up  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |      |      |  -   |  =   |  [   |  ]   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mute |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Play |      | Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_CAPS, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, _______, KC_MINS, KC_EQUAL,KC_LBRC, KC_RBRC, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT  \
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TD(TD_RESET), \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t shift_timer;
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case KC_CAPS:
      if (record->event.pressed) {
          caps = !caps;
          if (caps) rgblight_sethsv_noeeprom(HSV_ORANGE); 
      }
      break;
    case SHIFT_ENTER:
      if(record->event.pressed) {
          shift_timer = timer_read();
          register_code(KC_LSHIFT);
      } else {
          unregister_code(KC_LSHIFT);
          if (timer_elapsed(shift_timer) < TAPPING_TERM) {
              send_string(SS_TAP(X_ENTER));
          }
      }
      return false;
      break;
  }
  return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_WHITE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _RAISE:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case _LOWER:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
        case _QWERTY:
            if (caps) rgblight_sethsv_noeeprom(HSV_ORANGE); 
            else rgblight_sethsv_noeeprom(HSV_WHITE);
            break;
    }
    return state;
}
#endif
