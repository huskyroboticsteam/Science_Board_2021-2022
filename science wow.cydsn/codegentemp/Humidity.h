/*******************************************************************************
* File Name: Humidity.h  
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

#if !defined(CY_PINS_Humidity_H) /* Pins Humidity_H */
#define CY_PINS_Humidity_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Humidity_aliases.h"


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
} Humidity_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Humidity_Read(void);
void    Humidity_Write(uint8 value);
uint8   Humidity_ReadDataReg(void);
#if defined(Humidity__PC) || (CY_PSOC4_4200L) 
    void    Humidity_SetDriveMode(uint8 mode);
#endif
void    Humidity_SetInterruptMode(uint16 position, uint16 mode);
uint8   Humidity_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Humidity_Sleep(void); 
void Humidity_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Humidity__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Humidity_DRIVE_MODE_BITS        (3)
    #define Humidity_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Humidity_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Humidity_SetDriveMode() function.
         *  @{
         */
        #define Humidity_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Humidity_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Humidity_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Humidity_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Humidity_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Humidity_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Humidity_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Humidity_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Humidity_MASK               Humidity__MASK
#define Humidity_SHIFT              Humidity__SHIFT
#define Humidity_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Humidity_SetInterruptMode() function.
     *  @{
     */
        #define Humidity_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Humidity_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Humidity_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Humidity_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Humidity__SIO)
    #define Humidity_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Humidity__PC) && (CY_PSOC4_4200L)
    #define Humidity_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Humidity_USBIO_DISABLE              ((uint32)(~Humidity_USBIO_ENABLE))
    #define Humidity_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Humidity_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Humidity_USBIO_ENTER_SLEEP          ((uint32)((1u << Humidity_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Humidity_USBIO_SUSPEND_DEL_SHIFT)))
    #define Humidity_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Humidity_USBIO_SUSPEND_SHIFT)))
    #define Humidity_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Humidity_USBIO_SUSPEND_DEL_SHIFT)))
    #define Humidity_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Humidity__PC)
    /* Port Configuration */
    #define Humidity_PC                 (* (reg32 *) Humidity__PC)
#endif
/* Pin State */
#define Humidity_PS                     (* (reg32 *) Humidity__PS)
/* Data Register */
#define Humidity_DR                     (* (reg32 *) Humidity__DR)
/* Input Buffer Disable Override */
#define Humidity_INP_DIS                (* (reg32 *) Humidity__PC2)

/* Interrupt configuration Registers */
#define Humidity_INTCFG                 (* (reg32 *) Humidity__INTCFG)
#define Humidity_INTSTAT                (* (reg32 *) Humidity__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Humidity_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Humidity__SIO)
    #define Humidity_SIO_REG            (* (reg32 *) Humidity__SIO)
#endif /* (Humidity__SIO_CFG) */

/* USBIO registers */
#if !defined(Humidity__PC) && (CY_PSOC4_4200L)
    #define Humidity_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Humidity_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Humidity_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Humidity_DRIVE_MODE_SHIFT       (0x00u)
#define Humidity_DRIVE_MODE_MASK        (0x07u << Humidity_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Humidity_H */


/* [] END OF FILE */
