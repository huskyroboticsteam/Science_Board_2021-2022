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
#include "Milliseconds.h"

#define LED_COLOR_ID 0xF7
#define TICKS_TO_NEXT_CUP 20

CANPacket can_send;
CANPacket current;
uint32_t time_ms;
uint8_t current_cup_pos;
uint32_t encoder_val;

CY_ISR(Enc2_Handler) {
    QuadDec_2_ClearInterrupt(QuadDec_2_INTR_MASK_CC_MATCH);
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
    CC2_isr_StartEx(Enc2_Handler);
    
    //wip
    //isr_sensor_StartEx(Sensor_Handler);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitCAN(DEVICE_GROUP_SCIENCE, 0x1); //1 because only 1 science board
    ADC_Start();
    pca_init();
    
    QuadDec_1_Start();
    QuadDec_2_Start();
    //set index trigger
    QuadDec_2_TriggerCommand(QuadDec_2_MASK, QuadDec_2_CMD_RELOAD);
    
    UART_Start();
    VEML6070_init();
    reset_servo_cont();
    time_ms = 0;
    
    encoder_val = QuadDec_2_ReadCounter();
    current_cup_pos = 0;
    
    for(;;)
    {      
        
        //uint32 count = QuadDec_2_ReadCounter();
//         Testing area
//         encoder
        //char out1[32];
//        uint32_t value = QuadDec_2_ReadCounter();
//        UART_UartPutString(itoa(value, out1, 10));
//        UART_UartPutString("\n\r");
//        
        //LEDs
       /* for(int i = 1; i <=5; ++i){
            DBG_LED_Write(1);
            CyDelay(300);
            DBG_LED_Write(0);
            CyDelay(300);
        } */
        
        //Sensors
 //       uint32_t Hum_val = read_ADC(0);
        //uint32_t Temp_val = read_ADC(1);
//        VEML6070_init();
//        uint32_t sensor_val = read_uv_sensor();
//        
//        char out[32];
        //show results
//        UART_UartPutString(itoa(Hum_val, out1, 10));
        //UART_UartPutString("\n\r");
//        UART_UartPutString(itoa(Temp_val, out1, 10));
//        //uart_uartputstring(itoa(sensor_val, out, 10));
//        UART_UartPutString("bababooey");
//        UART_UartPutString("\n\r");
//        
//        int servo = 7;
//        int degrees = 31;
//        setPWMFromDutyCycle(9, 50);

        
        /* Place your application code here. */
        
        
        int poll = PollAndReceiveCANPacket(&current); 
        if (poll == 0) {
            ERR_LED_Write(0);
            int ID = GetPacketID(&current);
            switch (ID) {
                case ID_SCIENCE_LAZY_SUSAN_POS_SET : //pos set on lazy susan
                    {
                        CAN_LED_Write(1);
                        current_cup_pos = GetScienceLazySusanPosFromPacket(&current);
//                        uint8_t goal_cup_pos = GetScienceLazySusanPosFromPacket(current);
                        //uint32_t tick_goal = QuadDec_2_ReadCounter() + cups_forward(goal_cup_pos, current_cup_pos);
                    }
                    break;
                case ID_TELEMETRY_TIMING : //wip
                    {
                        CAN_LED_Write(1); 
                        // the enableInterrupts variable saves the current interrupt 
                        // masking state inside the cpu registers. We pause interrupts
                        // so that it does not interfere with the reading of 32 bits
                        uint8 enableInterrupts = CyEnterCriticalSection();
                        uint32_t time_ms = GetTelemetryTimingFromPacket(&current);
                        // restore the interrupt masking state
                        CyExitCriticalSection(enableInterrupts);
                        //if compare time is not 0
                        if (time_ms) {
                            //start millisecond counter
                            init_milliseconds();
                        } else {
                            //stop millisecond counter
                            isr_1ms_Stop();
                        }
                        CAN_LED_Write(0);
                    }
                    break;
                case ID_SCIENCE_SERVO_SET : //servo set 
                    {   
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t servoID = GetScienceServoIDFromPacket(&current);
                        uint8_t angle = GetScienceServoAngleFromPacket(&current);
                        set_servo_position(servoID, angle);
                        CAN_LED_Write(0);
                    }
                    break;
                case ID_SCIENCE_CONT_SERVO_POWER_SET :
                    {
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t servoID = GetScienceServoIDFromPacket(&current);
                        //uint8_t miliDegrees = GetScienceServoAngleFromPacket(current); //tell davis SCUFFED CODE NOT IMPLEMENTED PLACEHOLDER
                        uint8_t power = GetScienceContServoPowerFromPacket(&current);
                        set_servo_continuous(servoID, power);
                        CAN_LED_Write(0);
                    }
                case ID_TELEMETRY_PULL : //sensor pull
                    {
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t sensor_type = DecodeTelemetryType(&current);
                        uint8_t target_group = GetSenderDeviceGroupCode(&current);
                        uint8_t target_serial = GetSenderDeviceSerialNumber(&current);
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
            //when the compare time is greater than 0 and the current milliseconds is greater than
            //or equal to the compare time, we send sensor data.
            if ((time_ms > 0) && (milliseconds >= time_ms)) {
                milliseconds = 0;
                periodicSend();
            }
        } 
    }            
}

void nextCup() {
    set_servo_continuous(LAZY_SUSAN, 100);
    while(QuadDec_2_ReadCounter() < encoder_val + 12) {}
    set_servo_continuous(LAZY_SUSAN, 0);
}

void prevCup() {
    set_servo_continuous(LAZY_SUSAN, -100);
    while(QuadDec_2_ReadCounter() > encoder_val - 12) {}
    set_servo_continuous(LAZY_SUSAN, 0);
} 



/* [] END OF FILE */
