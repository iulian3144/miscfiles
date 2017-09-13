/* hal_gpio_driver.h - ATmega328p GPIO driver header file */

#include "atmega328p.h"

#define GPIO_PIN_INPUT_MODE                             ((uint8_t)0x00)
#define GPIO_PIN_OUTPUT_MODE                            ((uint8_t)0x01)

#define GPIO_PIN_OUTPUT_LOW                             ((uint8_t)0x00)
#define GPIO_PIN_OUTPUT_HIGH                            ((uint8_t)0x01)

typedef struct
{
    uint8_t pin;    /* GPIO pin number */
    uint8_t mode;   /* Operating mode (input/output) */
} GPIO_PIN_CONF_T;

typedef enum
{
    INT_LOW,
    INT_RISING_FALLING_EDGE,
    INT_FALLING_EDGE,
    INT_RISING_EDGE
} int_edge_sel_t;

int halGpioPinInit(GPIO_TypeDef *GPIOx, GPIO_PIN_CONF_T *gpio_pin_conf);

int halGpioPinRead(GPIO_TypeDef *GPIOx, uint8_t pin_no);

int halGpioPinWrite(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t val);

int halGpioPinToggle(GPIO_TypeDef *GPIOx, uint8_t pin_no);

int halGpioExtIntConfig(uint8_t pin_no, int_edge_sel_t edge_sel);

int halGpioExtIntEnable(uint8_t pin_no);

int halGpioExtIntDisable(uint8_t pin_no);
