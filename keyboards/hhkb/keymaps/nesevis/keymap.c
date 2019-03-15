/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H

#define BASE 0
#define HHKB 1

// Tap Dance Declarations
enum {
  TD_LBRC_LPRN = 0,
  TD_RBRC_RPRN = 1,
  TD_RABK_FSHARP_PIPE = 2,
};

enum {
  M_NORWEGIAN_AE = 2,
  M_ACCENT_MOVED = 3,
  M_SHFT_BSPC_IS_DELETE = 4,
  M_ESC_IS_GRAVE_WITH_CMD = 5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Esc   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -     | =   | \     | ` |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Tab   | Q | W | E | R | T | Y | U | I | O | P | [     | ]   | Backs |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Cont  | A | S | D | F | G | H | J | K | L | ; | '     | Ent |       |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Shift | Z | X | C | V | B | N | M | , | . | / | Shift | Fn0 |       |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|

            |------+------+-----------------------+------+------|
            | LAlt | LGUI | ******* Space ******* | RGUI | RAlt |
            |------+------+-----------------------+------+------|
    */

    [BASE] = LAYOUT( //  default layer
        M(M_ESC_IS_GRAVE_WITH_CMD), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, M(M_NORWEGIAN_AE), KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD(TD_LBRC_LPRN), TD(TD_RBRC_RPRN), M(M_SHFT_BSPC_IS_DELETE),
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, M(M_ACCENT_MOVED), KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, TD(TD_RABK_FSHARP_PIPE), KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, /*        */ KC_SPC, KC_RGUI, KC_RALT),

    /* Layer HHKB: HHKB mode (HHKB Fn)
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Pwr  | F1  | F2  | F3  | F4 | F5 | F6 | F7 | F8  | F9  | F10 | F11 | F12   | Ins   | Del |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Caps |     |     |     |    |    |    |    | Psc | Slk | Pus | Up  |       | Backs |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      | VoD | VoU | Mut |    |    | *  | /  | Hom | PgU | Lef | Rig | Enter |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      |     |     |     |    |    | +  | -  | End | PgD | Dow |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|

                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+

     */

    [HHKB] = LAYOUT(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

bool mod_down(uint16_t key_code)
{
  return keyboard_report->mods & MOD_BIT(key_code);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    bool pressed = record->event.pressed;
    bool altDown = mod_down(KC_RALT) || mod_down(KC_LALT);
    bool cmdDown = mod_down(KC_RGUI) || mod_down(KC_LGUI);
    bool lShiftDown = mod_down(KC_LSHIFT);
    bool rShiftDown = mod_down(KC_RSHIFT);
    bool shiftDown = lShiftDown || rShiftDown;
    switch (id)
    {
    case HHKB:
      pressed
        ? register_code(KC_RSFT)
        : unregister_code(KC_RSFT);
      break;
    // Moving Æ from alt+right quote to alt+e, to bring it in line with ø and å
    case M_NORWEGIAN_AE:
      pressed
        ? register_code(altDown ? KC_QUOT : KC_E)
        : unregister_code(altDown ? KC_QUOT : KC_E);
      break;
    // Moving accent dead key to where æ was moved from
    case M_ACCENT_MOVED:
      pressed
        ? register_code(altDown ? KC_E : KC_QUOT)
        : unregister_code(altDown ? KC_E : KC_QUOT);
        break;
    // Tapping backspace when either shift is held turns 
    // it into a delete, matching Apple keyboard behaviour
    case M_SHFT_BSPC_IS_DELETE:
      if (shiftDown && pressed) {
        // Turn shift off momentarily
        unregister_code(lShiftDown ? KC_LSHIFT : KC_RSHIFT);
        register_code(KC_DEL);
        register_code(lShiftDown ? KC_LSHIFT : KC_RSHIFT);
      } else {
        pressed
          ? register_code(shiftDown ? KC_DEL : KC_BSPC)
          : unregister_code(shiftDown ? KC_DEL : KC_BSPC);
      }
      break;
    case M_ESC_IS_GRAVE_WITH_CMD:
      pressed
        ? register_code(cmdDown ? KC_GRV : KC_ESC)
        : unregister_code(cmdDown ? KC_GRV : KC_ESC);
    }
    return MACRO_NONE;
};

void fsharp_pipe(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code(KC_DOT); unregister_code(KC_DOT);
    break;
  case 2:
    if (mod_down(KC_LSHIFT) || mod_down(KC_RSHIFT))
    {
      // Fsharp |> pipe character
      register_code(KC_BSLS); unregister_code(KC_BSLS); register_code(KC_DOT); unregister_code(KC_DOT);
    }
    else
    {
      // Just two dots.
      register_code(KC_DOT); unregister_code(KC_DOT); register_code(KC_DOT); unregister_code(KC_DOT);
    }

    break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Esc, twice for Caps Lock
    [TD_LBRC_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LPRN),
    [TD_RBRC_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RPRN),
    [TD_RABK_FSHARP_PIPE] = ACTION_TAP_DANCE_FN(fsharp_pipe),

};
