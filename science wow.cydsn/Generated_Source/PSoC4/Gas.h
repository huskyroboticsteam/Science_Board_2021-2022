/*******************************************************************************
* File Name: Gas.h  
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

#if !defined(CY_PINS_Gas_H) /* Pins Gas_H */
#define CY_PINS_Gas_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Gas_aliases.h"


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
} Gas_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Gas_Read(void);
void    Gas_Write(uint8 value);
uint8   Gas_ReadDataReg(void);
#if defined(Gas__PC) || (CY_PSOC4_4200L) 
    void    Gas_SetDriveMode(uint8 mode);
#endif
void    Gas_SetInterruptMode(uint16 position, uint16 mode);
uint8   Gas_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Gas_Sleep(void); 
void Gas_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Gas__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Gas_DRIVE_MODE_BITS        (3)
    #define Gas_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Gas_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Gas_SetDriveMode() function.
         *  @{
         */
        #define Gas_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Gas_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Gas_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Gas_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Gas_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Gas_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Gas_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Gas_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Gas_MASK               Gas__MASK
#define Gas_SHIFT              Gas__SHIFT
#define Gas_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Gas_SetInterruptMode() function.
     *  @{
     */
        #define Gas_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Gas_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Gas_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Gas_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Gas__SIO)
    #define Gas_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Gas__PC) && (CY_PSOC4_4200L)
    #define Gas_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Gas_USBIO_DISABLE              ((uint32)(~Gas_USBIO_ENABLE))
    #define Gas_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Gas_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Gas_USBIO_ENTER_SLEEP          ((uint32)((1u << Gas_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Gas_USBIO_SUSPEND_DEL_SHIFT)))
    #define Gas_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Gas_USBIO_SUSPEND_SHIFT)))
    #define Gas_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Gas_USBIO_SUSPEND_DEL_SHIFT)))
    #define Gas_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Gas__PC)
    /* Port Configuration */
    #define Gas_PC                 (* (reg32 *) Gas__PC)
#endif
/* Pin State */
#define Gas_PS                     (* (reg32 *) Gas__PS)
/* Data Register */
#define Gas_DR                     (* (reg32 *) Gas__DR)
/* Input Buffer Disable Override */
#define Gas_INP_DIS                (* (reg32 *) Gas__PC2)

/* Interrupt configuration Registers */
#define Gas_INTCFG                 (* (reg32 *) Gas__INTCFG)
#define Gas_INTSTAT                (* (reg32 *) Gas__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Gas_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Gas__SIO)
    #define Gas_SIO_REG            (* (reg32 *) Gas__SIO)
#endif /* (Gas__SIO_CFG) */

/* USBIO registers */
#if !defined(Gas__PC) && (CY_PSOC4_4200L)
    #define Gas_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Gas_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Gas_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Gas_DRIVE_MODE_SHIFT       (0x00u)
#define Gas_DRIVE_MODE_MASK        (0x07u << Gas_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Gas_H */


/* [] END OF FILE */
