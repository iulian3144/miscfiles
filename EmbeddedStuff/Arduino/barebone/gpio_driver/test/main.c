#include "hal_gpio_driver.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t var = 0;
GPIO_PIN_CONF_T pinConf;

ISR(TIMER0_OVF_vect)
{
    ++var;
    // halGpioPinToggle(GPIO_PORTB, 5);
}

// extern __vector_17 = (int)isr_17;

int main()
{
    TCCR0B = (1<<2)|1;
    TCNT0 = 0x0;
    TIMSK0 = _BV(TOIE0);
    sei();
    pinConf.pin = 5;
    pinConf.mode = GPIO_PIN_OUTPUT_MODE;
    halGpioPinInit(GPIO_PORTB, &pinConf);
    while(1)
    {
        if(var >= 61)
        {
            halGpioPinToggle(GPIO_PORTB, pinConf.pin);
            var = 0;
        }
        // _delay_ms(100);
    }
    return 0;
}
