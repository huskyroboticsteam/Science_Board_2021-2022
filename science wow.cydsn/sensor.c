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
#include "project.h"
#include "CANLibrary.h"
#include "CANScience.h"
#include <stdint.h>

#define HUMIDITY (uint8_t) 0x16
#define TEMPERATURE (uint8_t) 0x17 //wrong
#define SPECTROMETER (uint8_t) 0x18 //wrong

//referenced John's past work
void get_data(CANPacket* packet) {
    CANPacket new_packet;
    uint8_t sensor_type = DecodeTelemetryType(packet);
    uint8_t target_group = GetSenderDeviceGroupCode(packet);
    uint8_t target_serial = GetSenderDeviceSerialNumber(packet);
    uint32_t sensor_val = 0;
    switch(sensor_type) {
        case HUMIDITY :       
        break;
        case TEMPERATURE :
        break;
        case SPECTROMETER :
        break;
    }
    AssembleTelemetryReportPacket(&new_packet, target_group, target_serial, sensor_type, sensor_val);
    if(SendCANPacket(&new_packet)){
		ERR_LED_Write(0);
        CyDelay(500);
        ERR_LED_Write(1);
	}
}
/* [] END OF FILE */
