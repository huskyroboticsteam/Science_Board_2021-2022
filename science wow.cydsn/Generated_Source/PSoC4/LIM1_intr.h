/*******************************************************************************
* File Name: LIM1_intr.h
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
#if !defined(CY_ISR_LIM1_intr_H)
#define CY_ISR_LIM1_intr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LIM1_intr_Start(void);
void LIM1_intr_StartEx(cyisraddress address);
void LIM1_intr_Stop(void);

CY_ISR_PROTO(LIM1_intr_Interrupt);

void LIM1_intr_SetVector(cyisraddress address);
cyisraddress LIM1_intr_GetVector(void);

void LIM1_intr_SetPriority(uint8 priority);
uint8 LIM1_intr_GetPriority(void);

void LIM1_intr_Enable(void);
uint8 LIM1_intr_GetState(void);
void LIM1_intr_Disable(void);

void LIM1_intr_SetPending(void);
void LIM1_intr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LIM1_intr ISR. */
#define LIM1_intr_INTC_VECTOR            ((reg32 *) LIM1_intr__INTC_VECT)

/* Address of the LIM1_intr ISR priority. */
#define LIM1_intr_INTC_PRIOR             ((reg32 *) LIM1_intr__INTC_PRIOR_REG)

/* Priority of the LIM1_intr interrupt. */
#define LIM1_intr_INTC_PRIOR_NUMBER      LIM1_intr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LIM1_intr interrupt. */
#define LIM1_intr_INTC_SET_EN            ((reg32 *) LIM1_intr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LIM1_intr interrupt. */
#define LIM1_intr_INTC_CLR_EN            ((reg32 *) LIM1_intr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LIM1_intr interrupt state to pending. */
#define LIM1_intr_INTC_SET_PD            ((reg32 *) LIM1_intr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LIM1_intr interrupt. */
#define LIM1_intr_INTC_CLR_PD            ((reg32 *) LIM1_intr__INTC_CLR_PD_REG)



#endif /* CY_ISR_LIM1_intr_H */


/* [] END OF FILE */
