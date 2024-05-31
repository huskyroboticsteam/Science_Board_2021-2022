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
#include <stdio.h>
#include <math.h>
#include <stdio.h>

#include "main.h"
#include "FSM.h"
#include "debug.h"

CANPacket can_send;
CANPacket current;
uint32_t time_ms;
// lazy susan
int8_t target_cup_pos;
int8_t first_cup_pos;
int32_t encoder_val;
double ideal_encoder_val;
double target_encoder_val;
uint8_t has_moved;
uint8_t moving;
int curr_power;

// debugging
char txData[200];
uint8 dbg_servo_sel = 0;
extern int16 current_servo_values[16];

// leds
uint8_t CAN_time_LED = 0;
uint8_t ERRORTimeLED = 0;

CY_ISR(Enc2_Handler) {
    QuadDec_2_ClearInterrupt(QuadDec_2_INTR_MASK_CC_MATCH);
}

CY_ISR(Limit_Handler){
    //Stuff to do during interupt
    AssembleLimitSwitchAlertPacket(&can_send, DEVICE_GROUP_JETSON, 
        DEVICE_SERIAL_JETSON, Status_Reg_LIM_Read() & 0b11111);
    SendCANPacket(&can_send);
}

CY_ISR(LED_Timer_Handler) {
    int timer = Timer_LEDs_ReadStatusRegister();
    CAN_time_LED++;
    ERRORTimeLED++;
   
    if(ERRORTimeLED >= 3) {
        ERR_LED_Write(0); // off 
        DBG_LED_Write(0);
    }
    if(CAN_time_LED >= 3){
        CAN_LED_Write(LED_OFF);
    }
}

void Initialize() {
    CyGlobalIntEnable;
    Status_Reg_LIM_InterruptEnable();
    isr_LIM_StartEx(Limit_Handler);
    CC2_isr_StartEx(Enc2_Handler);
    isr_LEDs_StartEx(LED_Timer_Handler);
    
    //wip
    //isr_sensor_StartEx(Sensor_Handler);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitCAN(DEVICE_GROUP_SCIENCE, 0x1); //1 because only 1 science board
    ADC_Start();
    pca_init();
    Timer_LEDs_Start();
    QuadDec_1_Start();
    QuadDec_2_Start();
    
    //set index trigger
    QuadDec_2_TriggerCommand(QuadDec_2_MASK, QuadDec_2_CMD_RELOAD);
    
    DBG_UART_Start();
    VEML6070_init();
    
    DBG_UART_SpiUartClearRxBuffer();
}

int main(void)
{
    Initialize();
    
    // Print("Hello\r\n");
    
    reset_servo_cont();
    time_ms = 0;
    
    // lazy susan load regs 
    encoder_val = QuadDec_2_ReadCounter();
    target_encoder_val = encoder_val; //TODO: verify
    ideal_encoder_val = encoder_val;
    target_cup_pos = 0;
    first_cup_pos = 0;
    has_moved = 0;
    moving = 0;
    curr_power = 0;
    
    ERR_LED_Write(0);
    
    Print("Select Mode:\r\n");
    Print("\tl: Lazy Susan\r\n");
    Print("\ts: Science Servos\r\n");
    Print("\tc: Continuous Servos\r\n");
    
    DBG_UART_SpiUartClearRxBuffer();

    for(;;) {
        //testing
        
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         * * * * * * * * * * E N C O D E R _ T E S T I N G * * * * * * * *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */        
        // uint32 count = QuadDec_2_ReadCounter();
        // char out_enc[32];        uint32_t value = QuadDec_2_ReadCounter();
        // DBG_UART_UartPutString("Encoder Value: ");
        // DBG_UART_UartPutString(itoa(value, out_enc, 10));
        // DBG_UART_UartPutString(", ");
        
        
        //UART_UartPutString("\n\r");
        
        
    
        //LEDs
       /* for(int i = 1; i <=5; ++i){
            DBG_LED_Write(1);
            CyDelay(300);
            DBG_LED_Write(0);
            CyDelay(300);
        } */
        
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         * * * * * * * * * * S E N S O R _ T E S T I N G * * * * * * * * *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
//        uint32_t Hum_val = read_ADC(0);
//        ADC_StartConvert();
//        char out[32];
//        UART_UartPutString("Humidity Value: ");
//        UART_UartPutString(itoa(Hum_val, out, 10));
//        UART_UartPutString(", ");
//        char out3[32];
//        UART_UartPutString("target encval: ");
//        UART_UartPutString(itoa(target_encoder_val, out3, 10));
//        UART_UartPutString("\n\r");
//        CyDelay(100);
        
        //uint32_t Temp_val = read_ADC(1);
//        VEML6070_init();
//        uint32_t sensor_val = read_uv_sensor(); 
        //char out[32];
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
        //setPWMFromDutyCycle(15, 7);
//        setPWMFromDutyCycle(9, 30);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * O P E R A T I O N A L _ C O D E * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        
        // update encoder 
        encoder_val = QuadDec_2_ReadCounter();
        
        // check lazy susan movement
        if (moving && (((curr_power > 0) && (encoder_val >= round(target_encoder_val))) 
                         || ((curr_power < 0) &&  (encoder_val <= round(target_encoder_val))))) {
            set_servo_continuous(0, 0);
            moving = 0;
            first_cup_pos = target_cup_pos;
            ideal_encoder_val = target_encoder_val;
        }
        char out4[32];
//        UART_UartPutString("ms: ");
//        UART_UartPutString(itoa(milliseconds, out4, 10));
//        UART_UartPutString(", time_ms: ");
//        UART_UartPutString(itoa(time_ms, out4, 10));
//        UART_UartPutString("\n\r");
        volatile int error = PollAndReceiveCANPacket(&current); 
        
        if (!error) {  // packet on 0
            CAN_LED_Write(LED_ON); //on+
            CAN_time_LED = 0;
            PrintCanPacket(&current);
            int ID = GetPacketID(&current);
            switch (ID) {
                case ID_SCIENCE_LAZY_SUSAN_POS_SET : //pos set on lazy susan
                    {
//                        UART_UartPutString("enter ");
//                        UART_UartPutString("\n\r");
                        //CAN_LED_Write(0);
                        target_cup_pos = GetScienceLazySusanPosFromPacket(&current);
                        setLazySusan(target_cup_pos);
                    }
                    break;
                case ID_TELEMETRY_TIMING : //wip
                    {
                        // CAN_LED_Write(0); 
                        // the enableInterrupts variable saves the current interrupt 
                        // masking state inside the cpu registers. We pause interrupts
                        // so that it does not interfere with the reading of 32 bits
                        uint8 enableInterrupts = CyEnterCriticalSection();
                        time_ms = GetTelemetryTimingFromPacket(&current);
                        
                        // TODO: enable/set periodic timer
                        
                        // restore the interrupt masking state
                        CyExitCriticalSection(enableInterrupts);
                    }
                    break;
                case ID_SCIENCE_SERVO_SET : //servo set 
                    {   
                        CAN_LED_Write(1);
                        //CyDelay(500);
                        uint8_t servoID = GetScienceServoIDFromPacket(&current);
                        uint8_t angle = GetScienceServoAngleFromPacket(&current);
                        set_servo_position(servoID, angle);
                        //setPWMFromDutyCycle(7, (angle/180.0)*5 + 5); // TODO remove, map ids correctly
                        CAN_LED_Write(1);
                    }
                    break;
                case ID_SCIENCE_CONT_SERVO_POWER_SET :
                    {
                        // CAN_LED_Write(0);
                        // CyDelay(500);
                        uint8_t servoID = GetScienceServoIDFromPacket(&current);
                        // uint8_t miliDegrees = GetScienceServoAngleFromPacket(current);
                        // tell davis SCUFFED CODE NOT IMPLEMENTED PLACEHOLDER
                        uint8_t power = GetScienceContServoPowerFromPacket(&current);
                        set_servo_continuous(servoID, power);
                        // CAN_LED_Write(1);
                    }
                case ID_TELEMETRY_PULL : // sensor pull
                    {
                        // CAN_LED_Write(0);
                        // CyDelay(500);
                        uint8_t sensor_type = DecodeTelemetryType(&current);
                        uint8_t target_group = GetSenderDeviceGroupCode(&current);
                        uint8_t target_serial = GetSenderDeviceSerialNumber(&current);
                        get_data(sensor_type, target_group, target_serial); // fetch sensor data with ADC read & send new Telemetry Packet to CAN
                        // CAN_LED_Write(1);
                    }
                    break;
                default :
                    // no packet, do nothing
                    break;
            }
        }
        
        if (DBG_UART_SpiUartGetRxBufferSize()) {
            char rx = DBG_UART_UartGetChar();
            UART_FSM(rx);
        }
        
        if (getFlag()) {
            switch (getFlag()) {
                case 1: // lazy susan
                    setLazySusan(getVal());
                    Print("\r\nLazy Susan position set.");
                    break;
                case 2: // servos
                    set_servo_position(getServoID(), getVal());
                    Print("\r\nServo position set.");
                    break;
                case 3: // continuous servos
                    set_servo_continuous(getServoID(), getVal());
                    Print("\r\nContinuous servo power set.");
            }
            resetFlag();
            Print("\r\n");
            Print("Select Mode:\r\n");
            Print("\tl: Lazy Susan\r\n");
            Print("\ts: Science Servos\r\n");
            Print("\tc: Continuous Servos\r\n");
        }
    }     
}

void setLazySusan(uint8_t target_cup_pos) {
// first move
    if (!has_moved) {
        first_cup_pos = 0;
        ideal_encoder_val = encoder_val; // load first cup starting pos (cup closest to funnel)
        has_moved = 1;
    }
    if (first_cup_pos != target_cup_pos) {
        if (!moving) {
            int8_t next_pow;
            int8_t diff = target_cup_pos - first_cup_pos;
            int8_t sum = target_cup_pos + first_cup_pos + 1; // plus 1 because zero indexed
            if (diff > 0) {
                if (diff > 5) {  // if "far" we go other direction
                    next_pow = -5;  // TODO: may have to reverse
                    target_encoder_val = ideal_encoder_val - ((11 - target_cup_pos + 1) * 6.67);  //TODO: Verify
                } else {
                    // UART_UartPutString("case 2\r\n");
                    next_pow = 3;
                    target_encoder_val = ideal_encoder_val + (diff * 6.67);
                }
            }
            if (diff < 0) {
                if (diff < -5) {
                    // UART_UartPutString("case 3\r\n");
                    next_pow = 3;
                    target_encoder_val = ideal_encoder_val + (11 - first_cup_pos + target_cup_pos + 1) * 6.67;//((sum - first_cup_pos) * 6.5);  //TODO: Verify
                } else {
                    // UART_UartPutString("case 4\r\n");
                    next_pow = -5;
                    target_encoder_val = ideal_encoder_val + (diff * 6.67);  // TODO: Verify signs
                }
            }
            moving = 1;
            set_servo_continuous(LAZY_SUSAN, next_pow); // check servo num
            curr_power = next_pow;
        } // dont process packet if moving
        // uint8_t goal_cup_pos = GetScienceLazySusanPosFromPacket(current);
        // uint32_t tick_goal = QuadDec_2_ReadCounter() + cups_forward(goal_cup_pos, current_cup_pos); 
    }
}

//blocking, bad
//void nextCup() {
//    set_servo_continuous(LAZY_SUSAN, 100);
//    while(QuadDec_2_ReadCounter() < encoder_val + 12) {}
//    set_servo_continuous(LAZY_SUSAN, 0);
//}
//
//void prevCup() {
//    set_servo_continuous(LAZY_SUSAN, -100);
//    while(QuadDec_2_ReadCounter() > encoder_val - 12) {}
//    set_servo_continuous(LAZY_SUSAN, 0);
//} 

/* [] END OF FILE */
