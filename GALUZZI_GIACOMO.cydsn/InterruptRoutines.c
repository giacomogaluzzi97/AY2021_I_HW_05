/* ======================================== */
/* ================ ISR H ================= */
/* ======================================== */

#include "InterruptRoutines.h"

CY_ISR(PUSH_BUTTON_ISR)
{
    
    
    CurrentFreq ++;
    
    if(CurrentFreq > 6) CurrentFreq = 1;
    
    ButtonPressed = 1;
}    

/* [] END OF FILE */
