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

#define LAZY_SUSAN 0 
#define CUP_LIDS 1
#define MICROSCOPE 2
#define CAM_PAN 3
#define CAM_TILT 4
#define DRILL_COVER 5

void set_servo_position(int servo, int degrees);
void set_servo_continuous(int servo, int power);
void correctPosition(int servo, int power);
uint32_t cups_forward (uint8_t goal_cup_pos, uint32_t current_cup_pos);
void reset_servo_cont(); 
/* [] END OF FILE */
