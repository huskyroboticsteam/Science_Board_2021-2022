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

#define PWM_PERIOD 20 //pwm period ms

//constants for actual LED pin number on board
//#define CUP_LIDS_SERVO 1
//#define CAMERA_SERVO 5
//#define DRILL_ARM 7

//#define MSCOPE_CONT_SERVO 8  
#define LSUSAN_CONT_SERVO_LED_NUM 9
//#define CAMERA_CONT_SERVO 15

#define DRILL_COVER_SERVO_LED_NUM 8


void set_servo_position(uint8_t servo, uint8_t degrees){
    // float32 min;
    // float32 range;
    // float32 offset;
    float32 pwmDuty;
    int found = 1;
    if(degrees > 179) degrees = 179; //may be different for each case
	if(degrees < 1) degrees = 1;
	if (servo < 0) {// || servo > 4){
		return;
	}
    switch(servo) {
        //case numbers were arbitrarily defined by software
        case DRILL_COVER_ID : // Drill Cover Servo
            servo = DRILL_COVER_SERVO_LED_NUM;
            break;
//        case 4 : //Tower Pro SG90 //CAMERA TILT
//            servo = CAMERA_SERVO;
//            break;
//        case 5: //Tower Pro SG90 //DRILL ARM
//            servo = DRILL_ARM;
//            break;
        default: 
            found = 0;
            ERR_LED_Write(0);
            //CyDelay(500);
            ERR_LED_Write(1);
            break;
    }
    //offset = ((float)degrees / 180) * range; 
    if (found) {
        pwmDuty = (degrees/((float32)180))*5 + 5;
   	    setPWMFromDutyCycle(servo, pwmDuty);
    }
}

void reset_servo_cont() {
    //setPWMFromDutyCycle(9, 7.6);
    set_servo_continuous(0, 0);
    set_servo_continuous(2, 0);
    set_servo_continuous(4, 0);
}

void lazy_susan_pos_set() {
}
void set_servo_continuous(int servo, int power) {
// Do math to control servo, stable is 1.5, so use given direction and speed to determine what pulse length to use
    //vector gives speed and direction, from -100 to 100. negative is counter-clockwise
    
    //int32_t tickGoal = miliDegrees;
    //float32 range = 0;
    float32 offset = 0;
    float32 pwmDuty = 0;
    int found = 1;
    switch(servo) {
        case LAZY_SUSAN_ID: //SM-S4303R //Lazy Susan
            servo = LSUSAN_CONT_SERVO_LED_NUM;
            //range = 0.5;
            break;
//        case 2: //Parallax Rotation //Microscope
//            servo = MSCOPE_CONT_SERVO;
//            //range = 0.4;
//            break;
//        case 3: //SM-S4303R //camera PAN
//            servo = CAMERA_CONT_SERVO;
//            //range = 0.5;
//            break;
        default:
            found = 0;
            ERR_LED_Write(0);
            //CyDelay(500);
            ERR_LED_Write(1);
            break;
    }
    pwmDuty = (((float32)power + 100) / 200)* 5 + 5.1;     
    
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

  
//wip
//uint32_t cups_forward (uint8_t goal_cup_pos, uint32_t current_cup_pos) {
//    if (goal_cup_pos < current_cup_pos) {
//        6 * (12 - current_cup_pos) 
//    }
//}

//not needed probably - Jordan
//void correctPosition(int servo, int power){
//    switch(servo){
//        case PIN3:
//            break;
//        case PIN4:
//            break;
//        default:
//            ERR_LED_Write(0);
//            CyDelay(500);
//            ERR_LED_Write(1);
//            break;
//    }   
//}

/* [] END OF FILE */
