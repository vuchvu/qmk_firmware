// Copyright 2022 Arturo Avila (@ADPenrose), Christopher Courtney/Drashna Jael're (@drashna)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Structure that helps store settings in memory and write to the EEPROM: */
typedef union {
  uint32_t raw;
  struct {
    bool     split_zero :1;
    bool     split_enter :1;
    bool     split_plus :1;
  };
} via_layout_t;

via_layout_t via_layouts;

/* Setting up the LED matrix */
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0, 1, 2, 3, NO_LED },
  { 4, 5, 6, 7, NO_LED },
  { 8, 9, 10, 11, 12 },
  { 13, 14, 15, 16, NO_LED },
  { 17, 18, 19, 20, 21 },
  { 22, 23, 24, 25, 26 },
}, {
  // LED Index to Physical Position
  {  0,0  }, { 37,0  }, { 74,0  }, {111,0  }, {  0,34 }, { 37,34 }, { 74,34 }, {111,34 }, {  0,62 }, { 37,62 }, 
  { 74,62 }, {111,62 }, {120,75 }, {  0,89 }, { 37,89 }, { 74,89 }, {111,89 }, {  0,117}, { 37,117}, { 74,117}, 
  {111,117}, {120,130}, {  0,137}, { 18,144}, { 37,137}, { 74,144}, {111,144}
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };

/* Keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                  MO(1),    MO(2),     MO(3),     KC_DEL,
                  KC_NUM,   KC_PSLS,   KC_PAST,   KC_PMNS,
                  KC_P7,    KC_P8,     KC_P9,     KC_PPLS,
                  KC_P4,    KC_P5,     KC_P6,     KC_PPLS,
                  KC_P1,    KC_P2,     KC_P3,     KC_PENT,
        KC_MUTE,  KC_P0,    KC_P0,     KC_PDOT,   KC_PENT 
    ),
    [1] = LAYOUT_all(
                  KC_TRNS,  CK_DOWN,   CK_UP,     CK_RST,
                  MU_TOG,   MU_MOD,    KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        CK_TOGG,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [2] = LAYOUT_all(
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [3] = LAYOUT_all(
                  QK_BOOT,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif

/* Setting layout options and debugging text indicators */
void via_set_layout_options_kb(uint32_t value) { 
  via_layouts.raw = value;
  #ifdef CONSOLE_ENABLE
    if (via_layouts.split_zero && via_layouts.split_enter && via_layouts.split_plus){
      xprintf("All three layouts are active with a value of: %d\n", value);
    } else if (!(via_layouts.split_zero) && via_layouts.split_enter && via_layouts.split_plus){
      xprintf("SE and SP layouts are active with a value of: %d\n", value);
    } else if (via_layouts.split_zero && !(via_layouts.split_enter) && via_layouts.split_plus){
      xprintf("SZ and SP layouts are active with a value of: %d\n", value);
    } else if (!(via_layouts.split_zero) && !(via_layouts.split_enter) && via_layouts.split_plus){
      xprintf("SP is the only layout active with a value of: %d\n", value);
    } else if (via_layouts.split_zero && via_layouts.split_enter && !(via_layouts.split_plus)){
      xprintf("SE and SZ layouts are active with a value of: %d\n", value);
    } else if (!(via_layouts.split_zero) && via_layouts.split_enter && !(via_layouts.split_plus)) {
      xprintf("SE is the only layout active with a value of: %d\n", value);
    } else if (via_layouts.split_zero && !(via_layouts.split_enter) && !(via_layouts.split_plus)){
      xprintf("SZ is the only layout active with a value of: %d\n", value); 
    } else {
      xprintf("The base layout is active with a value of: %d\n", value);
    }
  #endif
}

/* Turing LEDs on/off depending on the layout selected on VIA */
bool rgb_matrix_indicators_user(void){
  if (via_layouts.split_zero && via_layouts.split_enter && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
  } else if (!(via_layouts.split_zero) && via_layouts.split_enter && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
  } else if (via_layouts.split_zero && !(via_layouts.split_enter) && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  } else if (!(via_layouts.split_zero) && !(via_layouts.split_enter) && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  } else if (via_layouts.split_zero && via_layouts.split_enter && !(via_layouts.split_plus)){
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
  } else if (!(via_layouts.split_zero) && via_layouts.split_enter && !(via_layouts.split_plus)) {
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
  } else if (via_layouts.split_zero && !(via_layouts.split_enter) && !(via_layouts.split_plus)){
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  } else {
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  }
  return false;
}
