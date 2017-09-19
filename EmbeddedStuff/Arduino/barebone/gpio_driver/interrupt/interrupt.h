

int halGpioExtIntConfig(uint8_t pin_no, int_edge_sel_t edge_sel);

int halGpioExtIntConnect(uint8_t pin_no, void *isr);

int halGpioExtIntEnable(uint8_t pin_no);

int halGpioExtIntDisable(uint8_t pin_no);

typedef enum
{
    INT_LOW, ///< interrupt triggers on low edge
    INT_RISING_FALLING_EDGE, ///< interrupt triggers on rising or falling edge
    INT_FALLING_EDGE, ///< interrupt triggers on falling edge
    INT_RISING_EDGE ///< interrupt triggers on rising edge
} int_edge_sel_t;
