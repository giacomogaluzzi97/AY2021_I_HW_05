/* ======================================== */
/* ================ MAIN H ================ */
/* ======================================== */

#include "Global.h"
#include "I2C_Interface.h"
#include "InterruptRoutines.h"
#include "Accelerometer_Driver.h"


int main(void)
{
    CyGlobalIntEnable;      // Enable global interrupts
    InitAll();              // Initialization of UART, EEPROM, I2C PERIPH., ISR and LIS3DH

    // DataBuffer
    DataBuffer[0]               = HEADER;
    DataBuffer[BUFFER_SIZE-1]   = TAIL;
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
