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

#include <stdint.h>

#ifndef __MAIN__
#define __MAIN__
    
#define Print(message) DBG_UART_UartPutString(message)
#define PrintChar(character) DBG_UART_UartPutChar(character)
#define PrintInt(integer) DBG_UART_UartPutString(itoa(integer, txData, 10))
#define PrintIntBin(integer) DBG_UART_UartPutString(itoa(integer, txData, 2))

#define LED_COLOR_ID 0xF7
#define TICKS_TO_NEXT_CUP 20
#define LED_ON 1
#define LED_OFF 0
    
void DebugPrint(char input);

void setLazySusan(uint8_t target_cup_pos);
    
#endif // __MAIN__


/* [] END OF FILE */
