/*******************************************************************************
* File Name: Temp.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Temp_H) /* Pins Temp_H */
#define CY_PINS_Temp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Temp_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Temp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Temp_Read(void);
void    Temp_Write(uint8 value);
uint8   Temp_ReadDataReg(void);
#if defined(Temp__PC) || (CY_PSOC4_4200L) 
    void    Temp_SetDriveMode(uint8 mode);
#endif
void    Temp_SetInterruptMode(uint16 position, uint16 mode);
uint8   Temp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Temp_Sleep(void); 
void Temp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Temp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Temp_DRIVE_MODE_BITS        (3)
    #define Temp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Temp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Temp_SetDriveMode() function.
         *  @{
         */
        #define Temp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Temp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Temp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Temp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Temp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Temp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Temp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Temp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Temp_MASK               Temp__MASK
#define Temp_SHIFT              Temp__SHIFT
#define Temp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Temp_SetInterruptMode() function.
     *  @{
     */
        #define Temp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Temp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Temp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Temp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Temp__SIO)
    #define Temp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Temp__PC) && (CY_PSOC4_4200L)
    #define Temp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Temp_USBIO_DISABLE              ((uint32)(~Temp_USBIO_ENABLE))
    #define Temp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Temp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Temp_USBIO_ENTER_SLEEP          ((uint32)((1u << Temp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Temp_USBIO_SUSPEND_DEL_SHIFT)))
    #define Temp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Temp_USBIO_SUSPEND_SHIFT)))
    #define Temp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Temp_USBIO_SUSPEND_DEL_SHIFT)))
    #define Temp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Temp__PC)
    /* Port Configuration */
    #define Temp_PC                 (* (reg32 *) Temp__PC)
#endif
/* Pin State */
#define Temp_PS                     (* (reg32 *) Temp__PS)
/* Data Register */
#define Temp_DR                     (* (reg32 *) Temp__DR)
/* Input Buffer Disable Override */
#define Temp_INP_DIS                (* (reg32 *) Temp__PC2)

/* Interrupt configuration Registers */
#define Temp_INTCFG                 (* (reg32 *) Temp__INTCFG)
#define Temp_INTSTAT                (* (reg32 *) Temp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Temp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Temp__SIO)
    #define Temp_SIO_REG            (* (reg32 *) Temp__SIO)
#endif /* (Temp__SIO_CFG) */

/* USBIO registers */
#if !defined(Temp__PC) && (CY_PSOC4_4200L)
    #define Temp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Temp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Temp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Temp_DRIVE_MODE_SHIFT       (0x00u)
#define Temp_DRIVE_MODE_MASK        (0x07u << Temp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Temp_H */


/* [] END OF FILE */
