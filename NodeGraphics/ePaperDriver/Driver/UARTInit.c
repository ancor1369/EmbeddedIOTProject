#include "UARTInit.h"

void UART_Init(void)
{
    UART_Handle uart;
    UART_Params uartParams;

    UART_Init();

    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    //UART_enableInterrupt(eUSCI_UART_ConfigV1, mask)

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL)
    {
       /* UART_open() failed */
        while (1);
    }


}
