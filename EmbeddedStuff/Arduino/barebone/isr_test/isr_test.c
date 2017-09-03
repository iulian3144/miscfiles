#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

/*
 * A global flag used to communicate between the Interrupt Service Routine
 * and the main program.  It has to be declared volatile or the compiler
 *  might optimize it out.
 */
volatile bool update = false;

/*
 * The interrupt service routine.  This is run whenever the interrupt
 * "TIMER1_OVF_vect" is triggered.  This is an interrupt that the ATmega328P
 * triggers whenever Timer 1 overflows past its maximum value.  It sets
 * the update flag to "true" to tell the main program that it needs to
 * do something.
 */
ISR(TIMER1_OVF_vect) {
    update = true;
}

int main(void) {

    // Set PORTB pins as output, but off
    DDRB = 0xFF;
    PORTB = 0x00;

    // Turn on timer with no prescaler on the clock for fastest
    // triggering of the interrupt service routine.
    TCCR1B |= _BV(CS10);
    TIMSK1 |= _BV(TOIE1);

    // Turn interrupts on.
    sei();

    for (;;)
    {
        // This turns interrupts off for the code inside it.  Probably
        // not needed here but it's good to know about.
        ATOMIC_BLOCK(ATOMIC_FORCEON)
        {
            // If the ISR has indicated we need to update the state
            // then run this block.
            if (update)
            {
                // Toggle the pins on PORTB on/off.
                PORTB ^= 0xFF;  // Toggle the pins on/off
                /*
                 * We reset the update flag to false to indicate that
                 * we are done.  This ensures that this block will not
                 * be executed until update is set to true again, which
                 * is only done by the interrupt service routine.
                 */
                update = false;
            }
        }
    }
}