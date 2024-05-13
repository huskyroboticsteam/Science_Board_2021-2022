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

float32 current_duty_cycles[16] = {};

// sets the PCA duty cycle for positional servos 1-8
// degrees is from 0 to 180
int set_servo_position(int servo, int degrees){
    if(degrees > 180) degrees = 180;
	if(degrees < 0) degrees = 0;
	if (servo < 0 || servo > 7) return 1;
    
    current_duty_cycles[servo] = (degrees/180.0)*5 + 5;
   	setPWMFromDutyCycle(servo, current_duty_cycles[servo]);
    return 0;
}

// sets the PCA duty cycle for continuous servos 1,2,spare
// power is from -100 to 100
int set_servo_continuous(int servo, int power) {
    if (servo < 8 || servo > 15) return 1;
    if (power > 100) power = 100;
	if (power < -100) power = -100;
    
    current_duty_cycles[servo] = (power + 100) / 40.0 + 5.1;     
    setPWMFromDutyCycle(servo, current_duty_cycles[servo]);
    return 0;
}

// stop all continuous servos
void reset_servo_cont() {
    set_servo_continuous(CONT_SERVO1, 0);
    set_servo_continuous(CONT_SERVO2, 0);
    set_servo_continuous(CONT_SERVO_SPARE, 0);
}

// set lazy susan position
// TODO: position range
void lazy_susan_pos_set() {
    // TODO: implement (also position control on periodic interrupt)
}

/* [] END OF FILE */
