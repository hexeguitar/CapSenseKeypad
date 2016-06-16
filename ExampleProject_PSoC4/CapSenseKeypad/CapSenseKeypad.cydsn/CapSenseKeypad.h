#if !defined(CAPSENSE_KEYPAD_H)
#define CAPSENSE_KEYPAD_H

#include <cytypes.h>

typedef  enum
{
    KEYPAD_1,
    KEYPAD_2,
    KEYPAD_3,
    KEYPAD_4,
    KEYPAD_5,
    KEYPAD_6,
    KEYPAD_7,
    KEYPAD_8,
    KEYPAD_SETUP,
    KEYPAD_9,
    KEYPAD_0,
    KEYPAD_DOT,
    KEYPAD_LEFT,
    KEYPAD_DOWN,
    KEYPAD_UP,
    KEYPAD_RIGHT,
    KEYPAD_NONE
} keypadKeys_t;
    

void keypadInit(void);
uint16_t MBR3Keypad_getKey(void);
uint32_t keypadHandle(void);

#endif
