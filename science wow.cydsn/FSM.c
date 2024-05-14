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

#include "FSM.h"
#include "main.h"

uint8_t state;
uint8_t mode;

void UART_FSM(char rxByte) {
    switch (state) {
        case (IDLE):
            switch (rxByte) {
                case 'L':
                    setFSMMode(LAZY_SUSAN_MODE);
                    setFSMState(READ_DATA);
                    Print("Setting Lazy Susan Position...\r\n");
                    break;
                case 'S':
                    setFSMMode(SCI_SERVO_MODE);
                    setFSMState(READ_DATA);
                    break;
                case 'C':
                    setFSMMode(CONT_SERVO_MODE);
                    setFSMState(READ_DATA);
                    break;
                default:
                    setFSMState(DEFAULT_UART);
            }
        case (READ_DATA):
        
        case (SET_LAZY_SUSAN):
        
        case (SET_SCI_SERVO):
        
        case (SET_CONT_SERVO_POWER):
        
        case (DEFAULT_UART):
            DebugPrint(rxByte);
            break;
        default:
            setFSMState(IDLE);
            setFSMMode(MICHAEL_MODE);
    }
}

void setFSMState(uint8_t next_state) {
    state = next_state;
}

void setFSMMode(uint8_t next_mode) {
    mode = next_mode;
}

/* [] END OF FILE */
