#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <symbol.h>

#define BLINK_DELAY_MS 500

volatile unsigned int var1 = 0;
// volatile unsigned int var2 = 0;

ISR(TIMER0_OVF_vect)
{
    ++var1;
}

int main (void)
{
    // cli();
    // set clock source to clk/1024 (prescaler)
    TCCR0B = (1<<2)|1;
    TCNT0 = 0x0;
    TIMSK0 = _BV(TOIE0);
    sei();
    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    while (1)
    {
        if(var1 >= 61)
        {
            PORTB ^= _BV(PORTB5);
            var1 = 0;
        }
    }
}
