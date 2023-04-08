export const keyCodes: { [id: string]: number } = {
    "KeyA": 4,                      // A
    "KeyB": 5,                      // B
    "KeyC": 6,                      // C
    "KeyD": 7,                      // D
    "KeyE": 8,                      // E
    "KeyF": 9,                      // F
    "KeyG": 10,                     // G
    "KeyH": 11,                     // H 
    "KeyI": 12,                     // I
    "KeyJ": 13,                     // J
    "KeyK": 14,                     // K
    "KeyL": 15,                     // L
    "KeyM": 16,                     // M
    "KeyN": 17,                     // N
    "KeyO": 18,                     // O
    "KeyP": 19,                     // P
    "KeyQ": 20,                     // Q
    "KeyR": 21,                     // R
    "KeyS": 22,                     // S
    "KeyT": 23,                     // T
    "KeyU": 24,                     // U
    "KeyV": 25,                     // V
    "KeyW": 26,                     // W
    "KeyX": 27,                     // X
    "KeyY": 28,                     // Y
    "KeyZ": 29,                     // Z
    "Digit1": 30,                   // 1 and !
    "Digit2": 31,                   // 2 and @
    "Digit3": 32,                   // 3 and #
    "Digit4": 33,                   // 4 and $
    "Digit5": 34,                   // 5 and %
    "Digit6": 35,                   // 6 and ^
    "Digit7": 36,                   // 7 and &
    "Digit8": 37,                   // 8 and *
    "Digit9": 38,                   // 9 and (
    "Digit0": 39,                   // 0 and )
    "Enter": 40,                    // Return (ENTER)
    "Escape": 41,                   // ESCAPE
    "Backspace": 42,                // DELETE (Backspace)
    "Tab": 43,                      // Tab
    "Space": 44,                    // Spacebar
    "Minus": 45,                    // - and _
    "Equal": 46,                    // = and +
    "LeftBrace": 47,                // [ and {
    "RightBrace": 48,               // ] and }
    "BackSlash": 49,                // \ and |
    "NonUSPound": 50,               // Non-US \# and ~
    "Semicolon": 51,                // ; and :
    "Quote": 52,                    // ' and "
    "GraveAccent": 53,              // Grave Accent and Tilde
    "Comma": 54,                    // , and <
    "Period": 55,                   // . and >
    "ForwardSlash": 56,             // / and ?
    "CapsLock": 57,                 // Caps Lock
    "F1": 58,                       // F1
    "F2": 59,                       // F2
    "F3": 60,                       // F3
    "F4": 61,                       // F4
    "F5": 62,                       // F5
    "F6": 63,                       // F6
    "F7": 64,                       // F7
    "F8": 65,                       // F8
    "F9": 66,                       // F9
    "F10": 67,                      // F10
    "F11": 68,                      // F11
    "F12": 69,                      // F12
    "PrintScreen": 70,              // Print Screen
    "ScrollLock": 71,               // Scroll Lock
    "Pause": 72,                    // Pause
    "Insert": 73,                   // Insert
    "Home": 74,                     // Home
    "PageUp": 75,                   // Page Up
    "Delete": 76,                   // Delete Forward
    "End": 77,                      // End
    "PageDown": 78,                 // Page Down
    "Right": 79,                    // Right Arrow
    "Left": 80,                     // Left Arrow
    "Down": 81,                     // Down Arrow
    "Up": 82,                       // Up Arrow
    "KeypadNumLock": 83,            // Keypad Num Lock and Clear
    "KeypadDivide": 84,             // Keypad /
    "KeypadMultiply": 85,           // Keypad *
    "KeypadSubtract": 86,           // Keypad -
    "KeypadAdd": 87,                // Keypad +
    "KeypadEnter": 88,              // Keypad ENTER
    "Keypad1": 89,                  // Keypad 1 and End
    "Keypad2": 90,                  // Keypad 2 and Down Arrow
    "Keypad3": 91,                  // Keypad 3 and PageDn
    "Keypad4": 92,                  // Keypad 4 and Left Arrow
    "Keypad5": 93,                  // Keypad 5
    "Keypad6": 94,                  // Keypad 6 and Right Arrow
    "Keypad7": 95,                  // Keypad 7 and Home
    "Keypad8": 96,                  // Keypad 8 and Up Arrow
    "Keypad9": 97,                  // Keypad 9 and PageUp
    "Keypad0": 98,                  // Keypad 0 and Insert
    "KeypadPeriod": 99,             // Keypad . and Delete
    "NonUSBackSlash": 100,          // Non-US \ and |
    "Application": 101,             // Application
    "Power": 102,                   // Power
    "KeypadEqual": 103,             // Keypad =
    "F13": 104,                     // F13
    "F14": 105,                     // F14
    "F15": 106,                     // F15
    "F16": 107,                     // F16
    "F17": 108,                     // F17
    "F18": 109,                     // F18
    "F19": 110,                     // F19
    "F20": 111,                     // F20
    "F21": 112,                     // F21
    "F22": 113,                     // F22
    "F23": 114,                     // F23
    "F24": 115,                     // F24
    "Execute": 116,                 // Execute
    "Help": 117,                    // Help
    "Menu": 118,                    // Menu
    "Select": 119,                  // Select
    "Stop": 120,                    // Stop
    "Again": 121,                   // Again
    "Undo": 122,                    // Undo
    "Cut": 123,                     // Cut
    "Copy": 124,                    // Copy
    "Paste": 125,                   // Paste
    "Find": 126,                    // Find
    "Mute": 127,                    // Mute
    "VolumeUp": 128,                // Volume Up
    "VolumeDown": 129,              // Volume Down
    "LockingCapsLock": 130,         // Locking Caps Lock
    "LockingNumLock": 131,          // Locking Num Lock
    "LockingScrollLock": 132,       // Locking Scroll Lock
    "KeypadComma": 133,             // Keypad Comma
    "KeypadEqualSign": 134,         // Keypad Equal Sign
    "International1": 135,          // International1
    "International2": 136,          // International2
    "International3": 137,          // International3
    "International4": 138,          // International4
    "International5": 139,          // International5
    "International6": 140,          // International6
    "International7": 141,          // International7
    "International8": 142,          // International8
    "International9": 143,          // International9
    "Lang1": 144,                   // LANG1
    "Lang2": 145,                   // LANG2
    "Lang3": 146,                   // LANG3
    "Lang4": 147,                   // LANG4
    "Lang5": 148,                   // LANG5
    "Lang6": 149,                   // LANG6
    "Lang7": 150,                   // LANG7
    "Lang8": 151,                   // LANG8
    "Lang9": 152,                   // LANG9
    "AlternateErase": 153,          // Alternate Erase
    "SysReq": 154,                  // SysReq/Attention
    "Cancel": 155,                  // Cancel
    "Clear": 156,                   // Clear
    "Prior": 157,                   // Prior
    "Return": 158,                  // Return
    "Separator": 159,               // Separator
    "Out": 160,                     // Out
    "Oper": 161,                    // Oper
    "ClearAgain": 162,              // Clear/Again
    "CrSel": 163,                   // CrSel/Props
    "ExSel": 164,                   // ExSel
    "Keypad00": 176,                // Keypad 00
    "Keypad000": 177,               // Keypad 000
    "ThousandsSeparator": 178,      // Thousands Separator
    "DecimalSeparator": 179,        // Decimal Separator
    "CurrencyUnit": 180,            // Currency Unit
    "CurrencySubUnit": 181,         // Currency Sub-unit
    "KeypadLeftParen": 182,         // Keypad (
    "KeypadRightParen": 183,        // Keypad )
    "KeypadLeftBrace": 184,         // Keypad {
    "KeypadRightBrace": 185,        // Keypad }
    "KeypadTab": 186,               // Keypad Tab
    "KeypadBackspace": 187,         // Keypad Backspace
    "KeypadA": 188,                 // Keypad A
    "KeypadB": 189,                 // Keypad B
    "KeypadC": 190,                 // Keypad C
    "KeypadD": 191,                 // Keypad D
    "KeypadE": 192,                 // Keypad E
    "KeypadF": 193,                 // Keypad F
    "KeypadXOR": 194,               // Keypad XOR
    "KeypadCaret": 195,             // Keypad ^
    "KeypadPercent": 196,           // Keypad %
    "KeypadLessThan": 197,          // Keypad <
    "KeypadGreaterThan": 198,       // Keypad >
    "KeypadAmpersand": 199,         // Keypad &
    "KeypadDoubleAmpersand": 200,   // Keypad &&
    "KeypadBar": 201,               // Keypad |
    "KeypadDoubleBar": 202,         // Keypad ||
    "KeypadColon": 203,             // Keypad :
    "KeypadPound": 204,             // Keypad \#
    "KeypadSpace": 205,             // Keypad Space
    "KeypadAt": 206,                // Keypad @
    "KeypadExclamation": 207,       // Keypad !
    "KeypadMemoryStore": 208,       // Keypad Memory Store
    "KeypadMemoryRecall": 209,      // Keypad Memory Recall
    "KeypadMemoryClear": 210,       // Keypad Memory Clear
    "KeypadMemoryAdd": 211,         // Keypad Memory Add
    "KeypadMemorySubtract": 212,    // Keypad Memory Subtract
    "KeypadMemoryMultiply": 213,    // Keypad Memory Multiply
    "KeypadMemoryDivide": 214,      // Keypad Memory Divide
    "KeypadPlusMinus": 215,         // Keypad +/-
    "KeypadClear": 216,             // Keypad Clear
    "KeypadClearEntry": 217,        // Keypad Clear Entry
    "KeypadBinary": 218,            // Keypad Binary
    "KeypadOctal": 219,             // Keypad Octal
    "KeypadDecimal": 220,           // Keypad Decimal
    "KeypadHexadecimal": 221,       // Keypad Hexadecimal
    "ControlLeft": 224,             // Left Control
    "ShiftLeft": 225,               // Left Shift
    "AltLeft": 226,                 // Left Alt
    "ControlRight": 228,            // Right Control
    "ShiftRight": 229,              // Right Shift
    "AltRight": 230,                // Right Alt
};

export function getKeyCode(event: KeyboardEvent): number {
    const keyCode = keyCodes[event.code];
    if (keyCode == null) {
        console.error("unknown key code:", event.code);
        return 0;
    }
    return keyCode;
}
