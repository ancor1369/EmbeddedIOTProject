#include <ti/sysbios/knl/Queue.h>



struct MsgBuffer
{
    Queue_Elem elem;
    char buffer[128];
};

typedef struct MsgBuffer msgBuffer_t;
