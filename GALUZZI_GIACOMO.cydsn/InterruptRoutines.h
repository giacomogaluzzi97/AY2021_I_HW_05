/* ======================================== */
/* ================ ISR H ================= */
/* ======================================== */

// interrupt routine on push button controlling the change in 
// frequency (--> isr_ChangeFreq on TopDesign [Debouncer_PushButton])

#ifndef Interrupt_Routines_H
    #define Interrupt_Routines_H
    
    #include "Global.h"
    
    _Bool   ButtonPressed;              // Flag for the button IF pressed
    uint8_t ButtonCounter = 0b0001;     // Counter to change frequency
    
    CY_ISR_PROTO(PUSH_BUTTON_ISR);
    
#endif

/* [] END OF FILE */
