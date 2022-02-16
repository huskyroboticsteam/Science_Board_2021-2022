/*******************************************************************************
* File Name: LIMSW.h  
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

#if !defined(CY_PINS_LIMSW_ALIASES_H) /* Pins LIMSW_ALIASES_H */
#define CY_PINS_LIMSW_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LIMSW_0			(LIMSW__0__PC)
#define LIMSW_0_PS		(LIMSW__0__PS)
#define LIMSW_0_PC		(LIMSW__0__PC)
#define LIMSW_0_DR		(LIMSW__0__DR)
#define LIMSW_0_SHIFT	(LIMSW__0__SHIFT)
#define LIMSW_0_INTR	((uint16)((uint16)0x0003u << (LIMSW__0__SHIFT*2u)))

#define LIMSW_INTR_ALL	 ((uint16)(LIMSW_0_INTR))


#endif /* End Pins LIMSW_ALIASES_H */


/* [] END OF FILE */
