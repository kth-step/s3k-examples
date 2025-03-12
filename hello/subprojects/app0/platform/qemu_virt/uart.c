#include "serio/uart/ns16550a.h"

SERIOFILE _uartfile = SERIO_UART_NS16550A(0x10000000);

SERIOFILE *const _serio_out = &_uartfile;
SERIOFILE *const _serio_in = &_uartfile;
