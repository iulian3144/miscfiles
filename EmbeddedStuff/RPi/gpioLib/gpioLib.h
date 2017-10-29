/* file: gpioLib.h
 * Raspberry Pi 3 GPIO library header file
 */

#define BCM2835_PBASE   0x3F000000 /* BCM2835 peripheral base */
#define GPIO_BASE       0x3F200000 /* GPIO base */

#define GPFSEL0             (GPIO_BASE + 0x00) /* GPIO Function Select 0 */
#define GPFSEL1             (GPIO_BASE + 0x04) /* GPIO Function Select 1 */
#define GPFSEL2             (GPIO_BASE + 0x08) /* GPIO Function Select 2 */
#define GPFSEL3             (GPIO_BASE + 0x0C) /* GPIO Function Select 3 */
#define GPFSEL4             (GPIO_BASE + 0x10) /* GPIO Function Select 4 */
#define GPFSEL5             (GPIO_BASE + 0x14) /* GPIO Function Select 5 */

#define GPSET0              (GPIO_BASE + 0x1C) /* GPIO Pin Output Set 0 */
#define GPSET1              (GPIO_BASE + 0x20) /* GPIO Pin Output Set 1 */

#define GPCLR0              (GPIO_BASE + 0x28) /* GPIO Pin Output Clear 0 */
#define GPCLR1              (GPIO_BASE + 0x2C) /* GPIO Pin Output Clear 1 */

#define GPLEV0              (GPIO_BASE + 0x34) /* GPIO Pin Level 0 */
#define GPLEV1              (GPIO_BASE + 0x38) /* GPIO Pin Level 1 */

#define GPEDS0              (GPIO_BASE + 0x40) /* GPIO Event Detect Status 0 */
#define GPEDS1              (GPIO_BASE + 0x44) /* GPIO Event Detect Status 1 */

#define GPREN0              (GPIO_BASE + 0x4C) /* GPIO Pin Rising Edge Detect Enable 0 */
#define GPREN1              (GPIO_BASE + 0x50) /* GPIO Pin Rising Edge Detect Enable 1 */

#define GPFEN0              (GPIO_BASE + 0x58) /* GPIO Pin Falling Edge Detect Enable 0 */
#define GPFEN1              (GPIO_BASE + 0x5C) /* GPIO Pin Falling Edge Detect Enable 1 */

#define GPHEN0              (GPIO_BASE + 0x64) /* GPIO Pin High Detect Enable 0 */
#define GPHEN1              (GPIO_BASE + 0x68) /* GPIO Pin High Detect Enable 1 */

#define GPLEN0              (GPIO_BASE + 0x70) /* GPIO Pin Low Detect Enable 0 */
#define GPLEN1              (GPIO_BASE + 0x74) /* GPIO Pin Low Detect Enable 1 */

#define GPAREN0             (GPIO_BASE + 0x7C) /* GPIO Pin Async. Rising Edge Detect 0 */
#define GPAREN1             (GPIO_BASE + 0x80) /* GPIO Pin Async. Rising Edge Detect 1 */

#define GPAFEN0             (GPIO_BASE + 0x88) /* GPIO Pin Async. Falling Edge Detect 0 */
#define GPAFEN1             (GPIO_BASE + 0x8C) /* GPIO Pin Async. Falling Edge Detect 1 */

#define GPPUD               (GPIO_BASE + 0x94) /* GPIO Pin Pull-up/down Enable */
#define GPPUDCLK0           (GPIO_BASE + 0x98) /* GPIO Pin Pull-up/down Enable Clock 0 */
#define GPPUDCLK1           (GPIO_BASE + 0x9C) /* GPIO Pin Pull-up/down Enable Clock 1 */


typedef enum
{
    GPIO_PIN_INPUT_MODE  = 0,
    GPIO_PIN_OUTPUT_MODE = 1,
    GPIO_ALT_FUNC0 = 4,
    GPIO_ALT_FUNC1 = 5,
    GPIO_ALT_FUNC2 = 6,
    GPIO_ALT_FUNC3 = 7,
    GPIO_ALT_FUNC4 = 3,
    GPIO_ALT_FUNC5 = 2
} GPIO_ALT_FUNC;

typedef enum
{

} GPIO_;

#define BLOCK_SIZE  4096
#define PAGE_SIZE   4096

typedef uint8_t BOOL;

typedef int STATUS;
#define ERROR  (-1)
#define OK     (0)

/** @brief Initialize GPIO library
 * @retval OK or ERROR if initializing fails
 */
STATUS gpioLibInit();

/** @brief Set GPIO pin alternate function.
 * For details please see \ref GPIO_ALT_FUNC
 * @param pin     : pin to configure
 * @param altfunc : select alternate function
 * @retval OK if pin value is valid
 *         ERROR otherwise
 */
STATUS gpioPinSetAltFunc(uint32_t pin_no, GPIO_ALT_FUNC altfunc);

STATUS gpioPinSetDir(uint32_t pin_no, uint32_t dir);

STATUS gpioPinSetValue(uint32_t pin_no, uint32_t val);

BOOL gpioPinRead(uint32_t pin_no);
