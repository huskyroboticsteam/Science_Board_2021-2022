/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/* ========================================
 * Copyright Wade Maxfield, 2020
 * All Rights Reserved
 * LICENSED SOFTWARE.
 *  Under the GPL v3 license
 * This license does not override previous licenses
 * Some information may be Proprietary to 
 * Cypress (http://www.cypress.com) for their
 * PSoC 5LP®--Cypress Semiconductor and
 * only usable on their devices.
 * PROPERTY OF Wade Maxfield.
 * Commercial license available
 * ========================================
*/
#include "Milliseconds.h"

volatile uint32 milliseconds;
//volatile uint16 ms,seconds, minutes, hours;
//volatile int16 MsLedCounter;

CY_ISR(MillisecondInterrupt) {
    milliseconds++;
    
}

void init_milliseconds() {
    milliseconds = 0;
    isr_1ms_StartEx(MillisecondInterrupt);
    
}

/* [] END OF FILE */
