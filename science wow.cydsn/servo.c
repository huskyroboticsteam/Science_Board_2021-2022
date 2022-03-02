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
#include "CANLibrary.h"
#include "CANScience.h"
#include "PCA9685.h"
#include "project.h"
#include "servo.h"

//referenced John's past work
void set_servo_position(int servo, int degrees){
    int offset;
    int scalar;
    int divisor;
    if(degrees > 179) degrees = 179;
	if(degrees < 1) degrees = 1;
	if(servo < 0 || servo > 4){
		return;
	}
    switch(servo) {
        /*case PIN0 :
            break;
        case PIN1 :
            break;
        case PIN2 :
            break;
        case PIN3 :
            break;
        case PIN4 :
            break; */
        default: 
            offset = 102;
            scalar = 99;
            divisor = 172;
            break;
    }    
	setPWMFromDutyCycle(servo, offset + (degrees * scalar) / divisor);
}

void set_servo_continuous(int servoID, int direction, int speed, int miliDegrees){
// Do math to control servo, stable is 1.5, so use given direction and speed to determine what pulse length to use
    
    // Start Servo setPWMFromDutyCycle();
    
    if (servoID == 1){
        int32_t ticks = miliDegrees;
        while (QuadDec_1_GetCounter() < ticks){};
        // Stop Servo setPWNFromDutyCycle();
        // Maybe Check if end position is too far from goal
    }
    
    if (servoID == 2){
        int32_t ticks = miliDegrees;
        while (QuadDec_2_GetCounter() < ticks){};
        // Stop Servo setPWNFromDutyCycle();
        
    }
}

/* [] END OF FILE */
