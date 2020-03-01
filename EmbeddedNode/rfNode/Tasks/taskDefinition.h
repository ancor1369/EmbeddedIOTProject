#include <xdc/std.h>


#define rfTXQueue "TXQueue"
#define rfRXQueue "RXQueue"
#define MSGLENGHT 128
#define uartMSGLENGT 512

/*
 * @name : radioTaskFunction
 * @Purpose: Manage the ussage of the radio interface of the microcontroller
 * @return: Void
 *
 */

void radioTaskFunction(UArg *arg0, UArg *arg1);



/*
 * @name: serialReceive
 * @Purpose: This task takes any message that comes over the serial interface
 * and sends it to the RF_TX_Queue to send once those are ready to send
 * @return: void
 *
 */

void *serialReceive(UArg *arg0, UArg *arg1);



/*
 * @name: serialSend
 * @Purpose: This task takes the messages that arrive on the RF_RX_Queue and passes
 * them to the serial interface so that they can be used for further
 * processing.
 * @return: void
 *
 */
void serialSend(UArg *arg0, UArg *arg1);
