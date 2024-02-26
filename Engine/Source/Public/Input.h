#pragma once

typedef enum
{
    NF_KEY_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    NF_KEY_A = 4,
    NF_KEY_B = 5,
    NF_KEY_C = 6,
    NF_KEY_D = 7,
    NF_KEY_E = 8,
    NF_KEY_F = 9,
    NF_KEY_G = 10,
    NF_KEY_H = 11,
    NF_KEY_I = 12,
    NF_KEY_J = 13,
    NF_KEY_K = 14,
    NF_KEY_L = 15,
    NF_KEY_M = 16,
    NF_KEY_N = 17,
    NF_KEY_O = 18,
    NF_KEY_P = 19,
    NF_KEY_Q = 20,
    NF_KEY_R = 21,
    NF_KEY_S = 22,
    NF_KEY_T = 23,
    NF_KEY_U = 24,
    NF_KEY_V = 25,
    NF_KEY_W = 26,
    NF_KEY_X = 27,
    NF_KEY_Y = 28,
    NF_KEY_Z = 29,

    NF_KEY_1 = 30,
    NF_KEY_2 = 31,
    NF_KEY_3 = 32,
    NF_KEY_4 = 33,
    NF_KEY_5 = 34,
    NF_KEY_6 = 35,
    NF_KEY_7 = 36,
    NF_KEY_8 = 37,
    NF_KEY_9 = 38,
    NF_KEY_0 = 39,

    NF_KEY_RETURN = 40,
    NF_KEY_ESCAPE = 41,
    NF_KEY_BACKSPACE = 42,
    NF_KEY_TAB = 43,
    NF_KEY_SPACE = 44,

    NF_KEY_MINUS = 45,
    NF_KEY_EQUALS = 46,
    NF_KEY_LEFTBRACKET = 47,
    NF_KEY_RIGHTBRACKET = 48,
    NF_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    NF_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate NF_KEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    NF_KEY_SEMICOLON = 51,
    NF_KEY_APOSTROPHE = 52,
    NF_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    NF_KEY_COMMA = 54,
    NF_KEY_PERIOD = 55,
    NF_KEY_SLASH = 56,

    NF_KEY_CAPSLOCK = 57,

    NF_KEY_F1 = 58,
    NF_KEY_F2 = 59,
    NF_KEY_F3 = 60,
    NF_KEY_F4 = 61,
    NF_KEY_F5 = 62,
    NF_KEY_F6 = 63,
    NF_KEY_F7 = 64,
    NF_KEY_F8 = 65,
    NF_KEY_F9 = 66,
    NF_KEY_F10 = 67,
    NF_KEY_F11 = 68,
    NF_KEY_F12 = 69,

    NF_KEY_PRINTSCREEN = 70,
    NF_KEY_SCROLLLOCK = 71,
    NF_KEY_PAUSE = 72,
    NF_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    NF_KEY_HOME = 74,
    NF_KEY_PAGEUP = 75,
    NF_KEY_DELETE = 76,
    NF_KEY_END = 77,
    NF_KEY_PAGEDOWN = 78,
    NF_KEY_RIGHT = 79,
    NF_KEY_LEFT = 80,
    NF_KEY_DOWN = 81,
    NF_KEY_UP = 82,

    NF_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    NF_KEY_KP_DIVIDE = 84,
    NF_KEY_KP_MULTIPLY = 85,
    NF_KEY_KP_MINUS = 86,
    NF_KEY_KP_PLUS = 87,
    NF_KEY_KP_ENTER = 88,
    NF_KEY_KP_1 = 89,
    NF_KEY_KP_2 = 90,
    NF_KEY_KP_3 = 91,
    NF_KEY_KP_4 = 92,
    NF_KEY_KP_5 = 93,
    NF_KEY_KP_6 = 94,
    NF_KEY_KP_7 = 95,
    NF_KEY_KP_8 = 96,
    NF_KEY_KP_9 = 97,
    NF_KEY_KP_0 = 98,
    NF_KEY_KP_PERIOD = 99,

    NF_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    NF_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
    NF_KEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    NF_KEY_KP_EQUALS = 103,
    NF_KEY_F13 = 104,
    NF_KEY_F14 = 105,
    NF_KEY_F15 = 106,
    NF_KEY_F16 = 107,
    NF_KEY_F17 = 108,
    NF_KEY_F18 = 109,
    NF_KEY_F19 = 110,
    NF_KEY_F20 = 111,
    NF_KEY_F21 = 112,
    NF_KEY_F22 = 113,
    NF_KEY_F23 = 114,
    NF_KEY_F24 = 115,
    NF_KEY_EXECUTE = 116,
    NF_KEY_HELP = 117,    /**< AL Integrated Help Center */
    NF_KEY_MENU = 118,    /**< Menu (show menu) */
    NF_KEY_SELECT = 119,
    NF_KEY_STOP = 120,    /**< AC Stop */
    NF_KEY_AGAIN = 121,   /**< AC Redo/Repeat */
    NF_KEY_UNDO = 122,    /**< AC Undo */
    NF_KEY_CUT = 123,     /**< AC Cut */
    NF_KEY_COPY = 124,    /**< AC Copy */
    NF_KEY_PASTE = 125,   /**< AC Paste */
    NF_KEY_FIND = 126,    /**< AC Find */
    NF_KEY_MUTE = 127,
    NF_KEY_VOLUMEUP = 128,
    NF_KEY_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     NF_KEY_LOCKINGCAPSLOCK = 130,  */
/*     NF_KEY_LOCKINGNUMLOCK = 131, */
/*     NF_KEY_LOCKINGSCROLLLOCK = 132, */
    NF_KEY_KP_COMMA = 133,
    NF_KEY_KP_EQUALSAS400 = 134,

    NF_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    NF_KEY_INTERNATIONAL2 = 136,
    NF_KEY_INTERNATIONAL3 = 137, /**< Yen */
    NF_KEY_INTERNATIONAL4 = 138,
    NF_KEY_INTERNATIONAL5 = 139,
    NF_KEY_INTERNATIONAL6 = 140,
    NF_KEY_INTERNATIONAL7 = 141,
    NF_KEY_INTERNATIONAL8 = 142,
    NF_KEY_INTERNATIONAL9 = 143,
    NF_KEY_LANG1 = 144, /**< Hangul/English toggle */
    NF_KEY_LANG2 = 145, /**< Hanja conversion */
    NF_KEY_LANG3 = 146, /**< Katakana */
    NF_KEY_LANG4 = 147, /**< Hiragana */
    NF_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
    NF_KEY_LANG6 = 149, /**< reserved */
    NF_KEY_LANG7 = 150, /**< reserved */
    NF_KEY_LANG8 = 151, /**< reserved */
    NF_KEY_LANG9 = 152, /**< reserved */

    NF_KEY_ALTERASE = 153,    /**< Erase-Eaze */
    NF_KEY_SYSREQ = 154,
    NF_KEY_CANCEL = 155,      /**< AC Cancel */
    NF_KEY_CLEAR = 156,
    NF_KEY_PRIOR = 157,
    NF_KEY_RETURN2 = 158,
    NF_KEY_SEPARATOR = 159,
    NF_KEY_OUT = 160,
    NF_KEY_OPER = 161,
    NF_KEY_CLEARAGAIN = 162,
    NF_KEY_CRSEL = 163,
    NF_KEY_EXSEL = 164,

    NF_KEY_KP_00 = 176,
    NF_KEY_KP_000 = 177,
    NF_KEY_THOUSANDSSEPARATOR = 178,
    NF_KEY_DECIMALSEPARATOR = 179,
    NF_KEY_CURRENCYUNIT = 180,
    NF_KEY_CURRENCYSUBUNIT = 181,
    NF_KEY_KP_LEFTPAREN = 182,
    NF_KEY_KP_RIGHTPAREN = 183,
    NF_KEY_KP_LEFTBRACE = 184,
    NF_KEY_KP_RIGHTBRACE = 185,
    NF_KEY_KP_TAB = 186,
    NF_KEY_KP_BACKSPACE = 187,
    NF_KEY_KP_A = 188,
    NF_KEY_KP_B = 189,
    NF_KEY_KP_C = 190,
    NF_KEY_KP_D = 191,
    NF_KEY_KP_E = 192,
    NF_KEY_KP_F = 193,
    NF_KEY_KP_XOR = 194,
    NF_KEY_KP_POWER = 195,
    NF_KEY_KP_PERCENT = 196,
    NF_KEY_KP_LESS = 197,
    NF_KEY_KP_GREATER = 198,
    NF_KEY_KP_AMPERSAND = 199,
    NF_KEY_KP_DBLAMPERSAND = 200,
    NF_KEY_KP_VERTICALBAR = 201,
    NF_KEY_KP_DBLVERTICALBAR = 202,
    NF_KEY_KP_COLON = 203,
    NF_KEY_KP_HASH = 204,
    NF_KEY_KP_SPACE = 205,
    NF_KEY_KP_AT = 206,
    NF_KEY_KP_EXCLAM = 207,
    NF_KEY_KP_MEMSTORE = 208,
    NF_KEY_KP_MEMRECALL = 209,
    NF_KEY_KP_MEMCLEAR = 210,
    NF_KEY_KP_MEMADD = 211,
    NF_KEY_KP_MEMSUBTRACT = 212,
    NF_KEY_KP_MEMMULTIPLY = 213,
    NF_KEY_KP_MEMDIVIDE = 214,
    NF_KEY_KP_PLUSMINUS = 215,
    NF_KEY_KP_CLEAR = 216,
    NF_KEY_KP_CLEARENTRY = 217,
    NF_KEY_KP_BINARY = 218,
    NF_KEY_KP_OCTAL = 219,
    NF_KEY_KP_DECIMAL = 220,
    NF_KEY_KP_HEXADECIMAL = 221,

    NF_KEY_LCTRL = 224,
    NF_KEY_LSHIFT = 225,
    NF_KEY_LALT = 226, /**< alt, option */
    NF_KEY_LGUI = 227, /**< windows, command (apple), meta */
    NF_KEY_RCTRL = 228,
    NF_KEY_RSHIFT = 229,
    NF_KEY_RALT = 230, /**< alt gr, option */
    NF_KEY_RGUI = 231, /**< windows, command (apple), meta */

    NF_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *  See https://usb.org/sites/default/files/hut1_2.pdf
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
    /* @{ */

    NF_KEY_AUDIONEXT = 258,
    NF_KEY_AUDIOPREV = 259,
    NF_KEY_AUDIOSTOP = 260,
    NF_KEY_AUDIOPLAY = 261,
    NF_KEY_AUDIOMUTE = 262,
    NF_KEY_MEDIASELECT = 263,
    NF_KEY_WWW = 264,             /**< AL Internet Browser */
    NF_KEY_MAIL = 265,
    NF_KEY_CALCULATOR = 266,      /**< AL Calculator */
    NF_KEY_COMPUTER = 267,
    NF_KEY_AC_SEARCH = 268,       /**< AC Search */
    NF_KEY_AC_HOME = 269,         /**< AC Home */
    NF_KEY_AC_BACK = 270,         /**< AC Back */
    NF_KEY_AC_FORWARD = 271,      /**< AC Forward */
    NF_KEY_AC_STOP = 272,         /**< AC Stop */
    NF_KEY_AC_REFRESH = 273,      /**< AC Refresh */
    NF_KEY_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    NF_KEY_BRIGHTNESSDOWN = 275,
    NF_KEY_BRIGHTNESSUP = 276,
    NF_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    NF_KEY_KBDILLUMTOGGLE = 278,
    NF_KEY_KBDILLUMDOWN = 279,
    NF_KEY_KBDILLUMUP = 280,
    NF_KEY_EJECT = 281,
    NF_KEY_SLEEP = 282,           /**< SC System Sleep */

    NF_KEY_APP1 = 283,
    NF_KEY_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    NF_KEY_AUDIOREWIND = 285,
    NF_KEY_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
    /* @{ */

    NF_KEY_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    NF_KEY_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    NF_KEY_CALL = 289, /**< Used for accepting phone calls. */
    NF_KEY_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    NF_NUM_KEYS = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} NF_Key;

enum NF_MouseButton : unsigned int {
    NF_MOUSE_LEFT = 0,
    NF_MOUSE_MIDDLE,
    NF_MOUSE_RIGHT,
    // Not a key, just marks the number of buttons
    NF_NUM_BUTTONS
};

struct Vector2;

class Input {
public:
	Input() = default;
	~Input() = default;

	// Process inputs being pressed by the player
	void ProcessInput();

	// Test if the key is pressed down
	bool IsKeyDown(NF_Key Key);

    // Test if a mouse button is down
    bool IsMouseButtonDown(NF_MouseButton Button);

    // Get the position of the mouse on the window
    Vector2 GetMousePos() const;

private:
    // Detext the state of the mouse
    void DetectMouseButtonState(unsigned int Event, bool Value);

private:
    // Quick way to initialise array with all same value
    // state of each button on the mouse
    bool m_MouseState[3] = { false };
};