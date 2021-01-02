#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void dynMacro(qk_tap_dance_state_t *state, void *user_data);

extern keymap_config_t keymap_config;

extern uint8_t is_master;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
	DUMMY = SAFE_RANGE,
	ALT_TAB
};

enum tapdances{
	TD_MACRO = 0
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_MACRO] = ACTION_TAP_DANCE_FN(dynMacro)
};

#define EN_RS LT(_RAISE, KC_ENT)
#define SP_LW LT(_LOWER, KC_SPC)
#define MT_TAB MT(MOD_LCTL | MOD_LSFT, KC_TAB)
#define QUIT LALT(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  |\  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Backsp|   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |(Shift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |)Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Lead | Alt  | Ctl  | /Space  /       \Enter \  | LGui | `Esc | ATab |
 *                   |      |      |      |/ Lower /         \ Raise\ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

 [_BASE] = LAYOUT( \
  KC_MINS,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_EQL,  \
  MT_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,   KC_BSLASH, \
  KC_BSPC,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,      KC_QUOT, \
  KC_LSPO,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSPC, \
                             KC_LEAD, KC_LALT, KC_LCTL, SP_LW,   EN_RS,  KC_LGUI, KC_GESC, ALT_TAB \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Mc2  | ScU  | ScD  | Mc1  | Sp0  |                    |      |  Hme | PgUp | PgDn |  End |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Del  | MsL  | MsU  | MsD  | MsR  | Sp1  |-------.    ,-------|      |  Lt  |  Dn  |  Up  |  Rt  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      | Sp2  |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \Enter \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
   KC_F11, 	 KC_F1, 	KC_F2, 	 KC_F3, 	KC_F4, 	 KC_F5,                     KC_F6,	 KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F12, \
  _______, KC_BTN2, KC_WH_U, KC_WH_D, KC_BTN1, KC_ACL0,                   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______,\
   KC_DEL, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_ACL1,                   _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, \
  _______, _______, _______, _______, _______, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, XXXXXXX, XXXXXXX,  _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  Qt  |      |      | PScr | Ins  |                    |   .  |  7   |  8   |  9   |  *   |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Del |      | Macr |      | ATb  |      |-------.    ,-------|   0  |  4   |  5   |  6   |  +   |  -   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Mute | VolD | VolU |      |      | Brk  |-------|    |-------| Ent  |  1   |  2   |  3   |  =   |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______,  _______, _______, _______,   _______, \
  _______, 		QUIT, _______, _______, KC_PSCR,  KC_INS,                     KC_PDOT, 		KC_7,			KC_8, 	 KC_9, KC_PAST, KC_PSLS, \
  KC_DEL, _______, TD(TD_MACRO), _______, _______, _______,                     KC_0, KC_4, KC_5, KC_6, KC_PPLS, KC_MINS, \
  KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, KC_BRK, _______, _______, KC_PENT, KC_1, KC_2, KC_3, KC_EQUAL, _______, \
                             _______, _______, _______, XXXXXXX, XXXXXXX,  _______, _______, _______ \
)
};

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef OLED_DRIVER_ENABLE
uint16_t oled_timer;

const char *read_logo(void);

void oled_task_user(void) {
	if (timer_elapsed(oled_timer) > OLED_CUSTOM_TIMEOUT) {
		oled_off();
	}else{
		oled_on();
		oled_write(read_logo(), false);
	}
	return;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master)
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

#endif//SSD1306OLED

void ctrl_win(uint16_t keycode){
	tap_code16(LCTL(LGUI(keycode)));
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > ALT_TAB_TIMER) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
	LEADER_DICTIONARY() {
    leading = false;
		
    SEQ_TWO_KEYS(KC_D, KC_R) {
			ctrl_win(KC_RGHT);
    }else
		SEQ_TWO_KEYS(KC_D, KC_L) {
      ctrl_win(KC_LEFT);
    }else
		SEQ_TWO_KEYS(KC_D, KC_N) {
      ctrl_win(KC_D);
    }else
		SEQ_TWO_KEYS(KC_D, KC_Q) {
      ctrl_win(KC_F4);
    }else
		SEQ_TWO_KEYS(KC_D, KC_C) {
      ctrl_win(KC_F4);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		oled_timer = timer_read();
	}
  switch (keycode) {
		case ALT_TAB:
			if (record->event.pressed) {
				if (!is_alt_tab_active) {
					is_alt_tab_active = true;
					register_code(KC_LALT);
				}
					alt_tab_timer = timer_read();
					register_code(KC_TAB);
			  } else {
					unregister_code(KC_TAB);
			  }
			break;
  }

  return true;
}

void dynMacro(qk_tap_dance_state_t *state, void *user_data) {
  if ( state->count > 3 )
    return;

  keyrecord_t kr;
  kr.event.pressed = false;
  uint16_t action = DYN_REC_STOP;

  if ( state->count == 1 ) {
    action = DYN_MACRO_PLAY1;
  }
  else if ( state->count == 2 ) {
    action = DYN_REC_STOP;
    kr.event.pressed = true;
  }
  else if ( state->count == 3 ) {
    action = DYN_REC_START1;
  }

  process_dynamic_macro( action, &kr );
}
