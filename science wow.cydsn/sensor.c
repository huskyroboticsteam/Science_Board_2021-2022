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
#include "CANLibrary.h"
#include "CANScience.h"
#include <stdint.h>

#define HUMIDITY (uint8_t) 0x16
#define TEMPERATURE (uint8_t) 0x17 //wrong
#define SPECTROMETER (uint8_t) 0x18 //wrong
	
void get_data(uint8_t sensor_type) {
    switch(sensor_type) {
        case HUMIDITY :       
        break;
        case TEMPERATURE :
        break;
        case SPECTROMETER :
        break;
    }
}
/* [] END OF FILE */
