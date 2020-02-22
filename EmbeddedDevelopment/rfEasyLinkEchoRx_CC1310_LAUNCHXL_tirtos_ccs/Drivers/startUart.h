#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/*
 * @brief   Funcion to initialize the UART port according to requirement by the application
 *
 * @return A handle that can be used to be passed as arguments to functions that will
 *          use the initialized UART port.
 *
 */
extern uint8_t startUART(UART_Handle *uart);
