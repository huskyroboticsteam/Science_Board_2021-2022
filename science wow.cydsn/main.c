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
#include <stdlib.h>

#define SERVO_SET_ID 0x0D
#define SENSOR_PULL_ID 0xF5
#define LED_COLOR_ID 0xF7
#define SERVO_CONTINOUS_ID 0x0E

CANPacket can_send;

CY_ISR(Limit_Handler){
    //Stuff to do during interupt
    AssembleLimitSwitchAlertPacket(&can_send, DEVICE_GROUP_JETSON, 
        DEVICE_SERIAL_JETSON, Status_Reg_LIM_Read() & 0b11);
    SendCANPacket(&can_send);
}

int main(void)
{
    CyGlobalIntEnable;
    Status_Reg_LIM_InterruptEnable();
    isr_LIM_StartEx(Limit_Handler);
    
      
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitCAN(DEVICE_GROUP_SCIENCE, 0x1); //1 because only 1 science board
    ADC_Start();
    pca_init();
    QuadDec_1_Start();
    QuadDec_2_Start();
    UART_Start();
    VEML6070_init();
    
     
    for(;;)
    {           
        
        // Testing area
        
        //LEDs
       /* for(int i = 1; i <=5; ++i){
            DBG_LED_Write(1);
            CyDelay(300);
            DBG_LED_Write(0);
            CyDelay(300);
        } */
        
        //Sensors
        //uint32_t Hum_val = read_ADC(0);
        //uint32_t Temp_val = read_ADC(1);
//        VEML6070_init();
//        uint32_t sensor_val = read_uv_sensor();
//        
//        char out[32];
//        //Show Results
//        UART_UartPutString(itoa(sensor_val, out, 10));
//        UART_UartPutString("\n\r");
        
//        int servo = 7;
//        int degrees = 31;
//        setPWMFromDutyCycle(9, 50);

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
                case SERVO_CONTINOUS_ID :
                    {
                        CAN_LED_Write(1);
                        CyDelay(500);
                        CAN_LED_Write(0);
                        uint8_t servoID = GetScienceServoIDFromPacket(current);
                        uint8_t miliDegrees = GetScienceServoAngleFromPacket(current); //tell davis SCUFFED CODE NOT IMPLEMENTED PLACEHOLDER
                        uint8_t speed = GetScienceServoSpeedFromPacket(current);
                        uint8_t direction = GetScienceServoDirectionFromPacket(current);
                        set_servo_continuous(servoID, direction, speed, miliDegrees);
                    }
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
