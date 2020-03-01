#include <stdint.h>

struct packet
{
    uint8_t addr[8];
    uint8_t payload[128];
};

typedef struct packet packet_t;
