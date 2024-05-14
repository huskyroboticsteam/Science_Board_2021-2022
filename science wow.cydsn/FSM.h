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

#include <stdint.h>

#ifndef __FSM__
#define __FSM__
    
/*
  Using modes with states so that the FSM will not
  need a separate path for building the data, but 
  instead can read data generally then use the mode
  to figure out how to apply it.
*/

// STATE DECLARATIONS
#define IDLE                    (uint8_t) 0x0
#define READ_DATA               (uint8_t) 0x1
#define SET_LAZY_SUSAN          (uint8_t) 0x2
#define SET_SCI_SERVO           (uint8_t) 0x3
#define SET_CONT_SERVO_POWER    (uint8_t) 0x4
#define DEFAULT_UART            (uint8_t) 0x5
    
// MODE DECLARATIONS
#define MICHAEL_MODE            (uint8_t) 0x0 // default mode
#define LAZY_SUSAN_MODE         (uint8_t) 0x1
#define SCI_SERVO_MODE          (uint8_t) 0x2
#define CONT_SERVO_MODE         (uint8_t) 0x3
    
void UART_FSM(char rxByte);

void setFSMState(uint8_t next_state);

void setFSMMode(uint8_t next_mode);

#endif // __FSM__

/* [] END OF FILE */
