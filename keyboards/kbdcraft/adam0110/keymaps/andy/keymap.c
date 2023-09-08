// Keymap for andy
// 
// Keycode overview: https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
//


#include QMK_KEYBOARD_H


enum custom_keycodes {
	M_HELLO = SAFE_RANGE,
M_C_ALL,
	M_VER,
	SRCHSEL,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_HELLO:
        if (record->event.pressed) {
            // when keycode M_HELLO is pressed
            SEND_STRING("hello!");
        } else {
            // when keycode M_HELLO is released
        }
        break;

     case M_VER:
        if (record->event.pressed) {
            SEND_STRING("Keymap version: andy 0003");
        } 
        break;

    case M_C_ALL:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("ac")); // selects all and copies
        }
        break;

    case SRCHSEL:  // Searches the current selection in a new tab.
        if (record->event.pressed) {
    	    // Mac users, change LCTL to LGUI.
    	    SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER));
  	}
	break;
    }

    return true;
};

#define _BASE 	    0
#define _ACCESS     1
#define _SPECIAL    2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_64_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_LEFT,  KC_DOWN, KC_RGHT
        // for Mac, this last line is: 
        // KC_LCTL, KC_LOPT, KC_LCMD, ...
    ),

    [_ACCESS] = LAYOUT_64_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL, 
        KC_NO,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_NO, 
        KC_NO,   M_C_ALL, SRCHSEL, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_SPI, RGB_SPD, KC_HOME,  KC_PGUP,            EE_CLR, 
        KC_NO,   KC_NO,   KC_NO,   KC_CALC, KC_NO,   KC_NO,   NK_TOGG, KC_NO,   KC_NO,   KC_INS,  KC_END,   KC_PGDN,  KC_VOLU,  KC_MUTE, 
        OSL(2),  KC_NO,   KC_NO,                     KC_NO,                              KC_MPRV, KC_TRNS,  KC_MPLY,  KC_VOLD,  KC_MNXT
    ),

    [_SPECIAL] = LAYOUT_64_ansi(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOTLOADER, 
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   M_HELLO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO, 
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   M_VER,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
        KC_NO,   KC_NO,   KC_NO,                     KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};

void rgb_set_color_defined_key(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED) { 
	        if (keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, red, green, blue);
		} else {
                    rgb_matrix_set_color(index, 0, 0, 0);
		}
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _SPECIAL:
            rgb_set_color_defined_key(RGB_PURPLE, led_min, led_max);
            break;
        case _ACCESS:
            rgb_set_color_defined_key(RGB_YELLOW, led_min, led_max);
            break;
        case _BASE:
	    rgb_matrix_set_color_all(RGB_GREEN);
            //rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_SPIRAL);
            break;
        default:
            break;
    }
    return false;
}

// :vim:ts=4:expandtab:
