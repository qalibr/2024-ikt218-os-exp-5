/* Source: UiA, Per-Arne Lecture/Assignment Assets

    And,    
    UiA IKT218 2024V
    Group-5 
*/

#include "io/keyboard.h"

bool isCapsLockEnabled = false;

const char largeAscii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\016', '?', 'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\034', '?',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', ',', '.', '/', '?', '?', '?', ' '
};

const char smallAscii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\016', '?', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\034', '?',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', '?', '?', '?', ' '
};

char ScancodeToAscii(uint8_t *scanCode) {
    uint8_t val = *scanCode;

    switch (val)
    {
    case 1:
        /* ESC */
        return 0;
    case 14:
        /* BACK */
        return 0;
    case 15:
        return 0;
    case 28:
        /* ENTER */
        return 2;
    case 29:
        return 0;
    case 42:
        isCapsLockEnabled = !isCapsLockEnabled;
        return 0;
    case 54:
        isCapsLockEnabled = !isCapsLockEnabled;
        return 0;
    case 56:
        return 0;
    case 57:
        /* SPACE */
        return 3;
    case 58:
        return isCapsLockEnabled = !isCapsLockEnabled;
    case 72:
        /* UP */
        return 0;
    case 75:
        /* LEFT */
        return 0;
    case 77:
        /* RIGHT */
        return 0;
    case 80:
        /* DOWN */
        return 0;
    case 170:
        isCapsLockEnabled = !isCapsLockEnabled;
        return 0;
    default:
        if (val < 57) {
            int b = val;
            char c;
            if (isCapsLockEnabled) {
                c = largeAscii[val];
            } else {
                c = smallAscii[val];
            }

            return c;
        } else {
            return 0;
        }
    }
}

void KeyboardIrqHandler(Registers_t *r, void *context) {
    uint8_t scancode = InPortByte(0x60);
    char ascii = ScancodeToAscii(&scancode);
    // printf("%c", ascii);

    switch (ascii)
    {
    case 'c':
    case 'C':
        MusicRestart();
        break;
    case 'v':
    case 'V':
        MusicNext();
        break;
    case 'x':
    case 'X':
        MusicContinue();
        break;
    default:
        break;
    }
}

void InitKeyboard() {
    RegisterIrqHandler(IRQ1, &KeyboardIrqHandler, NULL);
}