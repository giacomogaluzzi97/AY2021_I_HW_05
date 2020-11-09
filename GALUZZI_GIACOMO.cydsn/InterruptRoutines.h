/* ======================================== */
/* ================ ISR H ================= */
/* ======================================== */

// interrupt routine on push button controlling the change in 
// frequency (--> isr_ChangeFreq on TopDesign [Debouncer_PushButton])

#ifndef Interrupt_Routines_H
    #define Interrupt_Routines_H
    
    #include "Global.h"
    
    CY_ISR_PROTO(PUSH_BUTTON_ISR);
    
#endif

/* [] END OF FILE */
