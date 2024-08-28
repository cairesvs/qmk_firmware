#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_CYC, // Cycle between window in the same app (cmd-grv)

    SW_WIN,  // Switch to next window         (cmd-tab)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_planck_grid(
        _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        _______,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
        _______,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
        _______,  _______, _______, _______, LA_NAV,  KC_RSFT, KC_SPC,  LA_SYM,  _______, _______, _______, _______
    ),

    [SYM] = LAYOUT_planck_grid(
        _______, KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,  _______,
        _______, KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, _______,
        _______, KC_PLUS, KC_PIPE, KC_AT,   KC_SLSH, KC_PERC, KC_QUOT, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_planck_grid(
        _______, KC_TAB,  SW_WIN,  TAB_L,   TAB_R,   KC_VOLU, RESET,   HOME,    KC_UP,   END,     KC_DEL,  _______,
        _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______,
        _______, SPACE_L, SPACE_R, BACK,    FWD,     KC_MPLY, XXXXXXX, KC_PGDN, KC_PGUP, OS_CYC,  KC_ENT , _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_planck_grid(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_F11,  KC_F10,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

enum combos {
  // top left
  WER_DELETE,
  // top right
  UI_BSPC,
  UO_CTRL_W,
  // home left
  DF_ESC,
  SD_TAB,
  SF_SEMICOLON, // ;
  // home right
  JK_SEMICOLON, // :
  KL_ENTER,
  JL_SINGLE_QUOTE,
  JKL_DOUBLE_QUOTE,
  // bottom left
  MCOMMA_CIRC,
  MDOT_DOLLAR,
};


// top left
const uint16_t PROGMEM wer_combo[] = {KC_W, KC_E, KC_R, COMBO_END};

// top right
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM uo_combo[] = {KC_U, KC_O, COMBO_END};

// home left
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM sf_combo[] = {KC_S, KC_F, COMBO_END};

// home right
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM jkl_combo[] = {KC_J, KC_K, KC_L, COMBO_END};

// bottom left
const uint16_t PROGMEM mcomma_combo[] = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM mdot_combo[] = {KC_M, KC_DOT, COMBO_END};



combo_t key_combos[] = {
  // top left
  [WER_DELETE] = COMBO(wer_combo, KC_DEL),

  // top right
  [UI_BSPC] = COMBO(ui_combo, KC_BSPC),
  [UO_CTRL_W] = COMBO(uo_combo, C(KC_W)),

  // home left
  [DF_ESC] = COMBO(df_combo, KC_ESC),
  [SD_TAB] = COMBO(sd_combo, KC_TAB),
  [SF_SEMICOLON] = COMBO(sf_combo, KC_SCLN),

  // home right
  [JK_SEMICOLON] = COMBO(jk_combo, S(KC_SCLN)),
  [KL_ENTER] = COMBO(kl_combo, KC_ENT),
  [JL_SINGLE_QUOTE] = COMBO(jl_combo, KC_QUOT),
  [JKL_DOUBLE_QUOTE] = COMBO(jkl_combo, S(KC_QUOT)),

  // bottom left
  [MCOMMA_CIRC] = COMBO(mcomma_combo, KC_CIRC),
  [MDOT_DOLLAR] = COMBO(mdot_combo, KC_DLR),
};

/* void process_combo_event(uint16_t combo_index, bool pressed) { */
/*   switch(combo_index) { */
/*     case WE_CTRL_W: */
/*       if (pressed) { */
/*         tap_code16(C(KC_W)); */
/*       } */
/*       break; */
/*     case UI_SKIP_VM: */
/*       if (pressed) { */
/*         tap_code(KC_LCTL); */
/*         tap_code(KC_LGUI); */
/*       } */
/*       break; */
/*   } */
/* } */

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LGUI, KC_GRV, OS_CYC,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
