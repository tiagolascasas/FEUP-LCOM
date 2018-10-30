/*macros for lab4*/

/*interruptions-related codes*/
#define MOUSE_IRQ 12
#define HOOK_ID_3 3

/*ports*/
#define CTRL_REG 0x64
#define IN_BUF_MOUSE 0x60
#define OUT_BUF_MOUSE 0x60

/*kbc commands*/
#define ENABLE_MOUSE 0xA8
#define DISABLE_MOUSE 0xA7
#define WRITE_BYTE_TO_MOUSE 0xD4
#define READ_BYTE 0x20
#define WRITE_BYTE 0x60

/*ps2 commands*/
#define STREAM_MODE 0xEA
#define DISABLE_DATA_REP 0xF5
#define ENABLE_DATA_REP 0xF4
#define STATUS_REQUEST 0xE9

/*acknowledgement codes*/
#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC

/*miscellaneous*/
#define NO_ARG 0x0
#define SIGN_1 0xff00
#define SIGN_0 0x0
#define READ_ERROR 0x0

/*states*/
#define INIT 0

