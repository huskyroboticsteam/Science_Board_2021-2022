/*******************************************************************************
* File Name: LIM1.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LIM1.h"

static LIM1_BACKUP_STRUCT  LIM1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LIM1_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet LIM1_SUT.c usage_LIM1_Sleep_Wakeup
*******************************************************************************/
void LIM1_Sleep(void)
{
    #if defined(LIM1__PC)
        LIM1_backup.pcState = LIM1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LIM1_backup.usbState = LIM1_CR1_REG;
            LIM1_USB_POWER_REG |= LIM1_USBIO_ENTER_SLEEP;
            LIM1_CR1_REG &= LIM1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LIM1__SIO)
        LIM1_backup.sioState = LIM1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LIM1_SIO_REG &= (uint32)(~LIM1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LIM1_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to LIM1_Sleep() for an example usage.
*******************************************************************************/
void LIM1_Wakeup(void)
{
    #if defined(LIM1__PC)
        LIM1_PC = LIM1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LIM1_USB_POWER_REG &= LIM1_USBIO_EXIT_SLEEP_PH1;
            LIM1_CR1_REG = LIM1_backup.usbState;
            LIM1_USB_POWER_REG &= LIM1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LIM1__SIO)
        LIM1_SIO_REG = LIM1_backup.sioState;
    #endif
}


/* [] END OF FILE */
