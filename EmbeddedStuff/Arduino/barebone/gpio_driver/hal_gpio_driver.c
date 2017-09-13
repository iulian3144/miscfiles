#include <stdint.h>
#include "hal_gpio_driver.h"

/*
 * halGpioPinMode - set GPIO pin mode
 * GPIO_TypeDef *GPIOx: GPIO port to configure
 * uint8_t pin_no: GPIO pin to configure
 * uint8_t mode: mode (GPIO_PIN_OUTPUT_LOW, GPIO_PIN_OUTPUT_HIGH)
 *
 * RETURNS: 0 if pin is succesfully configure
            -1 otherwise
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

/* halGpioPinInit - initialize GPIO pin
 * GPIO_TypeDef *GPIOx: GPIO port to configure
 * GPIO_PIN_CONF_T *gpio_pin_conf: GPIO pin to configure
 *
 * RETURNS: 0 if pin was successfully initialized
            -1 otherwise
 */
int halGpioPinInit
(
    GPIO_TypeDef *GPIOx,
    GPIO_PIN_CONF_T *gpio_pin_conf
)
{
    return halGpioPinMode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode);
}

/*
 * halGpioPinRead - read GPIO pin
 * GPIO_TypeDef *GPIOx: GPIO port to configure
 * uint8_t pin_no: GPIO pin to read from
 *
 * RETURNS: GPIO pin state
 *          -1 if wrong pin number is specified
 */
int halGpioPinRead(GPIO_TypeDef *GPIOx, uint8_t pin_no)
{
    if(pin_no > 7 || (pin_no >=7 && GPIOx == GPIO_PORTC))
        return -1;

    return ((GPIOx->IDR >> pin_no) & 1);
}

/* halGpioPinWrite - write to GPIO pin
 * GPIO_TypeDef *GPIOx: GPIO port to configure
 * GPIO_PIN_CONF_T *gpio_pin_conf: GPIO pin to write to
 *
 * RETURNS: 0 if operation is successful
            -1 if wrong pin number is specified
 */
int halGpioPinWrite
(
    GPIO_TypeDef *GPIOx,
    uint8_t pin_no,
    uint8_t val
)
{
    if(pin_no > 7 || (pin_no >=7 && GPIOx == GPIO_PORTC))
        return -1;
    if(val)
        GPIOx->ODR |= (1 << pin_no);
    else
        GPIOx->ODR &= ~(1 << pin_no);
}

/* halGpioPinToggle - toggle a GPIO pin
 * GPIO_TypeDef *GPIOx: GPIO port to configure
 * GPIO_PIN_CONF_T *gpio_pin_conf: GPIO pin to toggle
 *
 * RETURNS: 0 if operation is successful
            -1 if wrong pin number is specified
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


/* halGpioExtIntEnable - Configure external interrupt
 * uint8_t pin_no: pin number (PD2, PD3)
 * int_edge_sel_t edge_sel: edge selection
 * RETURNS:
 *      0 if successful
 *      -1 if pin_no is not PD2 or PD3
 */
int halGpioExtIntConfig
(
    uint8_t pin_no,
    int_edge_sel_t edge_sel
)
{
    switch(pin_no)
    {
        case PD2:
            EICRA |= (edge_sel << 0);
        case PD3:
            EICRA |= (edge_sel << 2);
        default:
            return -1;
    }
    return 0;
}


/* halGpioExtIntEnable - Enable external interrupt
 * uint8_t pin_no: pin number (PD2, PD3)
 * RETURNS:
 *      0 if successful
 *      -1 if pin_no is not PD2 or PD3
 */
int halGpioExtIntEnable(uint8_t pin_no)
{
    switch(pin_no)
    {
        case PD2:
            EIMSK |= (1 << INT0);
            break;
        case PD3:
            EIMSK |= (1 << INT1);
            break;
        default:
            return -1;
    }
    return 0;
}


/* halGpioExtIntEnable - Enable external interrupt
 * uint8_t pin_no: pin number (PD2, PD3)
 * RETURNS:
 *      0 if successful
 *      -1 if pin_no is not PD2 or PD3
 */
int halGpioExtIntDisable(uint8_t pin_no)
{
    switch(pin_no)
    {
        case PD2:
            EIMSK &= ~(1 << INT0);
            break;
        case PD3:
            EIMSK &= ~(1 << INT1);
            break;
        default:
            return -1;
    }
    return 0;
}
