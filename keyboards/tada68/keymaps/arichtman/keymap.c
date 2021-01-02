#include QMK_KEYBOARD_H

bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

enum custom_keycodes { _MACRO_RANGE = SAFE_RANGE, UNDO, COPY, CUT, PASTE, ALT_TAB, CLOSE_TAB };

enum tapdances { TD_BACK = 0, TD_FWD, TD_LBR, TD_RBR, TD_MACRO };

void leftBracket(qk_tap_dance_state_t *state, void *user_data);
void rightBracket(qk_tap_dance_state_t *state, void *user_data);
void dynMacro(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 3) return;

    keyrecord_t kr;
    kr.event.pressed = false;
    uint16_t action  = DYN_REC_STOP;

    if (state->count == 1) {
        action = DYN_MACRO_PLAY1;
    } else if (state->count == 2) {
        action           = DYN_REC_STOP;
        kr.event.pressed = true;
    } else if (state->count == 3) {
        action = DYN_REC_START1;
    }

    process_dynamic_macro(action, &kr);
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD_BACK]  = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
    [TD_FWD]   = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),
    [TD_LBR]   = ACTION_TAP_DANCE_FN(leftBracket),
    [TD_RBR]   = ACTION_TAP_DANCE_FN(rightBracket),
    [TD_MACRO] = ACTION_TAP_DANCE_FN(dynMacro)};

#define _BASE 0
#define _FUNCTION 1
#define _NUMBER 2
#define _NORMAL 3
#define _NORMFUN 4

#define FN_ENT MT(MOD_RCTL, KC_ENT)
#define FN_SPC LT(_FUNCTION, KC_SPC)
#define FN_TAB LT(_NUMBER, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BASE: (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |`Esc| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
     * |----------------------------------------------------------------|
     * |Tab/#|  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|[({|])}|  \  |Del |
     * |----------------------------------------------------------------|
     * |Backsp |  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Return |PgUp|
     * |----------------------------------------------------------------|
     * |Shift (|  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift )| Up|PgDn|
     * |----------------------------------------------------------------|
     * |Ctrl|Win |Alt |      Space / Fn       |Alt|Num|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    // for some reason win and alt are reversed :s
    [_BASE] = LAYOUT_ansi(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_GRV, FN_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, TD(TD_LBR), TD(TD_RBR), KC_BSLS, KC_DEL, KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, FN_ENT, TD(TD_BACK), KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_UP, TD(TD_FWD), KC_LCTL, KC_LALT, KC_LGUI, FN_SPC, KC_RALT, MO(_FUNCTION), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap _FUNCTION: Function Layer
     * ,----------------------------------------------------------------.
     * | TM| F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    | BL |
     * |----------------------------------------------------------------|
     * | Del |Qt |Ctb|ATb|Psc|MB1|MWU|Hme|PgU|PgDn|En|Ins|   |     |BLT |
     * |----------------------------------------------------------------|
     * | SCtr |MsL|MsU|MsD|MsR|MB2|MWD|Lef|Dow|Up |Rig|   |        |    |
     * |----------------------------------------------------------------|
     * |        |Udo|Cut|Cpy|Pst|MSt|MSp|MPy|VU-|VU+|MUT|   McL|MsU|McR |
     * |----------------------------------------------------------------|
     * |    |GTOG|    |                       |   |   |    |MsL|MsD|MsR |
     * `----------------------------------------------------------------'
     */

    [_FUNCTION] = LAYOUT_ansi(TO(_NUMBER), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, BL_STEP, KC_DEL, LALT(KC_F4), CLOSE_TAB, ALT_TAB, KC_PSCR, KC_BTN1, KC_MS_WH_UP, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_INS, _______, _______, BL_BRTG, OSM(MOD_LCTL), KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_BTN2, KC_MS_WH_DOWN, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, _______, _______, UNDO, CUT, COPY, PASTE, _______, _______, TD(TD_MACRO), KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),

    /* Keymap _NUMBER: Number Layer
     * ,----------------------------------------------------------------.
     * |   |   |   |   |   |   |   |  7|  8|  9|  /|   |   |       |AST |
     * |----------------------------------------------------------------|
     * |     |   |Nlk|   |   |   |   |  4|  5|  6|  *|  /|   |     |ASP |
     * |----------------------------------------------------------------|
     * |      |   |   |   |   |   |Ent|  1|  2|  3|  +|  -|        |ASUp|
     * |----------------------------------------------------------------|
     * |        |   |   |   |   |   |  0|  .|   |   |  -|      |   |ASDn|
     * |----------------------------------------------------------------|
     * |    |    |    |                       |   |   |    |   |   |    |
     * `----------------------------------------------------------------'
     */

    [_NUMBER] = LAYOUT_ansi(_______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH, _______, _______, _______, KC_ASTG, _______, _______, KC_NUMLOCK, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, KC_KP_SLASH, _______, _______, KC_ASRP, _______, _______, _______, _______, _______, _______, KC_KP_ENTER, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_PLUS, KC_KP_MINUS, _______, KC_ASUP, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_KP_DOT, _______, _______, KC_KP_MINUS, _______, _______, KC_ASDN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* Keymap _NORMAL: (Normie Layer) QWERTY Layer
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
     * |----------------------------------------------------------------|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
     * |----------------------------------------------------------------|
     * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */

    [_NORMAL] = LAYOUT_ansi(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_GRV, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_NORMFUN), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap _NORMFUN: Layer Layer [yea, ok]
     * ,----------------------------------------------------------------.
     * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
     * |----------------------------------------------------------------|
     * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Hme |
     * |----------------------------------------------------------------|
     * |      |<- |Dn | ->|   |   |   |   |   |   |   |   |        |End |
     * |----------------------------------------------------------------|
     * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
     * |----------------------------------------------------------------|
     * |    |    |    |                       |   |   |    |MsL|MsD|MsR |
     * `----------------------------------------------------------------'
     */

    [_NORMFUN] = LAYOUT_ansi(TO(_BASE), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS, _______, _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END, _______, _______, _______, BL_DEC, BL_TOGG, BL_INC, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),
};

// There are keycodes for some of these but they aren't recognised in some cases
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CLOSE_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("w"));
            }
            break;
        case COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("c"));
            }
            break;
        case CUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("x"));
            }
            break;
        case PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("v"));
            }
            break;
        case UNDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("z"));
            }
            break;
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
    };
    return true;
};
// bracket subroutines may be improved using register_code16 or something but seems to recurse
// bracket subroutines can be made more DRY
void leftBracket(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            send_string("(");
            break;
        case 3:
            send_string("{");
            break;
        default:
            send_string("[");
    }
}

void rightBracket(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            send_string(")");
            break;
        case 3:
            send_string("}");
            break;
        default:
            send_string("]");
    }
};

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 800) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
};

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case KC_LBRC:
        case KC_RBRC:
            return 200;
            break;
        default:
            return TAPPING_TERM;
    }
}
