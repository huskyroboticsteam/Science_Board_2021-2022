/*******************************************************************************
* File Name: Debug_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Debug_IntClock_H)
#define CY_CLOCK_Debug_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Debug_IntClock_StartEx(uint32 alignClkDiv);
#define Debug_IntClock_Start() \
    Debug_IntClock_StartEx(Debug_IntClock__PA_DIV_ID)

#else

void Debug_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Debug_IntClock_Stop(void);

void Debug_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Debug_IntClock_GetDividerRegister(void);
uint8  Debug_IntClock_GetFractionalDividerRegister(void);

#define Debug_IntClock_Enable()                         Debug_IntClock_Start()
#define Debug_IntClock_Disable()                        Debug_IntClock_Stop()
#define Debug_IntClock_SetDividerRegister(clkDivider, reset)  \
    Debug_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define Debug_IntClock_SetDivider(clkDivider)           Debug_IntClock_SetDividerRegister((clkDivider), 1u)
#define Debug_IntClock_SetDividerValue(clkDivider)      Debug_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Debug_IntClock_DIV_ID     Debug_IntClock__DIV_ID

#define Debug_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Debug_IntClock_CTRL_REG   (*(reg32 *)Debug_IntClock__CTRL_REGISTER)
#define Debug_IntClock_DIV_REG    (*(reg32 *)Debug_IntClock__DIV_REGISTER)

#define Debug_IntClock_CMD_DIV_SHIFT          (0u)
#define Debug_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define Debug_IntClock_CMD_DISABLE_SHIFT      (30u)
#define Debug_IntClock_CMD_ENABLE_SHIFT       (31u)

#define Debug_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Debug_IntClock_CMD_DISABLE_SHIFT))
#define Debug_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Debug_IntClock_CMD_ENABLE_SHIFT))

#define Debug_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define Debug_IntClock_DIV_FRAC_SHIFT (3u)
#define Debug_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define Debug_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define Debug_IntClock_DIV_REG        (*(reg32 *)Debug_IntClock__REGISTER)
#define Debug_IntClock_ENABLE_REG     Debug_IntClock_DIV_REG
#define Debug_IntClock_DIV_FRAC_MASK  Debug_IntClock__FRAC_MASK
#define Debug_IntClock_DIV_FRAC_SHIFT (16u)
#define Debug_IntClock_DIV_INT_MASK   Debug_IntClock__DIVIDER_MASK
#define Debug_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Debug_IntClock_H) */

/* [] END OF FILE */
