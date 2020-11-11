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
    
    // Microcontroller functions (memory management, freq change, data acquisition and preparation)
    void MicroManager();
    
    // Frequency option function
    void FreqOption();
    
    // Record frequency in EEPROM function
    void UpdateMemory ();
    
    // Data collection from LIS3DH function
    XYZData DataFromAccelerometer();          
    
    // Data preparation from raw data function
    XYZData DataConversion(XYZData raw_data);
    
    // Buffer filling function
    void BufferFiller (XYZData conv_data);
    
    
    /*----------------------------------------------------
    The structure of these functions in the main.c is:
    
        1. InitAll
                1a. LIS3DH_InitRegister
    
        2. MicroManager
                2a. FreqOption
                        2aI. UpdateMemory
                2b. DataFromAccelerometer
                2c. DataConversion
                2d. BufferFiller                        
    ----------------------------------------------------*/
    
#endif    

/* [] END OF FILE */
