/*******************************************************************************
* File Name: Temp.h  
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

#if !defined(CY_PINS_Temp_ALIASES_H) /* Pins Temp_ALIASES_H */
#define CY_PINS_Temp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Temp_0			(Temp__0__PC)
#define Temp_0_PS		(Temp__0__PS)
#define Temp_0_PC		(Temp__0__PC)
#define Temp_0_DR		(Temp__0__DR)
#define Temp_0_SHIFT	(Temp__0__SHIFT)
#define Temp_0_INTR	((uint16)((uint16)0x0003u << (Temp__0__SHIFT*2u)))

#define Temp_INTR_ALL	 ((uint16)(Temp_0_INTR))


#endif /* End Pins Temp_ALIASES_H */


/* [] END OF FILE */
