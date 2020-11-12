/* ======================================== */
/* ======== ACCELEROMETER DRIVER C ======== */
/* ======================================== */

#include "Accelerometer_Driver.h"
#include "I2C_Interface.h"
#include "InterruptRoutines.h"
#include "UART_Debug.h"


// Variables for register configuration
uint8_t CurrentFreq;                                    // Sampling frequency variable

// Variable to use if debugging with UART
    //char message[50] = {'\0'};                        // Message for debugging purpose
    //uint8_t isConnected;                              // Variable to check if the device is connected 

/*------------------------------------------------------------------------------------------*/
// Initialisation function 
// [PASS 1 in main.c]

void InitAll()
{
    UART_Debug_Start();                                 // UART             Start
    EEPROM_Start();                                     // EEPROM           Start
    I2C_Peripheral_Start();                             // I2C Peripheral   Start
    ButtonPressed=0;                                    // Button flag      Init = 0
    isr_ChangeFreq_StartEx(PUSH_BUTTON_ISR);            // ISR              Start
    CurrentFreq=EEPROM_ReadByte(EEPROM_ADDRESS);        // Sampling freq    Init from EEPROM
    if(CurrentFreq>6 || CurrentFreq<1) CurrentFreq = 1; // Sampling freq    Check if there are no values allowed in EEPROM
    LIS3DH_InitRegister();    // [*]                    // Accelerometer    Init registers    
}   
/*------------------------------------------------------------------------------------------*/
// Accelerometer configuration
// [*] see above

void LIS3DH_InitRegister()
{
    // Brief code to check if the device is connected
        // isConnected = I2C_Peripheral_IsDeviceConnected(LIS3DH_DEVICE_ADDRESS);
        // sprintf(message, "is the device connected? %d -> connected = 1, unconnected = 0.\r\n", isConnected);
        // UART_Debug_PutString(message);
    
    // Initialisation of CTRL_REG1
    ErrorCode error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG1_ADDRESS,
                                                   LIS3DH_CTRL_REG1_INIT | (CurrentFreq<<4));
    
    if(error == ERROR) UART_Debug_PutString("Error in LIS3DH CTRL REG 1 configuration\r\n");
    
    // Initialisation of CTRL_REG4
    error = I2C_Peripheral_WriteRegister          (LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG4_ADDRESS,
                                                   LIS3DH_CTRL_REG4_INIT);
    
    if(error == ERROR) UART_Debug_PutString("Error in LIS3DH CTRL REG 4 configuration\r\n");
    
}   
/*------------------------------------------------------------------------------------------*/
// Record frequency in EEPROM
// [**] see below    

void UpdateMemory()
{
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(CurrentFreq, EEPROM_ADDRESS);
    
    ErrorCode error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG1_ADDRESS,
                                                   LIS3DH_CTRL_REG1_INIT | (CurrentFreq<<4));
    
    if(error == ERROR) UART_Debug_PutString("Error in update memory\r\n");
}  
/*------------------------------------------------------------------------------------------*/
// Frequency option
// [PASS 1 in MicroManager function (at the end of this file)]

void FreqOption()
{
    if(ButtonPressed)
    {
        ButtonPressed = 0;
        UpdateMemory(); // [**] see above
        // FOR DEBUGGING ONLY: add here the switch below
    }
}  

//      switch(CurrentFreq)
//      {
//            case(1):
//                    UART_Debug_PutString("Sampling Frequency = 1Hz\r\n");
//                    break;
//            case(2):
//                    UART_Debug_PutString("Sampling Frequency = 10Hz\r\n");
//                    break;
//            case(3):
//                    UART_Debug_PutString("Sampling Frequency = 25Hz\r\n");
//                    break;
//            case(4):
//                    UART_Debug_PutString("Sampling Frequency = 50Hz\r\n");
//                    break;
//            case(5):
//                    UART_Debug_PutString("Sampling Frequency = 100Hz\r\n");
//                    break;
//            case(6):
//                    UART_Debug_PutString("Sampling Frequency = 200Hz\r\n");
//                    break;
//            default:
//                    break;
//      }
/*------------------------------------------------------------------------------------------*/
// Data collection from LIS3DH
// [PASS 2 in MicroManager function (at the end of this file)]

XYZData DataFromAccelerometer()
{
    uint8_t MultiReadData[NUMBER_OF_DATA_REG];      // Vector for multi read
    XYZData raw_data;                               // Structure for data casting
    
    ErrorCode error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                       LIS3DH_OUT_X_L,
                                                       NUMBER_OF_DATA_REG,
                                                       MultiReadData);
    
    if(error == ERROR) UART_Debug_PutString("Error data acquisition\r\n");
    
    raw_data.X = (int16)(((MultiReadData[0])|(MultiReadData[1]<<8))>>4); 
    raw_data.Y = (int16)(((MultiReadData[2])|(MultiReadData[3]<<8))>>4);
    raw_data.Z = (int16)(((MultiReadData[4])|(MultiReadData[5]<<8))>>4);
    
    return(raw_data);
}    
/*------------------------------------------------------------------------------------------*/
// Data preparation from raw data
// [PASS 3 in MicroManager function (at the end of this file)]

XYZData DataConversion(XYZData raw_data)
{   
    XYZData conv_data;

    // 1000 is the multipling factor to save 3 digits after the comma
    conv_data.X = (int16)(1000*(raw_data.X*MG_TO_G*LIS3DH_SENSITIVITY*GRAVITY));
    conv_data.Y = (int16)(1000*(raw_data.Y*MG_TO_G*LIS3DH_SENSITIVITY*GRAVITY));
    conv_data.Z = (int16)(1000*(raw_data.Z*MG_TO_G*LIS3DH_SENSITIVITY*GRAVITY));
    
    return(conv_data);
}    
/*------------------------------------------------------------------------------------------*/
// Data preparation from raw data
// [PASS 4 in MicroManager function (at the end of this file)]

void BufferFiller (XYZData conv_data)
{
    uint8_t DataBuffer[BUFFER_SIZE];
    
    DataBuffer[0] = HEADER;
    DataBuffer[1] = (uint8_t)(conv_data.X & 0xFF);
    DataBuffer[2] = (uint8_t)(conv_data.X >> 8);
    DataBuffer[1] = (uint8_t)(conv_data.Y & 0xFF);
    DataBuffer[2] = (uint8_t)(conv_data.Y >> 8);
    DataBuffer[1] = (uint8_t)(conv_data.Z & 0xFF);
    DataBuffer[2] = (uint8_t)(conv_data.Z >> 8);
    DataBuffer[BUFFER_SIZE-1] = TAIL;
    
    UART_Debug_PutArray(DataBuffer, BUFFER_SIZE);
}
/*------------------------------------------------------------------------------------------*/
// Microcontroller functions (memory management, freq change, data acquisition and preparation)
// [PASS 2 in main.c, inside for(;;)]

void MicroManager()
{   
    // Frequency control
    FreqOption();                         //[see code above]
    
    // Status Register reading
    uint8_t Status_Reg;   
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_STATUS_REG_ADDRESS,
                                &Status_Reg);
    
    // Data Acquisition, Conversion and Buffer creation only if new data are available
    if(Status_Reg & LIS3DH_STATUS_REG_NEW_DATA_SET)
    {
        BufferFiller(DataConversion(DataFromAccelerometer()));      
        // a. raw data from accelerometer   [see code above]
        // b. data conversion               [see code above]
        // c. buffer preparation            [see code above]
    }    
}

/* [] END OF FILE */
