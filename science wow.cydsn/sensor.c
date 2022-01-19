/* File:         sensor.c
 * Authors:      Oliver Huang, Jordan Smith.
 * Organization: Husky Robotics Team
 * 
 * This file includes fuction implementations for the sensors on the 
 * Science Board allowing reading from an ADC
 */
#include "project.h"
#include "CANLibrary.h"
#include "CANScience.h"
#include "sensor.h"
#include <stdint.h>

#define HUMIDITY (uint8_t) 0x16
#define TEMPERATURE (uint8_t) 0x17 //wrong
#define GAS (uint8_t) 0x18 //wrong

//referenced John's past work
void get_data(CANPacket* packet) {
    CANPacket new_packet;
    uint8_t sensor_type = DecodeTelemetryType(packet);
    uint8_t target_group = GetSenderDeviceGroupCode(packet);
    uint8_t target_serial = GetSenderDeviceSerialNumber(packet);
    uint32_t sensor_val = 0;
    switch(sensor_type) {
        case HUMIDITY :
            sensor_val = read_ADC(0);
            break;
        case TEMPERATURE :
            sensor_val = read_ADC(1); 
            break;
    }
    //assemble and send telemetry packet
    AssembleTelemetryReportPacket(&new_packet, target_group, target_serial, sensor_type, sensor_val);
    //SendCANPacket returns 0x0 for successful send, 0x1 for generic error, 0x2 if all output buffers are full
    if(SendCANPacket(&new_packet)){ 
		ERR_LED_Write(0);
        CyDelay(500);
        ERR_LED_Write(1);
	} 
}

uint16_t read_ADC(uint32_t channel) {
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT); //returns when all conversions are completed
    ADC_StopConvert();
    return ADC_GetResult16(channel); //channel 0 for humidity and 1 for temperature
}
/* [] END OF FILE */
