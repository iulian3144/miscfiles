#include <avr/io.h>

/* ***** clock selection *****
 *                  CS02    CS01    CS00
 * no prescaling:      0       0       1
 * clkIO/8      :      0       1       0
 * clkIO/64     :      0       1       1
 * clkIO/256    :      1       0       0
 * clkIO/1024   :      1       0       1
 */
#define CLK_NO_PRESCALING   (_BV(CS00))
#define CLK_PRESCALE_8      (_BV(CS01))
#define CLK_PRESCALE_64     (_BV(CS01) | _BV(CS00))
#define CLK_PRESCALE_256    (_BV(CS02))
#define CLK_PRESCALE_1024   (_BV(CS02) | _BV(CS00))

int initialize_pwm(uint8_t duty_cycle0, uint8_t duty_cycle1);

int main(void)
{
    // set duty cycle to 7%
    int duty_cycle0 = 255*7/100;
    int duty_cycle1 = 255*7/100;
    initialize_pwm(duty_cycle0, duty_cycle1);

    // set pin 6 and 5 as outputs
    DDRD |= _BV(DDD6) | _BV(DDD5);
    while(1)
    {

    }
}


int initialize_pwm(uint8_t duty_cycle0, uint8_t duty_cycle1)
{
    // Fast PWM mode for OC0A
    TCCR0A |= _BV(COM0A1) | _BV(COM0A0);

    // Fast PWM mode for OC0B
    TCCR0A |= _BV(COM0B1) | _BV(COM0B0);

    // set Waveform Generation mode to Fast PWM with TOP = 0xFF
    TCCR0A |= _BV(WGM01) | _BV(WGM01);

    /* clock selection
     * pwm frequency can be calculated with the following formula:
     * f = f_clkIO / (N * 256)
     * f_clkIO is the clock frequency
     * N represents the prescale factor (1, 8, 64, 256 or 1024)
     */
    TCCR0B |= CLK_PRESCALE_256;

    /* set duty cycle
     * duty cycle should be between 5% and 10%
     */
    // pin OC0A; arduino pin 6
    OCR0A = 255 - duty_cycle0;

    // pin 0C0B; arduino pin 5
    OCR0B = 255 - duty_cycle1;

    return 0;
}