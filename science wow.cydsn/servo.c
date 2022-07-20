/* File:         sensor.c
 * Authors:      Oliver Huang, Jordan Smith.
 * Organization: Husky Robotics Team
 * 
 * This file includes fuction implementations for the servos on the 
 * Science Board including continuous servos
 */
#include <stdint.h>
#include "CANLibrary.h"
#include "CANScience.h"
#include "PCA9685.h"
#include "project.h"
#include "servo.h"

#define PWM_PERIOD 5 //pwm period ms

//constants for actual LED pin number on board
#define CUP_LIDS_SERVO 6
#define CAMERA_SERVO 2

#define MSCOPE_CONT_SERVO 9  
#define LSUSAN_CONT_SERVO 8
#define CAMERA_CONT_SERVO 15

void set_servo_position(int servo, int degrees){
    float32 min;
    float32 range;
    float32 offset;
    uint16_t pwmDuty;
    int found = 1;
    if(degrees > 179) degrees = 179; //may be different for each case
	if(degrees < 1) degrees = 1;
	if(servo < 0 || servo > 4){
		return;
	}
    switch(servo) {
        //case numbers were arbitrarily defined by software
        case 1 : //Lids
            servo = CUP_LIDS_SERVO;
            min = 1.1;
            range = 0.8;
            offset = ((float32)degrees / 180) * range;
            break;
        case 4 : //Tower Pro SG90 //CAMERA TILT
            servo = CAMERA_SERVO;
            min = 1;
            range = 1;
            offset = ((float32)degrees / 180) * range; 
            break;
        default: 
            found = 0;
            ERR_LED_Write(0);
            //CyDelay(500);
            ERR_LED_Write(1);
            break;
    }    
    //offset = ((float)degrees / 180) * range; 
    if (found) {
        pwmDuty = ((min + offset) / PWM_PERIOD) * 100;
   	    setPWMFromDutyCycle(servo, pwmDuty);
        //setPWMFromBytes(servo, (4095 - pwm) & 0xFF, (4095 - pwm) >> 8, pwm & 0xFF, pwm >> 8);
    }

}

void set_servo_continuous(int servo, int power) {
// Do math to control servo, stable is 1.5, so use given direction and speed to determine what pulse length to use
    //vector gives speed and direction, from -100 to 100. negative is counter-clockwise
    
    //int32_t tickGoal = miliDegrees;
    float32 range = 0;
    float32 offset = 0;
    uint32_t pwmDuty = 0;
    int found = 1;
    switch(servo) {
        case 0 : //SM-S4303R //Lazy Susan
            servo = LSUSAN_CONT_SERVO;
            range = 0.5;
            break;
        case 2: //Parallax Rotation //Microscope
            servo = MSCOPE_CONT_SERVO;
            range = 0.4;
            break;
        case 4 : //SM-S4303R //camera PAN
            servo = CAMERA_CONT_SERVO;
            range = 0.5;
            break;
        default:
            found = 0;
            ERR_LED_Write(0);
            //CyDelay(500);
            ERR_LED_Write(1);
            break;
    }
    offset = ((float32)power / 100) * range;     
    pwmDuty = (1.5 + offset) / PWM_PERIOD;
    
    if (found) { //if correct servo id
        //setPWMFromBytes(servo, ((int)(4095 - pwm) & 0xFF), (int)(4095 - pwm) >> 8, (int)pwm & 0xFF, (int)pwm >> 8);
        setPWMFromDutyCycle(servo, pwmDuty);
    }
        
//    if (servo == PIN3){ //HSR-1425CR
//        while (QuadDec_1_GetCounter() < tickGoal){};
//        setPWMFromDutyCycle(servo, 0);
//        
//        //old
//        //if ((QuadDec_1_GetCounter() - tickGoal) >= 5){correctPosition(servo, 1);}
//        //if ((QuadDec_1_GetCounter() - tickGoal) <= 5){correctPosition(servo, 0);}
//    }
           
//    if (servo == PIN4){ //Parallax Rotation
//        while (QuadDec_2_GetCounter() < tickGoal){};
//        setPWMFromDutyCycle(servo, 0);
//        
//        //old
//        //if ((QuadDec_2_GetCounter() - tickGoal) >= 5){correctPosition(servo, 1);}
//        //if ((QuadDec_2_GetCounter() - tickGoal) <= 5){correctPosition(servo, 0);}
//    }
}

//not needed probably - Jordan
void correctPosition(int servo, int power){
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
