#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <util/delay.h>

/* ***** clock selection *****
 *                  CS02    CS01    CS00
 * no prescaling:      0       0       1
 * clkIO/8      :      0       1       0
 * clkIO/64     :      0       1       1
 * clkIO/256    :      1       0       0
 * clkIO/1024   :      1       0       1
 */

#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "atmega328p");

const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
    { AVR_MCU_VCD_SYMBOL("TCNT0"), .what = (void*)&TCNT0 },
    { AVR_MCU_VCD_SYMBOL("DDRD"),  .what = (void*)&DDRD },
    { AVR_MCU_VCD_SYMBOL("TCCR0A"),  .what = (void*)&TCCR0A },
    { AVR_MCU_VCD_SYMBOL("TCCR0B"),  .what = (void*)&TCCR0B },
};

AVR_MCU_VCD_PORT_PIN('D', 5, "OC0B");
AVR_MCU_VCD_PORT_PIN('D', 6, "OC0A");
// AVR_MCU_VCD_PORT_PIN('D', 1, "PORTD1");
// AVR_MCU_VCD_PORT_PIN('D', 0, "PORTD0");

#define CLK_NO_PRESCALING   (_BV(CS00))
#define CLK_PRESCALE_8      (_BV(CS01))
#define CLK_PRESCALE_64     (_BV(CS01) | _BV(CS00))
#define CLK_PRESCALE_256    (_BV(CS02))
#define CLK_PRESCALE_1024   (_BV(CS02) | _BV(CS00))

/* Timer/Counter Mode of Operation | TOP  | Update of OCR0x at | TOV Flag Set on */
/*             Normal              | 0xFF |     Immediate      |  MAX   */
#define WGM_MODE0() { TCCR0A &= ~(_BV(WGM01) | _BV(WGM00)); TCCR0B &= ~_BV(WGM02);         }
/*       PWM, Phase Correct        | 0xFF |        TOP         | BOTTOM */
#define WGM_MODE1() { TCCR0A |=                          _BV(WGM00); }
/*               CTC               | OCRA |     Immediate      |  MAX   */
#define WGM_MODE2() { TCCR0A |=                  _BV(WGM01);              }
/*            Fast PWM             | 0xFF |      BOTTOM        |  MAX   */
#define WGM_MODE3() { TCCR0A |=                  _BV(WGM01) | _BV(WGM00); }
/*            Reserved             |  -   |         -          |   -    */
#define WGM_MODE4() { TCCR0B |= _BV(WGM02);                          }
/*       PWM, Phase Correct        | OCRA |        TOP         | BOTTOM */
#define WGM_MODE5() { TCCR0B |= _BV(WGM02); TCCR0A |=         _BV(WGM00); }
/*            Reserved             |  -   |         -          |   -    */
#define WGM_MODE6() { TCCR0B |= _BV(WGM02); TCCR0A |= _BV(WGM01);         }
/*            Fast PWM             | OCRA |      BOTTOM        |  TOP    */
#define WGM_MODE7() { TCCR0B |= _BV(WGM02); TCCR0A |= _BV(WGM01) | _BV(WGM00); }

int initialize_pwm(uint8_t duty_cycle0, uint8_t duty_cycle1);
int set_duty_cycle(uint8_t dc0, uint8_t dc1);

int main(void)
{
    // set duty cycle to 50/256
    int duty_cycle0 = 100;
    int duty_cycle1 = 63;
    initialize_pwm(duty_cycle0, duty_cycle1);

    // set pin 6 and 5 as outputs
    DDRD |= _BV(DDD6) | _BV(DDD5);
    _delay_ms(1000);
    while(1)
    {
        WGM_MODE0();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE1();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE2();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE3();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE4();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE5();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE6();
        _delay_ms(1000);
        WGM_MODE0();
        WGM_MODE7();
        _delay_ms(1000);
        return 0;
    }
}


int initialize_pwm(uint8_t duty_cycle0, uint8_t duty_cycle1)
{
    // OC0A - Phase Correct PWM Mode: Set OC0A when up counting
    TCCR0A |= _BV(COM0A1) /*| _BV(COM0A0)*/;

    // OC0B - Phase Correct PWM Mode: Set OC0B when up counting
    // TCCR0A |= _BV(COM0B1) /*| _BV(COM0B0)*/;

    // set Waveform Generation mode to Phase Correct PWM with TOP = 0xFF
    WGM_MODE1();

    /* clock selection
     * pwm frequency can be calculated with the following formula:
     * 1. Fast PWM mode
     *      f = f_clkIO / (N * 256)
     * 2. Phase-correct PWM mode
     *      f = f_clkIO / (N * 510)
     * f_clkIO = clock frequency
     * N represents the prescale factor (1, 8, 64, 256 or 1024)
     */
    /* set clock prescale */
    TCCR0B |= CLK_PRESCALE_256;

    /* set duty cycle
     * duty cycle should be between 5% and 10%
     *
     * pin OC0A - arduino pin 6 */
    OCR0A = duty_cycle0;

    /* pin 0C0B - arduino pin 5 */
    OCR0B = duty_cycle1;

    return 0;
}

int set_duty_cycle(uint8_t dc0, uint8_t dc1)
{
    /* pin OC0A - arduino pin 6 */
    OCR0A = dc0;

    /* pin 0C0B - arduino pin 5 */
    OCR0B = dc1;

    return 0;
}
