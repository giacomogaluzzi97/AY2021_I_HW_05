/* ======================================== */
/* ======== ACCELEROMETER DRIVER H ======== */
/* ======================================== */

#ifndef Accelerometer_Driver_H
    #define Accelerometer_Driver_H

    #include "Global.h"
    
    // Initialisation function
    void InitAll();
    
    // Accelerometer configuration function
    void LIS3DH_InitRegister();
    
    // Record frequency in EEPROM function
    void UpdateMemory ();
    
    // Frequency option function
    void FreqOption();
    
    // Data collection from LIS3DH function
    XYZData DataFromAccelerometer();          
    
    // Data preparation from raw data function
    XYZData DataConversion(XYZData raw_data);
    
    // Buffer filling function
    void BufferFiller (XYZData conv_data);
    
    // Microcontroller functions (memory management, freq change, data acquisition and preparation)
    void MicroManager();
    
#endif    

/* [] END OF FILE */
