#include "interrupt.h"

/** halGpioExtIntEnable - Configure external interrupt
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

void (*ext_int[2])(void);
ISR(INT0_vect)
{
    ext_int[0];
}

ISR(INT1_vect)
{
    ext_int[1];
}

int halGpioExtIntConnect(uint8_t pin_no, void *isr)
{
    if(pin_no == 0 || pin_no == 1)
        ext_int[pin_no] = isr;
}

/** halGpioExtIntEnable - Enable external interrupt
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


/** halGpioExtIntEnable - Enable external interrupt
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
