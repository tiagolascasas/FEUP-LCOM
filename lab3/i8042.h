//Macros for lab3

#define BIT(n) (0x01<<(n))

#define TIMER0_IRQ                0    /**< @brief Timer 0 IRQ line */

#define KBD_IRQ 1
#define HOOK_ID_2 2

#define STAT_REG 0x64
#define IN_BUF 0x20
#define OUT_BUF 0x60

#define PAR BIT(7)
#define TIMEOUT BIT(6)
#define IBF BIT(1)
#define OBF BIT(0)

#define TWO_BYTE_SCAN_CODE 0xE0
#define ESC_BREAK_CODE 0x81

#define RETRIES 5

#define SET_LEDS 0xED

#define LED_2_SCROLL 0
#define LED_1_CAPS 2
#define LED_0_NUM 1

#define DELAY_US 20000
//#define DELAY_US 200000
