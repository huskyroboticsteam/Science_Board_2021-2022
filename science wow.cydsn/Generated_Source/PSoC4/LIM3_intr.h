/*******************************************************************************
* File Name: LIM3_intr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_LIM3_intr_H)
#define CY_ISR_LIM3_intr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LIM3_intr_Start(void);
void LIM3_intr_StartEx(cyisraddress address);
void LIM3_intr_Stop(void);

CY_ISR_PROTO(LIM3_intr_Interrupt);

void LIM3_intr_SetVector(cyisraddress address);
cyisraddress LIM3_intr_GetVector(void);

void LIM3_intr_SetPriority(uint8 priority);
uint8 LIM3_intr_GetPriority(void);

void LIM3_intr_Enable(void);
uint8 LIM3_intr_GetState(void);
void LIM3_intr_Disable(void);

void LIM3_intr_SetPending(void);
void LIM3_intr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LIM3_intr ISR. */
#define LIM3_intr_INTC_VECTOR            ((reg32 *) LIM3_intr__INTC_VECT)

/* Address of the LIM3_intr ISR priority. */
#define LIM3_intr_INTC_PRIOR             ((reg32 *) LIM3_intr__INTC_PRIOR_REG)

/* Priority of the LIM3_intr interrupt. */
#define LIM3_intr_INTC_PRIOR_NUMBER      LIM3_intr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LIM3_intr interrupt. */
#define LIM3_intr_INTC_SET_EN            ((reg32 *) LIM3_intr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LIM3_intr interrupt. */
#define LIM3_intr_INTC_CLR_EN            ((reg32 *) LIM3_intr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LIM3_intr interrupt state to pending. */
#define LIM3_intr_INTC_SET_PD            ((reg32 *) LIM3_intr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LIM3_intr interrupt. */
#define LIM3_intr_INTC_CLR_PD            ((reg32 *) LIM3_intr__INTC_CLR_PD_REG)



#endif /* CY_ISR_LIM3_intr_H */


/* [] END OF FILE */
