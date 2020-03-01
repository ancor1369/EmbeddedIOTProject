#include "startUart.h"
#include "Board.h"

uint8_t startUART(UART_Handle *uartPt)
{
    UART_Params uartParams;
    /* Call driver init functions */
    UART_init();
    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_TEXT;
    uartParams.readDataMode = UART_DATA_TEXT;
    uartParams.readReturnMode = UART_RETURN_NEWLINE;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    *uartPt = UART_open(Board_UART0, &uartParams);

    if (uartPt == NULL) {
        /* UART_open() failed so return 1*/
        return 1;
    }
    return 0;
}
