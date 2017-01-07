// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on MAC (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

//Alias
#define C(kc) LCTL(kc)
#define A(kc) LALT(kc)
#define SC(kc) (S(C(kc)))
#define SA(kc) (S(A(kc)))
#define KC_M_WU KC_MS_WH_UP
#define KC_M_WD KC_MS_WH_DOWN
#define KC_M_WL KC_MS_WH_LEFT
#define KC_M_WR KC_MS_WH_RIGHT
#define KC_M_U KC_MS_U
#define KC_M_D KC_MS_D
#define KC_M_L KC_MS_L
#define KC_M_R KC_MS_R
#define KC_M_A0 KC_MS_ACCEL0
#define KC_M_A1 KC_MS_ACCEL1
#define KC_M_A2 KC_MS_ACCEL2
#define KC_M_B1 KC_MS_BTN1
#define KC_M_B2 KC_MS_BTN2
#define KC_M_B3 KC_MS_BTN3
#define KC_NEXT C(KC_TAB)
#define KC_PREV SC(KC_TAB)

//Layers
enum layers {
  L_COMMON = 0,
  L_MAC,
  L_WIN,
  L_QWERTY,
  L_QWDR,
  L_GAME,
  L_GAME2,
  L_SYMB,
  L_LNAV,
  L_LNAV2,
  L_NAV, // mouse and cursor
  L_CONF // config
};

enum custom_keycodes {
  //--layers--
  // layouts
  CK_GAME = SAFE_RANGE,

  // os
  CK_MAC,
  CK_WIN,

  // lang
  CK_A_EN,
  CK_C_JA,
};

uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1! |   2@ |   3# |   4$ |   5% |      |           |      |   6^ |   7& |   8* |   9( |   0) | PSCR   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |      |      |      |      |      |  [{  |           |  ]}  |      |      |      |      |      | CAPS   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | [{     |      |      |      |      |      |------|           |------|      |      |      |      |      | ]}     |
 * |--------+------+------+------+------+------|  Tab |           |  =+  |------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |           | /CTRL|      |      |      |      |      | =+     |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |  \|  |  `~  | -_ /S|                                       | '" /S|  BS  |  DEL |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      | EISU |------|       |------| KANA   | Enter|
 *                                 |      | /LAlt| LNAV |       | ESC  | /RCtrl | /NAV |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_COMMON] = KEYMAP(  // layer 0 : default
  // left hand
  KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       _______,
  KC_TAB,     _______,    _______,    _______,    _______,    _______,    KC_LBRC,
  KC_LBRC,    _______,    _______,    _______,    _______,    _______,
  KC_LSFT,    _______,    _______,    _______,    _______,    _______,    KC_TAB,
  _______,    _______,    KC_BSLS,    KC_GRV,     SFT_T(KC_MINS),

              _______,    _______,
                          _______,
  _______,    CK_A_EN,    TG(L_LNAV),


  //righthand
  _______,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_PSCR,
  KC_RBRC,    _______,    _______,    _______,    _______,    _______,    KC_CAPS,
              _______,    _______,    _______,    _______,    _______,    KC_RBRC,
  CTL_T(KC_EQL),    _______,    _______,    _______,    _______,    _______,    KC_EQL,
                          SFT_T(KC_QUOT),    KC_BSPC,    KC_DEL,     _______,    _______,

  _______,    _______,
  _______,
  KC_ESC,     CK_C_JA,    LT(L_NAV,KC_ENT)
),


/* Keymap: Mac
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |ctl F2|      |       |ctl sp| ctl F3 |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|      |------|       |------|        |      |
 *                                 |  Cmd |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[L_MAC] = KEYMAP(  // layer 0 : default
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  TD(TD_GSP),    _______,    _______,    _______,    _______,

                  C(KC_F2),   _______,
                              _______,
  GUI_T(KC_SPC),  _______,    _______,


  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  C(KC_SPC),  C(KC_F3),
  _______,
  _______,    _______,    _______
),

/* Keymap: Windows
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Alt F4|      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Space|      |------|       |------|      |      |
 *                                 | LCtrl|      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_WIN] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

              A(KC_F4),   _______,
                          _______,
  CTL_T(KC_SPC),    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap : QWERTY
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,<  |  .>  |  /?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_QWERTY] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       _______,
  _______,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  _______,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       _______,
              KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    _______,
  _______,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),

/* Keymap:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   D  |   R  |   F  |      |           |      |   P  |   K  |   Y  |   L  |  ;:  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   U  |   T  |   G  |------|           |------|   H  |   N  |   I  |   O  |   E  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   B  |   V  |      |           |      |   J  |   M  |  ,<  |  .>  |  /?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_QWDR] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Q,       KC_W,       KC_D,       KC_R,       KC_F,       _______,
  _______,    KC_A,       KC_S,       KC_U,       KC_T,       KC_G,
  _______,    KC_Z,       KC_X,       KC_C,       KC_B,       KC_V,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_P,       KC_K,       KC_Y,       KC_L,       KC_SCLN,    _______,
              KC_H,       KC_N,       KC_I,       KC_O,       KC_E,       _______,
  _______,    KC_J,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),

/* Keymap: Game
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |      |      |      |      |      |  `~  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |      |      |      |      |      | Enter|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|  Tab |           |      |------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  F17 |  F18 |  F19 |  F20 | ESC  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |   N  |   M  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Space| LAlt |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_GAME] = KEYMAP(
  // left hand
  KC_ESC,     _______,    _______,    _______,    _______,    _______,    KC_GRV,
  KC_TAB,     _______,    _______,    _______,    _______,    _______,    KC_ENT,
  KC_LCTL,    _______,    _______,    _______,    _______,    _______,
  KC_LSFT,    _______,    _______,    _______,    _______,    _______,    KC_TAB,
  KC_F17,     KC_F18,     KC_F19,     KC_F20,     KC_ESC,

              KC_N,       KC_M,
                          _______,
  LT(L_GAME2,KC_SPC),     KC_LALT,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: Game layer2
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   0  |   Y  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|   H  |           |      |------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  | F10  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_GAME2] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_Y,
  _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,
  _______,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_H,
  _______,    _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),


/* Keymap: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |  <   |           |   >  |   ^  |   &  |   *  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   <    |   1! |   2@ |   3# |   4$ |   5% |------|           |------|   6^ |   7& |   8* |   9( |   0) |   >    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_SYMB] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_LT,
  KC_LT,      KC_1,       KC_2,       KC_3,       KC_4,       KC_5,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  KC_GT,      KC_CIRC,    KC_AMPR,    KC_ASTR,    _______,    _______,    _______,
              KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_GT,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),


/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | ->CNF  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PREV | M_U  | NEXT | MW_U |   (  |           |  )   | Home | PgUp |  Up  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   (    |      | M_L  | M_D  | M_R  | MW_D |------|           |------| End  | Left | Down | Right|   :  |   )    |
 * |--------+------+------+------+------+------| PREV |           | NEXT |------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |      |  ;:  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | MBtn3| MBtn2|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | MBtn1|      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_NAV] = KEYMAP(
    // left hand
    _______,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,            KC_F11,
    _______,      _______,        KC_PREV,        KC_M_U,         KC_NEXT,        KC_M_WU,          KC_LPRN,
    KC_LPRN,      _______,        KC_M_L,         KC_M_D,         KC_M_R,         KC_M_WD,
    _______,      KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,          KC_PREV,
    _______,      _______,        _______,        KC_M_B3,        KC_M_B2,

                  _______,        _______,
                                  _______,
    KC_M_B1,      _______,        _______,

    //righthand
    KC_F12,       KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,           MO(L_CONF),
    KC_RPRN,      KC_HOME,        KC_PGUP,        KC_UP,          KC_PGDN,        _______,          _______,
                  KC_END,         KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_COLN,          KC_RPRN,
    KC_NEXT,      KC_CIRC,        KC_AMPR,        KC_ASTR,        _______,        KC_SCLN,          _______,
                                  _______,        _______,        _______,        _______,          _______,

    _______,      _______,
    _______,
    _______,      _______,   _______
),

/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PgUp |  Up  | PgDn | Home |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Left | Down | Right| End  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | MBtn1  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | BS   |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 | LNAV2|      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_LNAV] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    KC_PGUP,    KC_UP,      KC_PGDN,    KC_HOME,    _______,
  _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_END,
  KC_M_B1,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    KC_BSPC,

              _______,    _______,
                          _______,
  MO(L_LNAV2),   _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PREV | M_U  | NEXT | MH_U | MBtn3|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | M_L  | M_D  | M_R  | MH_D |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------| MBtn2|           |      |------+------+------+------+------+--------|
 * | MBtn1  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_LNAV2] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    KC_PREV,    KC_M_U,     KC_NEXT,    KC_M_WU,    KC_M_B3,
  _______,    _______,    KC_M_L,     KC_M_D,     KC_M_R,     KC_M_WD,
  KC_M_B1,    _______,    _______,    _______,    _______,    _______,    KC_M_B2,
  _______,    _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: CONF
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET | Mac  | Win  |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  QWRT  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  QWDR  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  game  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_CONF] = KEYMAP(
  // left hand
  RESET,      CK_MAC,     CK_WIN,        _______,    _______,    _______,    _______,
  TO(L_QWDR),       _______,    _______,    _______,    _______,    _______,    _______,
  TO(L_QWERTY),     _______,    _______,    _______,    _______,    _______,
  CK_GAME,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
)

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void switch_layer (uint8_t layer, bool on) {
  if (on) {
    layer_on(layer);
  } else {
    layer_off(layer);
  }
};

void type_code(uint8_t keycode){
  register_code (keycode);
  unregister_code (keycode);
};

void set_eisu(void){
  type_code (KC_MHEN);
  type_code (KC_LANG2);
};

void set_kana(void){
  type_code (KC_HENK);
  type_code (KC_LANG1);
};

bool is_tap (keyrecord_t *record) {
  return hold_timers[record->event.key.row][record->event.key.col]
  && timer_elapsed (hold_timers[record->event.key.row][record->event.key.col]) < TAPPING_TERM;
}

void mod_tap_action(keyrecord_t *record, uint8_t mod, void (*cb)(void) ) {
  if (record->event.pressed) {
    add_mods(MOD_BIT(mod));
  } else {
    if (is_tap(record)) {
      del_mods(MOD_BIT(mod));
      cb();
    } else {
      unregister_code(mod);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // record pressed timer
  if (record->event.pressed) {
    hold_timers[record->event.key.row][record->event.key.col] = timer_read();
  }

  switch (keycode) {
    //--layers--

    //layout
    case CK_GAME:
      if (record->event.pressed) {
        layer_move(L_QWERTY);
        layer_on(L_GAME);
      }
      return false;
      break;

    //os
    case CK_MAC:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<L_MAC);
      }
      return false;
      break;
    case CK_WIN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<L_WIN);
      }
      return false;
      break;

    // langs
    case CK_A_EN: {
      mod_tap_action(record, KC_LALT, set_eisu);
      return false;
      break;
    }
    case CK_C_JA: {
      mod_tap_action(record, KC_RCTL, set_kana);
      return false;
      break;
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  persistant_default_layer_set(1UL<<L_MAC);
  layer_move(L_QWDR);
};
