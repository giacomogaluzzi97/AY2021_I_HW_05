/* ======================================== */
/* ======== ACCELEROMETER DRIVER H ======== */
/* ======================================== */

#ifndef Accelerometer_Driver_H
    #define Accelerometer_Driver_H

    #include "Global.h"
    
    // Initialisation function
    void InitAll();
    
    // Accelerometer configuration
    void LIS3DH_InitRegister();
    
    // Record frequency in EEPROM
    void UpdateMemory ();
    
    // Frequency option
    void FreqOption();
    
    // Data collection from LIS3DH
    XYZ_RawData DataFromAccelerometer();          
    
    // Data preparation from raw data
    XYZ_ConvData DataConversion(XYZ_RawData raw_data);
    
#endif    

/* [] END OF FILE */
