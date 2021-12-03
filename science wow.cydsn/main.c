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
#include "sensor.h"
#include <stdint.h>

#define SERVO_SET_ID 0x0D
#define SENSOR_PULL_ID 0xF5
#define LED_COLOR_ID 0xF7

int main(void)
{
    //CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitCAN(DEVICE_GROUP_SCIENCE, 0x1); //1 because only 1 science board
    //SCP_1_Start();
    for(;;)
    {
        /* Place your application code here. */
        CANPacket* current; 
        
        int poll = PollAndReceiveCANPacket(current); 
        if (poll == 0) {
            int ID = GetPacketID(current);
            switch (ID) {
                case SERVO_SET_ID : //servo set 
                    {   
                        CAN_LED_Write(1);
                        CyDelay(500);
                        CAN_LED_Write(0);
                        uint8_t servoID = GetScienceServoIDFromPacket(current);
                        uint8_t angle = GetScienceServoAngleFromPacket(current);
                        //send this stuff to i2c
                        
                    }
                    break;
                case SENSOR_PULL_ID : //sensor pull
                    //packet will only have 1 piece of data so just use dot operator, no function exists
                    {
                        CAN_LED_Write(1);
                        CyDelay(500);
                        CAN_LED_Write(0);                        
                        uint8_t sensor_type = DecodeTelemetryType(current);
                        get_data(sensor_type);
                        //fetch sensor data with ADC method call and sensor read
                    }
                    break;
                default : 
                    ERR_LED_Write(0);
                    CyDelay(500);
                    ERR_LED_Write(1);
                    break;
            }
        }
    }
}

/* [] END OF FILE */
