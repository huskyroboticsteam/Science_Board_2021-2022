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

#define VEML6070_ADDR_ARA 0x18
#define VEML6070_ADDR_CMD 0x70
#define VEML6070_ADDR_DATA_LSB 0x71
#define VEML6070_ADDR_DATA_MSB 0x73


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
        case CAN_SCIENCE_SENSOR_UV :
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




//void VEML6070_init(){
//	wdt_reset();
//	VEML6070_read_byte(VEML6070_ADDR_ARA);
//	VEML6070_write_byte(VEML6070_ADDR_CMD, 0x04); //Integration time = 1 //Possibly 06
//}

uint16_t read_uv_sensor(){
	uint8_t lsb;
    uint8_t msb;
    uint8_t lsberror = I2C_bus_read(VEML6070_ADDR_CMD, VEML6070_ADDR_DATA_LSB, &lsb, 1);
	uint8_t msberror = I2C_bus_read(VEML6070_ADDR_CMD, VEML6070_ADDR_DATA_MSB, &msb, 1);
    
    if (lsberror != I2C_I2C_MSTR_NO_ERROR || msberror != I2C_I2C_MSTR_NO_ERROR){
        ERR_LED_Write(0);
        CyDelay(500);
        ERR_LED_Write(1);
    }
	return (msb << 8) | lsb;
}



//yoinked from davis
//read byte(s) from i2C and store in array
uint8_t I2C_bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt)
{
    I2C_I2CMasterClearStatus(); //clear the garbage
  
    int ms_timeout = 20; 
    int32_t BNO055_iERROR = 0; // this is the "status" we usually use in our R/W functions 
	uint8_t idx;
	BNO055_iERROR = I2C_I2CMasterSendStart(dev_addr, I2C_I2C_WRITE_XFER_MODE, ms_timeout);
	// Check for BNO055_iERROR before proceeding
	BNO055_iERROR = I2C_I2CMasterWriteByte(reg_addr, ms_timeout);
	// Check for BNO055_iERROR before proceeding
	BNO055_iERROR = I2C_I2CMasterSendStop(10);
	
	BNO055_iERROR = I2C_I2CMasterSendStart(dev_addr, I2C_I2C_READ_XFER_MODE, ms_timeout);
    //PrintInt(BNO055_iERROR);
	for (idx = 0; (idx < cnt) && (BNO055_iERROR == 0); idx++)
	{
        if (idx < cnt-1)
        {
		    I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA, &reg_data[idx], ms_timeout);
        }
        else
        {
            I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA, &reg_data[idx], ms_timeout);
        }
	}
	// Check for BNO055_iERROR before proceeding
	BNO055_iERROR = I2C_I2CMasterSendStop(ms_timeout);

	return (int8_t)BNO055_iERROR;
}

/* [] END OF FILE */
