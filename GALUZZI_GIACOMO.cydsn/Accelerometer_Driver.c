/* ======================================== */
/* ======== ACCELEROMETER DRIVER C ======== */
/* ======================================== */

#include "Accelerometer_Driver.h"
#include "I2C_Interface.h"
#include "InterruptRoutines.h"

uint8_t CurrentFreq = LIS3DH_CTRL_REG1_INIT;    // The first frequency is 1 Hz


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
    LIS3DH_Start();                              // Accelerometer    Start    
}    
/*------------------------------------------------------------------------------------------*/
// Accelerometer configuration

void LIS3DH_Start()
{
    // Initialisation of CTRL_REG1
    ErrorCode error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                   LIS3DH_CTRL_REG1_ADDRESS,
                                                   LIS3DH_CTRL_REG1_INIT);
    
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


/* [] END OF FILE */
