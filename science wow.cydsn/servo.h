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

void set_servo_position(int servo, int degrees);
void set_servo_continuous(int servo, int direction, int speed, int miliDegrees);
void continuous_Encoder_Control(int encoderID);
/* [] END OF FILE */
