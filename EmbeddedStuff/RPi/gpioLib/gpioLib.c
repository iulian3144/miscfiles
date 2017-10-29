#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/mman.h>


#include "gpioLib.h"

uint32_t *GPIO_MAP_BASE = NULL;
uint32_t GPIO_OFFSET = GPIO_BASE;

STATUS gpioLibInit()
{
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0)
    {
        write(1, "[/dev/gpiomem] ", 15);
        if((fd = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0)
        {
            perror("error opening '/dev/mem' or '/dev/gpiomem'!\n");
            return ERROR;
        }
        /* if we open /dev/gpiomem instead of /dev/mem, then the GPIO offset is
         * 0x200000 */
        GPIO_OFFSET = 0x200000;
    }

    GPIO_MAP_BASE = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_OFFSET);

    if(GPIO_MAP_BASE == MAP_FAILED)
    {
        perror("mmap (GPIO) failed!\n");
        return ERROR;
    }

    return OK;
}

STATUS gpioPinSetAltFunc(uint32_t pin_no, GPIO_ALT_FUNC altfunc)
{
    if(pin_no > 53)
        return ERROR;

    /* select corresponding GPFSELn register */
    uint32_t *GPFSELx = (GPIO_MAP_BASE + (pin_no / 10));
    /* reset corresponding bits to 0 before setting them */
    *GPFSELx &= ~(7 << (3 * pin_no));
    *GPFSELx |= altfunc << (3 * pin_no);

    return OK;
}

STATUS gpioPinSetDir(uint32_t pin_no, uint32_t dir)
{
    return gpioPinSetAltFunc(pin_no, dir);
}

STATUS gpioPinSetValue(uint32_t pin_no, uint8_t val)
{
    uint32_t *GPIO_SET = GPIO_MAP_BASE + 7 + pin_no/32;
    uint32_t *GPIO_CLR = GPIO_MAP_BASE + 10 + pin_no/32;

    if(val)
        *GPIO_SET |= 1 << pin_no;
    else
        *GPIO_CLR |= 1 << pin_no;

    return OK;
}

STATUS gpioPinRead(uint32_t pin_no, uint8_t *val)
{
    uint32_t *GPIO_LEV = GPIO_MAP_BASE + 13 + pin_no/32;

    *val = (uint8_t)((*GPIO_LEV >> pin_no) & 1);

    return OK;
}
