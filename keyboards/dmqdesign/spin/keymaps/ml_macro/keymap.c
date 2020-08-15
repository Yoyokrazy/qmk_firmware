/* Copyright 2019-2020 DMQ Design
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                KC_7,         KC_8,         KC_9,         KC_TRNS,
                KC_MPRV,      KC_MNXT,      KC_MPLY,      KC_TRNS,
                KC_1,         KC_2,         KC_3,         KC_TRNS,
                KC_0,         M(WIN_TAB),   KC_PSCR
                ),
};

// Macro Declarations
enum custom_keycodes{
    WIN_TAB = 0,
    YOUR_MACRO_2,
    // ..., the rest of your macros
};

// Macro Definitions
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    // for more complex macros (want to add modifiers, etc.)
    case WIN_TAB: {
      if (recond->event.pressed) {
        return MACRO(
          // INSERT CODE HERE for your macro. See https://docs.qmk.fm/macros.html

        );
      }
    }
  }
  return MACRO_NONE;
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
