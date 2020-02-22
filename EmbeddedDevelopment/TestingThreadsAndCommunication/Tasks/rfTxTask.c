#include <stdlib.h>
#include <unistd.h>

/* TI Drivers */
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driverlib Header files */
#include DeviceFamily_constructPath(driverlib/rf_prop_mailbox.h)

/* Board Header files */
#include "Board.h"
#include "smartrf_settings/smartrf_settings.h"
//#include <DataStructures/llMessage.h>
#include <DataStructures/ComQueue.h>
#include "taskDefinitions.h"

#include "mqueue.h"


/***** Defines *****/

/* Do power measurement */
//#define POWER_MEASUREMENT

/* Packet TX Configuration */
#define PAYLOAD_LENGTH      30
#ifdef POWER_MEASUREMENT
#define PACKET_INTERVAL     5  /* For power measurement set packet interval to 5s */
#else
#define PACKET_INTERVAL     500000  /* Set packet interval to 500000us or 500ms */
#endif

/***** Prototypes *****/

/***** Variable declarations *****/
static RF_Object rfObject;
static RF_Handle rfHandle;

static uint8_t packet[PAYLOAD_LENGTH];
static uint16_t seqNumber;

/***** Function definitions *****/


void *txTask(UArg *arg0)
{
    //Configuration

    //UART_Handle uart = (UART_Handle)arg0;

    RF_Params rfParams;
    RF_Params_init(&rfParams);

    GPIO_setConfig(Board_GPIO_LED1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /* Turn off user LED */
    GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);


    RF_cmdPropTx.pktLen = PAYLOAD_LENGTH;
    RF_cmdPropTx.pPkt = packet;
    RF_cmdPropTx.startTrigger.triggerType = TRIG_NOW;

    rfHandle = RF_open(&rfObject, &RF_prop, (RF_RadioSetup*)&RF_cmdPropRadioDivSetup, &rfParams);

    /* Set the frequency */
    RF_postCmd(rfHandle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);
    bool state = false;

    mqd_t tQm = NULL;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = MAX_LENGTH;
    attr.mq_curmsgs = 0;
    tQm = mq_open(sendQueue, O_CREAT | O_RDONLY, 0644, &attr);

    ssize_t bytes_read;

    char messageReceived[MAX_LENGTH];

    while(1)
    {
        /* Create packet with incrementing sequence number and random payload */
//        packet[0] = (uint8_t)(seqNumber >> 8);
//        packet[1] = (uint8_t)(seqNumber++);
//        uint8_t i;
//        for (i = 2; i < PAYLOAD_LENGTH; i++)
//        {
//            packet[i] = (rand() % 50) + 48 ;
//        }

//        UART_read(uart, messageReceived, sizeof(messageReceived));
        bytes_read = mq_receive(tQm, (char *)packet, MAX_LENGTH, NULL);

        if(bytes_read)
        //if(true)
        {

        /* Send packet */
        RF_EventMask terminationReason =
        RF_runCmd(rfHandle, (RF_Op*)&RF_cmdPropTx, RF_PriorityNormal, NULL, 0);

        switch(terminationReason)
        {
            case RF_EventLastCmdDone:
                // A stand-alone radio operation command or the last radio
                // operation command in a chain finished.
                break;
            case RF_EventCmdCancelled:
                // Command cancelled before it was started; it can be caused
            // by RF_cancelCmd() or RF_flushCmd().
                break;
            case RF_EventCmdAborted:
                // Abrupt command termination caused by RF_cancelCmd() or
                // RF_flushCmd().
                break;
            case RF_EventCmdStopped:
                // Graceful command termination caused by RF_cancelCmd() or
                // RF_flushCmd().
                break;
            default:
                // Uncaught error event
                while(1);
        }

        uint32_t cmdStatus = ((volatile RF_Op*)&RF_cmdPropTx)->status;
        switch(cmdStatus)
        {
            case PROP_DONE_OK:
                // Packet transmitted successfully
                break;
            case PROP_DONE_STOPPED:
                // received CMD_STOP while transmitting packet and finished
                // transmitting packet
                break;
            case PROP_DONE_ABORT:
                // Received CMD_ABORT while transmitting packet
                break;
            case PROP_ERROR_PAR:
                // Observed illegal parameter
                break;
            case PROP_ERROR_NO_SETUP:
                // Command sent without setting up the radio in a supported
                // mode using CMD_PROP_RADIO_SETUP or CMD_RADIO_SETUP
                break;
            case PROP_ERROR_NO_FS:
                // Command sent without the synthesizer being programmed
                break;
            case PROP_ERROR_TXUNF:
                // TX underflow observed during operation
                break;
            default:
                // Uncaught error event - these could come from the
                // pool of states defined in rf_mailbox.h
                while(1);
        }

//        GPIO_write(Board_GPIO_LED1, state);
//        if(state)
//        {
//            state = false;
//        }
//        else
//        {
//            state = true;
//        }
        /* Power down the radio */
        RF_yield(rfHandle);

        #ifdef POWER_MEASUREMENT
                /* Sleep for PACKET_INTERVAL s */
                sleep(PACKET_INTERVAL);
        #else
                /* Sleep for PACKET_INTERVAL us */
                usleep(PACKET_INTERVAL);
        #endif
        }
        else
        {
            usleep(PACKET_INTERVAL);
        }
    }
}
