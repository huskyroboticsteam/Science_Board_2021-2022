/*******************************************************************************
* File Name: ERR_LED.h  
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

#if !defined(CY_PINS_ERR_LED_ALIASES_H) /* Pins ERR_LED_ALIASES_H */
#define CY_PINS_ERR_LED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ERR_LED_0			(ERR_LED__0__PC)
#define ERR_LED_0_PS		(ERR_LED__0__PS)
#define ERR_LED_0_PC		(ERR_LED__0__PC)
#define ERR_LED_0_DR		(ERR_LED__0__DR)
#define ERR_LED_0_SHIFT	(ERR_LED__0__SHIFT)
#define ERR_LED_0_INTR	((uint16)((uint16)0x0003u << (ERR_LED__0__SHIFT*2u)))

#define ERR_LED_INTR_ALL	 ((uint16)(ERR_LED_0_INTR))


#endif /* End Pins ERR_LED_ALIASES_H */


/* [] END OF FILE */
