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
    void DataFromAccelerometer();          
    
    // Data preparation from raw data function
    void DataConversion(void);
    
    // Buffer filling function
    void BufferFiller (void);
    
    // Microcontroller functions (memory management, freq change, data acquisition and preparation)
    void MicroManager();
    
    
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
