#include QMK_KEYBOARD_H

enum custom_keycodes {
    DTP_LEFT = SAFE_RANGE,
    DTP_RIGHT,
    DTP_MID,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                KC_7,         KC_8,         KC_9,         KC_TRNS,
                KC_MPRV,      KC_MPLY,      KC_MNXT,      KC_TRNS,
                KC_1,         KC_2,         KC_3,         KC_TRNS,
                DTP_LEFT,     DTP_MID,      DTP_RIGHT
                ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DTP_LEFT:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_LCTRL);
            register_code(KC_LEFT);
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTRL);
            unregister_code(KC_LEFT);
        } break;

    case DTP_RIGHT:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_LCTRL);
            register_code(KC_RIGHT);
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTRL);
            unregister_code(KC_RIGHT);
        } break;

    case DTP_MID:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_TAB);
            unregister_code(KC_LGUI);
            unregister_code(KC_TAB);
        } break;

    }
    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      rgblight_increase_hue(); //Cycle through the RGB hue
    } else {
      rgblight_decrease_hue();
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_VOLU); //Example of using tap_code which lets you use keycodes outside of the keymap
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 2) { /* Third encoder */
    if (clockwise) {
      rgblight_increase_val(); //Change brightness on the RGB LEDs
    } else {
      rgblight_decrease_val();
    }
  }
}
