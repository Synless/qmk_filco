#include "pegasushoof.h"

#define _______ KC_TRNS

#define KM_QWERTY  0
#define KM_MEDIA   1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Layer 0: Standard ISO layer */
	[KM_QWERTY] = KEYMAP( \
		KC_ESC,          KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_MEDIA_PLAY_PAUSE, \
		KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,  _______,KC_HOME,KC_PGUP, \
		KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,  KC_DEL, KC_END, KC_PGDN, \
		KC_CLCK, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,                            \
		KC_LSFT, KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        KC_RSFT,          KC_UP,           \
		KC_LCTL, KC_LGUI,KC_LALT,                       KC_SPC,                          KC_RALT,KC_RGUI,KC_RCTL,KC_FN0,   KC_LEFT,KC_DOWN,KC_RGHT),
	/* Layer 1: Function layer */
	[KM_MEDIA] = KEYMAP( \
		_______,     KC_MS_LEFT,KC_MS_DOWN,KC_MS_UP,KC_MS_RIGHT,KC_MS_BTN1,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN4,KC_MS_BTN5,_______,_______,_______,   _______,_______,_______, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    RESET ,_______,KC_VOLU, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,KC_VOLD, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                            \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           KC_MPLY,         \
		_______,_______,_______,                        _______,                        _______,_______,_______,_______,   KC_MPRV,KC_MSTP,KC_MNXT)
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(KM_MEDIA)
};

const uint32_t PROGMEM unicode_map[] = {0x0151};

bool canPress = false;

void led_set_user(uint8_t usb_led)
{
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) 
	{
		ph_caps_led_on();
		canPress = false;
	} 
	else
	{
		ph_caps_led_off();
		canPress = true;
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK))
	{
		ph_sclk_led_on();
	} 
	else
	{
		ph_sclk_led_off();
	}
}

void clickKey(uint16_t keycode)
{
	add_key(keycode);
	send_keyboard_report();
	del_key(keycode);
	send_keyboard_report();
	//wait_ms(1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	if(keycode==KC_CLCK)
	{
		if(record->event.pressed && canPress)
		{
			clickKey(KC_CLCK);
		}
		else if(!record->event.pressed && !canPress)
		{
			clickKey(KC_CLCK);
		}		
		return false;
	}
	return true;
}