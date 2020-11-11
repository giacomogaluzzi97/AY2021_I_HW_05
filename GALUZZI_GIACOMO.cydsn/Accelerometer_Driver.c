/* ======================================== */
/* ======== ACCELEROMETER DRIVER C ======== */
/* ======================================== */

#include "Accelerometer_Driver.h"
#include "I2C_Interface.h"
#include "InterruptRoutines.h"


// Variables for register configuration
uint8_t CurrentFreq = (LIS3DH_CTRL_REG1_INIT | 0b00010000);    // The first frequency is 1 Hz


/*------------------------------------------------------------------------------------------*/
// Initialisation function

void InitAll()
{
    UART_Debug_Start();                          // UART             Start
    EEPROM_Start();                              // EEPROM           Start
    I2C_Peripheral_Start();                      // I2C Peripheral   Start
    ButtonPressed=0;                             // Button flag      Init = 0
    isr_ChangeFreq_StartEx(PUSH_BUTTON_ISR);     // ISR              Start
    CurrentFreq=EEPROM_ReadByte(EEPROM_ADDRESS); // Working freq     Init from EEPROM
    ButtonCounter=(CurrentFreq)>>4;              // Button counter   Init from EEPROM (ODR)                         
    LIS3DH_InitRegister();                       // Accelerometer    Init registers    
}   
/*------------------------------------------------------------------------------------------*/
// Accelerometer configuration

void LIS3DH_InitRegister()
{
    // Initialisation of CTRL_REG1
    ErrorCode error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG1_ADDRESS,
                                                   CurrentFreq);
    
    if(error == ERROR) UART_Debug_PutString("Error in LIS3DH configuration\r\n");
    
    // Initialisation of CTRL_REG4
    error = I2C_Peripheral_WriteRegister          (LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG4_ADDRESS,
                                                   LIS3DH_CTRL_REG4_INIT);
    
    if(error == ERROR) UART_Debug_PutString("Error in LIS3DH configuration\r\n");
    
}    
/*------------------------------------------------------------------------------------------*/
// Record frequency in EEPROM
                
void UpdateMemory()
{
    CurrentFreq = ((ButtonCounter)<<4 | LIS3DH_CTRL_REG1_INIT);
    
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(CurrentFreq, EEPROM_ADDRESS);
    
    ErrorCode error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG1_ADDRESS,
                                                   CurrentFreq);
    
    if(error == ERROR) UART_Debug_PutString("Error in update memory\r\n");
}    
/*------------------------------------------------------------------------------------------*/
// Frequency option

void FreqOption()
{
    if(ButtonPressed)
    {
        if(ButtonCounter >= 0b0111 | ButtonCounter == 0b0001)
        {
            ButtonCounter = 0b0001;
            UpdateMemory();
            UART_Debug_PutString("Sampling Frequency = 1Hz");
            ButtonPressed = 0;
        }
        else 
        {
            switch(ButtonCounter)
            {
                case (0b0010):
                        UpdateMemory();
                        UART_Debug_PutString("Sampling Frequency = 10Hz");
                        ButtonPressed = 0;
                        break;
                case (0b0011):
                        UpdateMemory();
                        UART_Debug_PutString("Sampling Frequency = 25Hz");
                        ButtonPressed = 0;
                        break;
                case (0b0100):
                        UpdateMemory();
                        UART_Debug_PutString("Sampling Frequency = 50Hz");
                        ButtonPressed = 0;
                        break;
                case (0b0101):
                        UpdateMemory();
                        UART_Debug_PutString("Sampling Frequency = 100Hz");
                        ButtonPressed = 0;
                        break;
                case (0b0110):
                        UpdateMemory();
                        UART_Debug_PutString("Sampling Frequency = 200Hz");
                        ButtonPressed = 0;
                        break;
                default:
                        break;
            }
        }
    }
}
/*------------------------------------------------------------------------------------------*/
// Data collection from LIS3DH

XYZData DataFromAccelerometer()
{
    uint8_t MultiReadData[NUMBER_OF_DATA_REG];      // Vector for multi read
    XYZData raw_data;                               // Structure for data casting
    
    ErrorCode error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                       LIS3DH_OUT_X_L,
                                                       NUMBER_OF_DATA_REG,
                                                       MultiReadData);
    
    if(error == ERROR) UART_Debug_PutString("Error data acquisition\r\n");
    
    raw_data.X = (int16)(MultiReadData[0] |(MultiReadData[1])<<8)>>4; 
    raw_data.Y = (int16)(MultiReadData[2] |(MultiReadData[3])<<8)>>4;
    raw_data.Z = (int16)(MultiReadData[4] |(MultiReadData[5])<<8)>>4;
    
    return(raw_data);
}    
/*------------------------------------------------------------------------------------------*/
// Data preparation from raw data

XYZData DataConversion(XYZData raw_data)
{   
    XYZData conv_data;

    // 1000 is the multipling factor to save 3 digits after the comma
    conv_data.X = 1000*(raw_data.X*MG_TO_G*LIS3DH_SENSITIVITY*GRAVITY);
    conv_data.Y = 1000*(raw_data.Y*MG_TO_G*LIS3DH_SENSITIVITY*GRAVITY);
    conv_data.Z = 1000*(raw_data.Z*MG_TO_G*LIS3DH_SENSITIVITY*GRAVITY);
    
    return(conv_data);
}    
/*------------------------------------------------------------------------------------------*/
// Data preparation from raw data

void BufferFiller (XYZData conv_data)
{
    uint8_t DataBuffer[BUFFER_SIZE];
    
    DataBuffer[0] = HEADER;
    DataBuffer[1] = (uint8_t)(conv_data.X & 0xFF);
    DataBuffer[2] = (uint8_t)(conv_data.X >> 8) & 0xFF;
    DataBuffer[1] = (uint8_t)(conv_data.Y & 0xFF);
    DataBuffer[2] = (uint8_t)(conv_data.Y >> 8) & 0xFF;
    DataBuffer[1] = (uint8_t)(conv_data.Z & 0xFF);
    DataBuffer[2] = (uint8_t)(conv_data.Z >> 8) & 0xFF;
    DataBuffer[BUFFER_SIZE-1] = TAIL;
    
    UART_Debug_PutArray(DataBuffer, BUFFER_SIZE);
}





/* [] END OF FILE */
