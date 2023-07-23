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

#define LAZY_SUSAN_ID 0 
#define CUP_LIDS_ID 1
#define MICROSCOPE_ID 2
#define CAM_PAN_ID 3
#define CAM_TILT_ID 4
#define DRILL_COVER_ID 5

void set_servo_position(uint8_t servo, uint8_t degrees);
void set_servo_continuous(int servo, int power);
void correctPosition(int servo, int power);
uint32_t cups_forward (uint8_t goal_cup_pos, uint32_t current_cup_pos);
void reset_servo_cont(); 
/* [] END OF FILE */
