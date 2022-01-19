/* File:         sensor.h
 * Authors:      Oliver Huang, Jordan Smith.
 * Organization: Husky Robotics Team
 * 
 * This file includes fuction prototypes for the sensors on the 
 * Science Board and functionality for reading from an ADC
 */
#include <stdint.h>
#include "CANLibrary.h"
#include "CANScience.h"

void get_data(CANPacket* packet);
uint16_t read_ADC(uint32_t channel);
/* [] END OF FILE */
