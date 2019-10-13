#include "pin_mux_config.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "interrupt.h"
#include "rom_map.h"
#include "pin.h"
#include "prcm.h"
#include "gpio.h"
#include "utils.h"

extern uVectorEntry __vector_table;


static void boardInit()
{
	MAP_IntVTableBaseSet((unsigned long)&__vector_table);
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);
    PRCMCC3200MCUInit();
}

void main()
{
    unsigned long ulCount = 8000000;
    boardInit();
    PinMuxConfig();
    GPIOPinWrite(GPIOA1_BASE, 0X0E, 0X00);
    
    while (1)
    {   
        if (GPIOPinRead(GPIOA1_BASE, 0X20))
        {
            if (ulCount > 1000000)
              ulCount -= 1000000;
        }
        
        if (GPIOPinRead(GPIOA2_BASE, 0X40))
        {
            if (ulCount < 8000000)
              ulCount += 1000000;
        }
      
        GPIOPinWrite(GPIOA1_BASE, 0X02, 0X02);
        UtilsDelay(ulCount);
        GPIOPinWrite(GPIOA1_BASE, 0X02, 0X00);
        GPIOPinWrite(GPIOA1_BASE, 0X04, 0X04);
        UtilsDelay(ulCount);
        GPIOPinWrite(GPIOA1_BASE, 0X04, 0X00);
        GPIOPinWrite(GPIOA1_BASE, 0X08, 0X08);
        UtilsDelay(ulCount);
        GPIOPinWrite(GPIOA1_BASE, 0X08, 0X00);
    }
}