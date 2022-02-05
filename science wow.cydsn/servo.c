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
/* [] END OF FILE */
