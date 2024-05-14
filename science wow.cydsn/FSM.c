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
#include "project.h"
#include <stdlib.h>
#include <stdint.h>

uint8_t state;
uint8_t mode;
int8_t pos;
uint32_t val;
uint8_t servoID;

void UART_FSM(char rxByte) {
    switch (state) {
        case (IDLE):
            switch (rxByte) {
                case 'l':
                    setFSMMode(LAZY_SUSAN_MODE);
                    setFSMState(READ_DATA);
                    PrintChar(rxByte);
                    Print("\r\n");
                    Print("Setting Lazy Susan...\r\n");
                    break;
                case 's':
                    setFSMMode(SCI_SERVO_MODE);
                    setFSMState(SERVO_SELECT);
                    PrintChar(rxByte);
                    Print("\r\n");
                    Print("Setting Servos...\r\n");
                    break;
                case 'c':
                    setFSMMode(CONT_SERVO_MODE);
                    setFSMState(SERVO_SELECT);
                    PrintChar(rxByte);
                    Print("\r\n");
                    Print("Setting Continuous Servos...\r\n");
                    break;
                default:
                    DebugPrint(rxByte);
            }
            break;
        case (READ_DATA):
            if (rxByte == '\r' || rxByte == '\n') {
                switch (mode) {
                    case LAZY_SUSAN_MODE:
                        setFSMState(SET_LAZY_SUSAN);
                        setFSMMode(MICHAEL_MODE);
                        Print("\r\n");
                        break;
                    case SCI_SERVO_MODE:
                        setFSMState(SET_SCI_SERVO);
                        setFSMMode(MICHAEL_MODE);
                        Print("\r\n");
                        break;
                    case CONT_SERVO_MODE:
                        setFSMState(SET_CONT_SERVO_POWER);
                        setFSMMode(MICHAEL_MODE);
                        Print("\r\n");
                        break;
                    default:
                        resetFSM();
                        DebugPrint(rxByte);
                }
            } else if (rxByte == '-') {
                if (!val) {
                    setSign(0);
                    PrintChar('-');
                } else {
                    setSign(1);
                    setVal(0);
                    Print("\r\nInvalid Value Entered. Try Again.\r\n");   
                }
            } else if (rxByte - 48 < 0 || rxByte - 48 > 9) {
                setSign(1);
                setVal(0);
                Print("\r\nInvalid Value Entered. Try Again.\r\n"); 
            } else {
                setVal(val*10 + rxByte - 48);
                PrintChar(rxByte);
            }
            break;
        case SERVO_SELECT:
            break;
        case SET_LAZY_SUSAN:
            break;
        case SET_SCI_SERVO:
            break;
        case SET_CONT_SERVO_POWER:
            break;
        default:
            resetFSM();
    }
}

void setFSMState(uint8_t next_state) { state = next_state; }

void setFSMMode(uint8_t next_mode) { mode = next_mode; }

void setSign(uint8_t sign) { pos = sign; }

void setVal(uint32_t val) { val = val; }

void resetFSM() {
    setFSMState(IDLE);
    setFSMMode(MICHAEL_MODE);
    setSign(1);
    setVal(0);
    servoID = 0;
}

/* [] END OF FILE */
