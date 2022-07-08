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

#define LED_COLOR_ID 0xF7

CANPacket can_send;
int sensorGetFlag = 0;

CY_ISR(Sensor_Handler) {
    sensorGetFlag = 1;
}
    
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
    
    //wip
    //isr_sensor_StartEx(Sensor_Handler);
    
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
        // encoder
        char out[32];
        uint16 value = QuadDec_1_GetCounter();
        UART_UartPutString(itoa(value, out, 10));
        UART_UartPutString("\n\r");
        
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
            ERR_LED_Write(0);
            int ID = GetPacketID(current);
            switch (ID) {
                case ID_TELEMETRY_TIMING : //wip
                    {
                        CAN_LED_Write(1); 
                        uint32_t time_ms = GetTelemetryTimingFromPacket(current);
                        if (time_ms == 0) {
                            isr_sensor_Disable();
                        }
                        //configure interrupt to new time
                        //isr_sensor_StartEx(Sensor_Handler);
                        CAN_LED_Write(0);
                    }
                    break;
                case ID_SCIENCE_SERVO_SET : //servo set 
                    {   
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t servoID = GetScienceServoIDFromPacket(current);
                        uint8_t angle = GetScienceServoAngleFromPacket(current);
                        set_servo_position(servoID, angle);
                        CAN_LED_Write(0);
                    }
                    break;
                case ID_SCIENCE_CONT_SERVO_POWER_SET :
                    {
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t servoID = GetScienceServoIDFromPacket(current);
                        //uint8_t miliDegrees = GetScienceServoAngleFromPacket(current); //tell davis SCUFFED CODE NOT IMPLEMENTED PLACEHOLDER
                        uint8_t power = GetScienceContServoPowerFromPacket(current);
                        set_servo_continuous(servoID, power);
                        CAN_LED_Write(0);
                    }
                case ID_TELEMETRY_PULL : //sensor pull
                    {
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t sensor_type = DecodeTelemetryType(current);
                        uint8_t target_group = GetSenderDeviceGroupCode(current);
                        uint8_t target_serial = GetSenderDeviceSerialNumber(current);
                        get_data(sensor_type, target_group, target_serial); //fetch sensor data with ADC read & send new Telemetry Packet to CAN
                        CAN_LED_Write(0);
                    }
                    break;
                default :
                    ERR_LED_Write(0);
                    //CyDelay(500);
                    ERR_LED_Write(1);
                    break;
            }
            
            if (sensorGetFlag) {
                periodicSend();
                sensorGetFlag = 0;
            }
        } 
    }            
}

/* [] END OF FILE */
