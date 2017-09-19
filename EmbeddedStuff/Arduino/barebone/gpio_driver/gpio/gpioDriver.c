#include <stdint.h>
#include "hal_gpio_driver.h"

/**
 * @brief set GPIO pin mode
 * @param GPIOx GPIO port to configure
 * @param pin_no GPIO pin to configure
 * @param mode mode (GPIO_PIN_OUTPUT_LOW, GPIO_PIN_OUTPUT_HIGH)
 * @return 0 if pin is succesfully configured; -1 otherwise
 */
int halGpioPinMode
(
    GPIO_TypeDef *GPIOx,
    uint8_t pin_no,
    uint8_t mode
)
{
    if(mode != GPIO_PIN_OUTPUT_LOW &&
       mode != GPIO_PIN_OUTPUT_HIGH)
        return -1;

    GPIOx->DDR |= (mode << pin_no);

    return 0;
}

/**
 * @brief initialize GPIO pin
 * @param GPIOx GPIO port to configure
 * @param gpio_pin_conf GPIO pin to configure
 * @return 0 if pin was successfully initialized; -1 otherwise
 */
int halGpioPinInit
(
    GPIO_TypeDef *GPIOx,
    GPIO_PIN_CONF_T *gpio_pin_conf
)
{
    return halGpioPinMode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode);
}

/**
 * @brief read GPIO pin
 * @param GPIOx GPIO port to configure
 * @param pin_no GPIO pin to read from
 * @return GPIO pin state; -1 if wrong pin number is specified
 */
int halGpioPinRead(GPIO_TypeDef *GPIOx, uint8_t pin_no)
{
    if(pin_no > 7 || (pin_no >=7 && GPIOx == GPIO_PORTC))
        return -1;

    return ((GPIOx->IDR >> pin_no) & 1);
}

/**
 * @brief write to GPIO pin
 * @param GPIOx GPIO port to configure
 * @param gpio_pin_conf GPIO pin to write to
 * @return 0 if operation is successful; -1 if wrong pin number is specified
 */
int halGpioPinWrite
(
    GPIO_TypeDef *GPIOx,
    uint8_t pin_no,
    uint8_t val
)
{
    /* if pin_no is greater than 7 (8 pins/port) or greater than 6 in case of
     * PORTC, we should return (-1) as an error */
    if(pin_no > 7 || (pin_no > 6 && GPIOx == GPIO_PORTC))
        return -1;
    if(val)
        GPIOx->ODR |= (1 << pin_no);
    else
        GPIOx->ODR &= ~(1 << pin_no);
}

/**
 * @brief toggle a GPIO pin
 * @param GPIOx GPIO port to configure
 * @param gpio_pin_conf GPIO pin to toggle
 * @return 0 if operation is successful -1 if wrong pin number is specified
 */
int halGpioPinToggle
(
    GPIO_TypeDef *GPIOx,
    uint8_t pin_no
)
{
    if(pin_no > 7 || (pin_no >=7 && GPIOx == GPIO_PORTC))
        return -1;

    GPIOx->ODR ^= (1 << pin_no);

    return 0;
}
