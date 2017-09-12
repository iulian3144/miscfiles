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

void halGpioInit(GPIO_TypeDef *GPIOx, GPIO_PIN_CONF_T *gpio_pin_conf);

uint8_t halGpioRead(GPIO_TypeDef *GPIOx, uint8_t pin_no);

void halGpioWrite(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t val);

void halGpioIntConfig(GPIO_TypeDef *GPIOx, uint8_t pin_no);

void halGpioIntEnable(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t irq);

void halGpioIntDisable(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t irq);
