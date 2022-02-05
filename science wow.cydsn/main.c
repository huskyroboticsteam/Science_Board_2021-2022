/* File:         main.c
 * Authors:      Oliver Huang, Jordan Smith.
 * Organization: Husky Robotics Team
 * Firmware for Science Sensors Board (2022)
 */
#include "project.h"
#include "CANLibrary.h"
#include "CANScience.h"
#include "sensor.h"
#include <stdint.h>
#include "PCA9685.h"
#include "servo.h"

#define SERVO_SET_ID 0x0D
#define SENSOR_PULL_ID 0xF5
#define LED_COLOR_ID 0xF7

int main(void)
{
    CyGlobalIntEnable;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitCAN(DEVICE_GROUP_SCIENCE, 0x1); //1 because only 1 science board
    ADC_Start();
    pca_init();
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
                        set_servo_position(servoID, angle);
                    }
                    break;
                case SENSOR_PULL_ID : //sensor pull
                    {
                        CAN_LED_Write(1);
                        CyDelay(500);
                        CAN_LED_Write(0);
                        get_data(current); //fetch sensor data with ADC read & send new Telemetry Packet to CAN
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
