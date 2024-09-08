#include QMK_KEYBOARD_H

/*
8 September 2024 - Current working version

2 layers only on the sofle - v1
Home Row ComboKeys

*/

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};

// --------------------------------------------------------
// KEY-COMBOS
// 
// These are the double key presses 
// Two keys pressed at the same time to produce one
// Getting the CMD CTRL keys under your finger tips

/*
|----------------+
| *SCMD | *SCMD  |   
|-------+--------+
| *CMD  | *CMD   | 
|-------+--------+
| *CTRL | *CTRL  | 
|-------+--------+
*/

enum combos {
    COMBO_SYM,
    COMBO_LCTL,
    COMBO_RCTL,
    COMBO_LGUI,
    COMBO_RGUI,
    COMBO_SLGUI,
    COMBO_SRGUI,
    COMBO_LALT,
    COMBO_LCTLGUI,
    COMBO_SDRAISE,
    COMBO_FGRAISE,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

// CTRL =  [CV]  [M,]
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM mcom_combo[] = {KC_M, KC_COMM, COMBO_END};

// CMD = [DF]  [JK]
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

// CMD + SHIFT =   [ER]  [UI]
const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};

// CMD + SHIFT [SD]  [FG]
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {KC_F, KC_G, COMBO_END};

// Two keys defined above, The key you want
combo_t key_combos[] = {
    [COMBO_LCTL] =  COMBO(cv_combo, KC_LCTL),            // CV  =   ctrl
    [COMBO_RCTL] =  COMBO(mcom_combo, KC_LCTL),          // M,  =   ctrl
    [COMBO_LGUI] =  COMBO(df_combo, KC_LGUI),            // DF  =   cmd
    [COMBO_RGUI] =  COMBO(jk_combo, KC_LGUI),            // JK  =   cmd
    [COMBO_SLGUI] = COMBO(ui_combo, LSFT(KC_LGUI)),      // UI  =   cmd+shift
    [COMBO_SRGUI] = COMBO(er_combo, LSFT(KC_LGUI)),      // ER  =   cmd+shift
    [COMBO_SDRAISE] = COMBO(sd_combo, MO(_RAISE)),       // SD  =   raise
    [COMBO_FGRAISE] = COMBO(fg_combo, MO(_RAISE)),       // FG  =   raise
};
// ------------------------------------------------------------------------------

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  \|  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -_ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [{  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC|MOD1| A |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|MUTE   |    | BTN2  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *        | KC_LOWER | RCMD | LCTR |LAlt | /BackSp  /       \Enter\  |Space| LCMD| RAlt | KC_LOWER |
 *            |      |      |      |      |/CMD    /         \ CMD\ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT(
KC_GRV            , KC_1, KC_2, KC_3, KC_4, KC_5,                    KC_6, KC_7, KC_8   , KC_9,   KC_0,    KC_MINS,
KC_TAB            , KC_Q, KC_W, KC_E, KC_R, KC_T,                    KC_Y, KC_U, KC_I   , KC_O,   KC_P,    KC_LBRC,
LT(_LOWER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G,                    KC_H, KC_J, KC_K   , KC_L,   KC_SCLN, LT(_LOWER, KC_QUOT),
KC_LSFT           , KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE,   KC_BTN2,KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_RAISE, KC_RGUI ,KC_LCTRL, KC_LALT,  KC_BSPC,          KC_ENT,  KC_SPC, KC_RCTRL, KC_RALT, KC_RAISE
),
/* LOWER 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |  01  |  02  |  03  |  04  |  05  |                     | .{}   | {}. |().    |).    |tick  |F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | 0    | 0    |  ~   |  #   |  =   |  0   |-------.    ,-------| left | Down | Up | Right  |  ~   |  #  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 w | Shift|  0   |  0   |  0   |   0  |   0  |-------|    |-------|   [  |   ]  |   -  |   +  |  =  |  > .  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | PgUp |PgDown| /Enter  /       \BackSpace\  |backspce| RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */ 
[_LOWER] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
RGUI(KC_TAB),    KC_1,    KC_2,    KC_3,    KC_4,  LALT(KC_0),               KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_EQL,  KC_F12,
  _______, _______,  _______,  KC_MINS,  KC_PLUS, KC_EQL,                    KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT,  KC_PIPE, KC_BSLS,
  _______,  KC_EQL, KC_MINS, LALT(KC_8), LALT(KC_9), LALT(KC_8), _______,       _______, KC_LBRC, KC_RBRC,  KC_MINS,KC_PLUS, KC_EQL, KC_GT,
                       _______, _______, KC_PGUP, KC_PGDN, _______,       KC_ENT, KC_PGUP, KC_PGDN, _______, _______
),
[_RAISE] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, KC_7, KC_8, KC_9,_______, KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_LEFT,  KC_4, KC_5, KC_6,  KC_DEL, KC_BSPC,
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX, KC_1, KC_2, KC_3,   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, KC_0, _______, _______, _______
)
};

#ifdef OLED_ENABLE

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_270;  
        return rotation;
    }

    bool oled_task_user(){
        // This stores the image content
        static const char hello_world_img [] PROGMEM = {
// 'hello_world_corne_final', 32x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 
0xc0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xe8, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xc0, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0x0f, 0x1f, 0x3f, 0x7f, 0x7e, 0x7f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0x7f, 0x7f, 
0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0xf0, 0xf0, 0x70, 0x78, 0x1c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x80, 0xf0, 0x70, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x06, 0x06, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0xff, 0x0f, 0x3f, 0xfc, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x03, 0x03, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0c, 0x0c, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x60, 0x60, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0c, 0x0c, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0xff, 0xdf, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        // this displays the image
        oled_write_raw_P(hello_world_img, sizeof(hello_world_img));
        
        return false;
    }

#endif


#ifdef ENCODER_ENABLE

//-------------------------------------------------------------------
// The KNOBS
//
//
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Volume up and down
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD); // volume down
        } else {
            tap_code(KC_VOLU); // volume up
        }
    } 

    // Zoom in and out- KC_MINS,  + KC_PLUS
    if (index == 1) {
        if (clockwise) {
            tap_code16(LGUI(KC_MINS)); // zoom out
        } else {
            tap_code16(LGUI(KC_PLUS)); // zoom in
        }
    }

    return true;
}

#endif
