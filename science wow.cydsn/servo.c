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

#define PWM_PERIOD 5 //pwm period ms

void set_servo_position(int servo, int degrees){
    float32 min;
    float32 range;
    float32 offset;
    uint16_t pwmDuty;
    if(degrees > 179) degrees = 179; //may be different for each case
	if(degrees < 1) degrees = 1;
	if(servo < 0 || servo > 4){
		return;
	}
    switch(servo) {
        case PIN7 : //Tower Pro SG90
            min = 1;
            range = 1;
            offset = ((float32)degrees / 180) * range; 
            break;
        case PIN1 : //HSB-9380TH
            break;
        case PIN2 : //HiTEC HS-645MG
            break;
        default: 
            min = 1;
            range = 1;
            offset = ((float32)degrees / 180) * range; 
            break;
    }    
    //offset = ((float)degrees / 180) * range; 
    pwmDuty = ((min + offset) / PWM_PERIOD) * 100;
   	setPWMFromDutyCycle(servo, pwmDuty);
    //setPWMFromBytes(servo, (4095 - pwm) & 0xFF, (4095 - pwm) >> 8, pwm & 0xFF, pwm >> 8);

}

void set_servo_continuous(int servo, int direction, int speed, int miliDegrees){
// Do math to control servo, stable is 1.5, so use given direction and speed to determine what pulse length to use
    
    int32_t tickGoal = miliDegrees;
    float32 range = 0;
    float32 offset = 0;
    uint32_t pwmDuty = 0;
    int notfound = 0;
    switch(servo) {
        case PIN3 : //SM-S4303R
            range = 0.5;
            break;
        case PIN4: //Parallax Rotation
            range = 0.4;
            break;
        default:
            notfound = 1;
            ERR_LED_Write(0);
            CyDelay(500);
            ERR_LED_Write(1);
            break;
    }
    offset = ((float32)speed / 100) * range;
    if (speed != 0) {        
        if (direction == 0) { //clockwise
            pwmDuty = (1.5 - offset) / PWM_PERIOD;
        } else if (direction == 1) { //counterclockwise
            pwmDuty = (1.5 + offset) / PWM_PERIOD;
        }
    }
    if (notfound == 0) { //if correct servo id
        //setPWMFromBytes(servo, ((int)(4095 - pwm) & 0xFF), (int)(4095 - pwm) >> 8, (int)pwm & 0xFF, (int)pwm >> 8);
        setPWMFromDutyCycle(servo, pwmDuty);
    }
        
    if (servo == PIN3){ //HSR-1425CR
        while (QuadDec_1_GetCounter() < tickGoal){};
        setPWMFromDutyCycle(servo, 0);
        //if ((QuadDec_1_GetCounter() - tickGoal) >= 5){correctPosition(servo, 1);}
        //if ((QuadDec_1_GetCounter() - tickGoal) <= 5){correctPosition(servo, 0);}
    }
           
    if (servo == PIN4){ //Parallax Rotation
        while (QuadDec_2_GetCounter() < tickGoal){};
        setPWMFromDutyCycle(servo, 0);
        //if ((QuadDec_2_GetCounter() - tickGoal) >= 5){correctPosition(servo, 1);}
        //if ((QuadDec_2_GetCounter() - tickGoal) <= 5){correctPosition(servo, 0);}
    }
}

void correctPosition(int servo, int direction){
    switch(servo){
        case PIN3:
            break;
        case PIN4:
            break;
        default:
            ERR_LED_Write(0);
            CyDelay(500);
            ERR_LED_Write(1);
            break;
    }   
}

/* [] END OF FILE */
