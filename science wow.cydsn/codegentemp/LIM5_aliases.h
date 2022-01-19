/*******************************************************************************
* File Name: LIM5.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LIM5_ALIASES_H) /* Pins LIM5_ALIASES_H */
#define CY_PINS_LIM5_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LIM5_0			(LIM5__0__PC)
#define LIM5_0_PS		(LIM5__0__PS)
#define LIM5_0_PC		(LIM5__0__PC)
#define LIM5_0_DR		(LIM5__0__DR)
#define LIM5_0_SHIFT	(LIM5__0__SHIFT)
#define LIM5_0_INTR	((uint16)((uint16)0x0003u << (LIM5__0__SHIFT*2u)))

#define LIM5_INTR_ALL	 ((uint16)(LIM5_0_INTR))


#endif /* End Pins LIM5_ALIASES_H */


/* [] END OF FILE */
