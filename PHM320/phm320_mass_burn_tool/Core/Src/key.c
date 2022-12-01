#include "stm32f1xx_hal.h"
#include "delay.h"
#include <stdbool.h>

typedef enum {
    KEY_INITIAL = 0,
    KEY_PRESSED,
    KEY_RELEASED
} key_state_t;

#define MAX_CHECK_COUNT         (10)

bool check_key_pressed(void)
{
    static key_state_t key_state = KEY_INITIAL;
    static uint32_t count = 0;
    GPIO_PinState key_value;
    bool ret = false;

    key_value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    switch (key_state)
    {
    case KEY_INITIAL/* constant-expression */:
        /* code */
        if (0 == key_value) {
            count++;
            key_state = KEY_PRESSED;
        }
        break;
    case KEY_PRESSED:
        if (0 == key_value) {
            count++;
            if (MAX_CHECK_COUNT < count) {
                count = 0;
                ret = true;
                key_state = KEY_INITIAL;
            }
        } else {
            key_state = KEY_INITIAL;
            count = 0;
        }
        break;
    default:
        break;
    }

    return ret;
}
