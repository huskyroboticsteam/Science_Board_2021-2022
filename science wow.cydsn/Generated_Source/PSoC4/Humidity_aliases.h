/*******************************************************************************
* File Name: Humidity.h  
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

#if !defined(CY_PINS_Humidity_ALIASES_H) /* Pins Humidity_ALIASES_H */
#define CY_PINS_Humidity_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Humidity_0			(Humidity__0__PC)
#define Humidity_0_PS		(Humidity__0__PS)
#define Humidity_0_PC		(Humidity__0__PC)
#define Humidity_0_DR		(Humidity__0__DR)
#define Humidity_0_SHIFT	(Humidity__0__SHIFT)
#define Humidity_0_INTR	((uint16)((uint16)0x0003u << (Humidity__0__SHIFT*2u)))

#define Humidity_INTR_ALL	 ((uint16)(Humidity_0_INTR))


#endif /* End Pins Humidity_ALIASES_H */


/* [] END OF FILE */
