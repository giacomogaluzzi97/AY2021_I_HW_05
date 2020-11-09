/* ======================================== */
/* =============== GLOBAL H =============== */
/* ======================================== */

#ifndef Global_H
    #define Global_H
    
    #include "cytypes.h"
    #include "project.h"
    #include "stdio.h"
    #include "UART_Debug.h"
    
    
    // Accelerometer register adresses
    #define LIS3DH_WHO_AM_I_REG_ADDRESS     0x0F        // Address of the WHO AM I register
    #define LIS3DH_DEVICE_ADDRESS           0x18        // 7-bit I2C address of the slave device
    #define LIS3DH_CTRL_REG1_ADDRESS        0x20        // Address of the Control register 1 (to set ODR[3:0] for the frequency)
    #define LIS3DH_CTRL_REG4_ADDRESS        0x23        // Address of the Control register 4 (to set FS[1:0] for the Full-scale) --> sensitivity is related to the FS (DATASHEET p.10)
    #define LIS3DH_STATUS_REG_ADDRESS       0x27        // Address of the Status register
    
    // Accelerometer data adresses
    #define LIS3DH_OUT_X_L                  0x28        // Address of the lower  output of  X coordinate --> useful when a multi read is used
    #define LIS3DH_OUT_X_H                  0x29        // Address of the higher output of  X coordinate
    #define LIS3DH_OUT_Y_L                  0x2A        // Address of the lower  output of  Y coordinate
    #define LIS3DH_OUT_Y_H                  0x2B        // Address of the higher output of  Y coordinate
    #define LIS3DH_OUT_Z_L                  0x2C        // Address of the lower  output of  Z coordinate
    #define LIS3DH_OUT_Z_H                  0x2D        // Address of the higher output of  Z coordinate
    #define LIS3DH_OUT_X_L                  0x28        // Address of the lower  output of  Z coordinate
    #define NUMBER_OF_DATA_REG              6           // Useful for multi read
    
    // Accelerometer register init
    #define LIS3DH_CTRL_REG1_INIT           0x17        // X,Y,Z-axis enable
    #define LIS3DH_CTRL_REG4_INIT           0x18        // FS = +-4g, HR mode
    
    // Accelerometer working info
    #define LIS3DH_SENSITIVITY              2           // Datasheet p.10   --> unit: mg/digit
    #define GRAVITY                         9.81        // Gravity acc      --> unit: m/(s^2)
    #define LIS3DH_FS                       8*GRAVITY   // from -4g to +4g  --> unit: g
    #define LIS3DH_HIGH_RESOLUTION          12          // 12 bit data output
    
    // Accelerometer status reg mask
    #define LIS3DH_STATUS_REG_NEW_DATA_SET  0x08        // New set of data for X,Y,Z-axis
    #define LIS3DH_STATUS_REG_OVERRUN       0x80        // New set of data for X,Y,Z-axis OVERWRITTEN previous data
    
    // EEPROM
    #define EEPROM_ADDRESS                  0x00        // EEPROM address to preserve the frequency value
    
    // Buffer data
    #define HEADER                          0xA0
    #define TAIL                            0xC0
    #define BUFFER_SIZE                     1+LIS3DH_HIGH_RESOLUTION+1
    
    
    
    
    // Variables
    extern _Bool        ButtonPressed;                  // Flag for the interrupt
    extern uint8_t      CurrentFreq;                    // Working frequency of accelerometer
    
    
#endif

/* [] END OF FILE */
