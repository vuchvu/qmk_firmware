#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        XXXXXXX, KC_A,    KC_Y,
        KC_COMM, KC_X,    KC_G,
        KC_LALT, KC_LEFT, KC_UP,
        MO(2),   KC_F,    KC_SPC,
        MO(1),   KC_D,    KC_ENT,
        KC_LSFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        XXXXXXX, KC_Q, KC_C,
        XXXXXXX, KC_W, KC_R,
        XXXXXXX, KC_Z, KC_V,
        KC_TAB,  KC_I, KC_DOT,
        _______, KC_E, KC_T,
        KC_LSFT, KC_C, KC_B
    ),
    [2] = LAYOUT(
        XXXXXXX, KC_7, KC_9,
        XXXXXXX, KC_4, KC_6,
        XXXXXXX, KC_1, KC_3,
        _______, KC_8, KC_0,
        XXXXXXX, KC_5, XXXXXXX,
        XXXXXXX, KC_2, KC_LCTL
    )
};
