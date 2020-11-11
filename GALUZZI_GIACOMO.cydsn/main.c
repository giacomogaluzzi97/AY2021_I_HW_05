/* ======================================== */
/* ================ MAIN H ================ */
/* ======================================== */

#include "I2C_Interface.h"
#include "InterruptRoutines.h"
#include "Accelerometer_Driver.h"


int main(void)
{
    CyGlobalIntEnable;      // Enable global interrupts 
    InitAll();              // Initialization of UART, EEPROM, I2C PERIPH., ISR and LIS3DH
    
    for(;;)
    {
        MicroManager();     // Microcontroller working (see in Accelerometer_Driver.c)
    }
}

/* [] END OF FILE */
