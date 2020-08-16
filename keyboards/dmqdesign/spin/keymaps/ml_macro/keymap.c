#include QMK_KEYBOARD_H
#define _MEDIA 0
#define _RGB 1

enum custom_keycodes {
    DTP_LFT = SAFE_RANGE,
    DTP_RGT,
    DTP_MID,
};

//----------------------------------------------------------------------------------------------------------------------------------------
//-- LAYERS ------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT( /* Base */
                _______,      _______,      RGB_TOG,        TO(_RGB),
                KC_MPRV,      KC_MPLY,      KC_MNXT,        _______,
                _______,      KC_PSCR,      _______,        KC_MUTE,
                DTP_LFT,      DTP_MID,      DTP_RGT
                ),

    [_RGB] = LAYOUT( /* LAYER 1 -- TAP UPPER KNOB */
                _______,      _______,      _______,        TO(_MEDIA),
                _______,      _______,      _______,        _______,
                _______,      _______,      _______,        _______,
                _______,      _______,      _______
              ),
};

//----------------------------------------------------------------------------------------------------------------------------------------
//-- MACROS ------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case DTP_LFT:
          if (record->event.pressed) {
              register_code(KC_LGUI);
              register_code(KC_LCTRL);
              register_code(KC_LEFT);
              clear_keyboard();
          } break;

      case DTP_RGT:
          if (record->event.pressed) {
              register_code(KC_LGUI);
              register_code(KC_LCTRL);
              register_code(KC_RIGHT);
              clear_keyboard();
          } break;

      case DTP_MID:
          if (record->event.pressed) {
              register_code(KC_LGUI);
              register_code(KC_TAB);
              clear_keyboard();
          } break;
    }
    return true;
};

//----------------------------------------------------------------------------------------------------------------------------------------
//-- ENCODER CODES -----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    switch(biton32(layer_state)) {
      case 0: // BASE LAYER
        if (clockwise) {
          rgblight_increase_hue(); //Cycle through the RGB hue
        } else {
          rgblight_decrease_hue();
        }
        break;

      case 1: // FIRST LAYER
        if (clockwise) {
          rgblight_increase_val(); //Change brightness on the RGB LEDs
        } else {
          rgblight_decrease_val();
        }
        break;

    }
  }  else if (index == 1) { /* second encoder -- EMPTY */




  } else if (index == 2) { /* third encoder */
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------
//-- LAYER LIGHTING ----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

// layer_state_t layer_state_set_user(layer_state_t state) { //This will run every time the layer is updated
//     switch(biton32(layer_state)) {
//         case 1:
//             setrgb(RGB_WHITE, &led[0]); //Set the top LED to white for the bottom layer
//             setrgb(0, 0, 0, &led[1]);
//             setrgb(0, 0, 0, &led[2]);
//             break;
//         case 0:
//             setrgb(0, 0, 0, &led[0]); //Set the middle LED to white for the middle layer
//             setrgb(RGB_WHITE, &led[1]);
//             setrgb(0, 0, 0, &led[2]);
//             break;
//         // case 2:
//         //     setrgb(0, 0, 0, &led[0]);
//         //     setrgb(0, 0, 0, &led[1]);
//         //     setrgb(RGB_WHITE, &led[2]); //Set the bottom LED to white for the top layer
//         //     break;
//     }
//     rgblight_set();
//     return state;
// }
