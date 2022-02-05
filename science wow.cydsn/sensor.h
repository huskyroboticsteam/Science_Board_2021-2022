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
uint8_t I2C_bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);
uint16_t read_uv_sensor();
/* [] END OF FILE */
