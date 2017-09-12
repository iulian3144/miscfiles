/* atmega328p.h - ATmega328p definition header file */

#include <avr/io.h>
#include <inttypes.h>


/*************************** BEGIN GPIO ***************************/
typedef struct
{
    volatile uint8_t IDR;       /* Input Data Register */
    volatile uint8_t DDR;       /* Data Direction Register */
    volatile uint8_t ODR;       /* Output Data Register */
} GPIO_TypeDef;

#define PORTB_BASE      (__SFR_OFFSET + 0x3)
#define PORTC_BASE      (__SFR_OFFSET + 0x6)
#define PORTD_BASE      (__SFR_OFFSET + 0x9)

#define PORTB           ((GPIO_TypeDef *) PORTB_BASE)
#define PORTC           ((GPIO_TypeDef *) PORTC_BASE)
#define PORTD           ((GPIO_TypeDef *) PORTD_BASE)

/**************************** END GPIO ****************************/
