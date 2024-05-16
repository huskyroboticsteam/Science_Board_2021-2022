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
#include <stdio.h>
#include "debug.h"

uint8_t state;
uint8_t mode;
int8_t pos;
int32_t val;
uint8_t servoID;
uint8_t runFlag;

uint8_t servoPosList[SERVO_COUNT];

void UART_FSM(char rxByte) {
    switch (state) {
        case (IDLE):
            idleAction(rxByte);
            break;
        case SERVO_SELECT:
            servoSelectAction(rxByte);
            break;
        case (READ_SET_DATA):
            readDataAction(rxByte);
            break;
        default:
            resetFSM();
    }
}

void setFSMState(uint8_t nextState) { state = nextState; }

void setFSMMode(uint8_t nextMode) { mode = nextMode; }

void setSign(uint8_t sign) { pos = sign; }

void setVal(uint32_t nextVal) { val = nextVal; }

void setFlag(uint8_t nextFlag) { runFlag = nextFlag; }

void setServoID(uint8_t nextServo) { servoID = nextServo; }

uint32_t getVal() { return val; }

uint8_t getServoID() { return servoID; }

uint8_t getFlag() { return runFlag; }

void resetFlag() { runFlag = 0; }

void resetFSM() {
    setFSMState(IDLE);
    setFSMMode(MICHAEL_MODE);
    setSign(1);
    setVal(0);
    servoID = 0;
    runFlag = 0;
}

void resetAllServos() {
    servoPosList = {0,0,0,0,0,0,0,0};
}

// State Actions

void idleAction(char rxByte) {
    Print("\r\n");
    Print("Select Mode:\r\n");
    Print("\tl: Lazy Susan\r\n");
    Print("\ts: Science Servos\r\n");
    Print("\tc: Continuous Servos\r\n");
    setVal(0);
    setSign(1);
    switch (rxByte) {
        case 'l':
            setFSMMode(LAZY_SUSAN_MODE);
            setFSMState(READ_SET_DATA);
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
            Print("Select Servo: ");
            break;
        case 'c':
            setFSMMode(CONT_SERVO_MODE);
            setFSMState(SERVO_SELECT);
            PrintChar(rxByte);
            Print("\r\n");
            Print("Setting Continuous Servos...\r\n");
            Print("Select Servo: ");
            break;
        default:
            DebugPrint(rxByte);
    }   
}

void readDataAction(char rxByte) {
    if (rxByte == '\r' || rxByte == '\n') {
        if (!pos) setVal(-1*val);
        Print("\r\n");
        switch (mode) {
            case LAZY_SUSAN_MODE:
                setFlag(1);
                
                setFSMState(IDLE);
                setFSMMode(MICHAEL_MODE);
                break;
            case SCI_SERVO_MODE:
                setFlag(2);
                
                setFSMState(IDLE);
                setFSMMode(MICHAEL_MODE);               
                break;
            case CONT_SERVO_MODE:
                setFlag(3);
                
                setFSMState(IDLE);
                setFSMMode(MICHAEL_MODE);
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
}

void servoSelectAction(char rxByte) {
    setServoID(rxByte - 48);
    PrintChar(rxByte);
    Print("\r\n");
    if (servoID < 0 || servoID > 7) {
        Print("Invalid Servo ID. Try Again.");
        setServoID(0);;
    } else {
        if (mode == SCI_SERVO_MODE || mode == CONT_SERVO_MODE) {
            setFSMState(READ_SET_DATA);
        } else {
            resetFSM();
        }
    }   
}

/* [] END OF FILE */
