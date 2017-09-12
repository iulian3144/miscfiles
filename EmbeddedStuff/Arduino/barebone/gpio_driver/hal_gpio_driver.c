#include <stdint.h>
#include "hal_gpio_driver.h"

halGpioPinMode(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t mode)
{
    GPIOx->DDR |= (mode << pin_no);
}

void halGpioInit(GPIO_TypeDef *GPIOx, GPIO_PIN_CONF_T *gpio_pin_conf)
{
    halGpioPinMode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode);
}

uint8_t halGpioPinRead(GPIO_TypeDef *GPIOx, uint8_t pin_no)
{
    return ((GPIOx->IDR >> pin_no) & 1);
}

void halGpioPinWrite(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t val)
{
    if(val)
        GPIOx->ODR |= (1 << pin_no);
    else
        GPIOx->ODR &= ~(1 << pin_no);
}

void halGpioIntConfig(GPIO_TypeDef *GPIOx, uint8_t pin_no, int_edge_sel_t edge_sel)
{
    EICRA |= (1 << edge_sel);
}

void halGpioIntEnable(GPIO_TypeDef *GPIOx, uint8_t pin_no, uint8_t irq)
{
    if(GPIOx == PORTD)
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
                return;
        }
    }
}
