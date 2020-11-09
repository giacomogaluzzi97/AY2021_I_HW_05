/* ======================================== */
/* ======== ACCELEROMETER DRIVER H ======== */
/* ======================================== */

#ifndef Accelerometer_Driver_H
    #define Accelerometer_Driver_H

    #include "Global.h"
    
    // Initialisation function
    void InitAll();
    
    // Accelerometer configuration
    void LIS3DH_Start();
    
    // Record frequency in EEPROM
    void UpdateMemory ();
    
    // Frequency option
    void FreqOption();
    
    
    
#endif    

/* [] END OF FILE */
