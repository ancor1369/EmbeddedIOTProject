#include <stdint.h>

struct packet
{
    uint8_t dstAddr; //Destination Address, This is the address of this device
    uint8_t sdrAddr; //Sender Address, Address needed to identify who to send answer to
    uint8_t total; //Total of packages coming from the sender
    uint8_t seqn;   //Current number of package to assamble the whole package
    uint8_t payload[124]; //payload containing a fraction of the message
};
typedef struct packet packet_t;
