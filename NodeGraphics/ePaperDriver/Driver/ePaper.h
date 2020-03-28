
#include "GPIOInit.h"
#include "SPIinit.h"


#define HRES 128
#define VRES 296

extern uint8_t GLOBAL_framebuffer[VRES][HRES / 8];

void initEPD(void);

void updateEPD(void);

void turnWhite(void);

void turnBlack(void);

void turnYellow(void);
