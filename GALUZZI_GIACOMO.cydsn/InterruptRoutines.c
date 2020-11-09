/* ======================================== */
/* ================ ISR H ================= */
/* ======================================== */

#include "InterruptRoutines.h"

CY_ISR(PUSH_BUTTON_ISR)
{
    ButtonPressed = 1;
    ButtonCounter ++;
}    

/* [] END OF FILE */
