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
        case PIN0 : //Futaba S3003
            offset = 113;
            scalar = 82;
            divisor = 179;
            break;
        case PIN1 : //HSB-9380TH
            offset = 72;
            scalar = 164;
            divisor = 205;
            break;
        case PIN2 : //HiTEC HS-645MG
            offset = 113;
            scalar = 82;
            divisor = 179;
            break;
        default: //john
            offset = 102;
            scalar = 99;
            divisor = 172;
            break;
    }    
	setPWMFromDutyCycle(servo, offset + (degrees * scalar) / divisor);
}

void set_servo_continuous(int servo, int direction, int speed, int miliDegrees){
// Do math to control servo, stable is 1.5, so use given direction and speed to determine what pulse length to use
    
    // Start Servo setPWMFromDutyCycle();
    int range = 0;
    double duty = 0;
    int notfound = 0;
    switch(servo) {
        case PIN3 : //HSR-1425CR
            range = 41;
            break;
        case PIN4: //Parallax Rotation
            range = 20;
            break;
        default:
            notfound = 1;
            ERR_LED_Write(0);
            CyDelay(500);
            ERR_LED_Write(1);
            break;
    }
    duty = (((double)range) * speed) / 100;
    if (speed != 0) {        
        if (direction == 0) { //clockwise
            duty = 153 - duty;
        } else if (direction == 1) { //counterclockwise
            duty += 154;
        }
    }
    if (notfound == 0) { //if correct servo id
        setPWMFromDutyCycle(servo, duty);
    }
        
    if (servo == PIN3){ //HSR-1425CR
        int32_t ticks = miliDegrees;
        while (QuadDec_1_GetCounter() < ticks){};
        // Stop Servo setPWNFromDutyCycle();
        // Maybe Check if end position is too far from goal
    }
    
    if (servo == PIN4){ //Parallax Rotation
        int32_t ticks = miliDegrees;
        while (QuadDec_2_GetCounter() < ticks){};
        // Stop Servo setPWNFromDutyCycle();
        
    }
}

/* [] END OF FILE */
