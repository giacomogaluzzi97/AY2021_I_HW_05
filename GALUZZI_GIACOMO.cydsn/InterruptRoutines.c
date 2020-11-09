/* ======================================== */
/* ================ ISR H ================= */
/* ======================================== */

#include "InterruptRoutines.h"

CY_ISR(PUSH_BUTTON_ISR)
{
    ButtonPressed = 1;
}    

/* [] END OF FILE */
