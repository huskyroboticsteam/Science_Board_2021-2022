/*******************************************************************************
* File Name: LIMSW.h  
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

#if !defined(CY_PINS_LIMSW_H) /* Pins LIMSW_H */
#define CY_PINS_LIMSW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LIMSW_aliases.h"


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
} LIMSW_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   LIMSW_Read(void);
void    LIMSW_Write(uint8 value);
uint8   LIMSW_ReadDataReg(void);
#if defined(LIMSW__PC) || (CY_PSOC4_4200L) 
    void    LIMSW_SetDriveMode(uint8 mode);
#endif
void    LIMSW_SetInterruptMode(uint16 position, uint16 mode);
uint8   LIMSW_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void LIMSW_Sleep(void); 
void LIMSW_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(LIMSW__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define LIMSW_DRIVE_MODE_BITS        (3)
    #define LIMSW_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LIMSW_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the LIMSW_SetDriveMode() function.
         *  @{
         */
        #define LIMSW_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define LIMSW_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define LIMSW_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define LIMSW_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define LIMSW_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define LIMSW_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define LIMSW_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define LIMSW_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define LIMSW_MASK               LIMSW__MASK
#define LIMSW_SHIFT              LIMSW__SHIFT
#define LIMSW_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LIMSW_SetInterruptMode() function.
     *  @{
     */
        #define LIMSW_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define LIMSW_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define LIMSW_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define LIMSW_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(LIMSW__SIO)
    #define LIMSW_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(LIMSW__PC) && (CY_PSOC4_4200L)
    #define LIMSW_USBIO_ENABLE               ((uint32)0x80000000u)
    #define LIMSW_USBIO_DISABLE              ((uint32)(~LIMSW_USBIO_ENABLE))
    #define LIMSW_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define LIMSW_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define LIMSW_USBIO_ENTER_SLEEP          ((uint32)((1u << LIMSW_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << LIMSW_USBIO_SUSPEND_DEL_SHIFT)))
    #define LIMSW_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << LIMSW_USBIO_SUSPEND_SHIFT)))
    #define LIMSW_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << LIMSW_USBIO_SUSPEND_DEL_SHIFT)))
    #define LIMSW_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(LIMSW__PC)
    /* Port Configuration */
    #define LIMSW_PC                 (* (reg32 *) LIMSW__PC)
#endif
/* Pin State */
#define LIMSW_PS                     (* (reg32 *) LIMSW__PS)
/* Data Register */
#define LIMSW_DR                     (* (reg32 *) LIMSW__DR)
/* Input Buffer Disable Override */
#define LIMSW_INP_DIS                (* (reg32 *) LIMSW__PC2)

/* Interrupt configuration Registers */
#define LIMSW_INTCFG                 (* (reg32 *) LIMSW__INTCFG)
#define LIMSW_INTSTAT                (* (reg32 *) LIMSW__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define LIMSW_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(LIMSW__SIO)
    #define LIMSW_SIO_REG            (* (reg32 *) LIMSW__SIO)
#endif /* (LIMSW__SIO_CFG) */

/* USBIO registers */
#if !defined(LIMSW__PC) && (CY_PSOC4_4200L)
    #define LIMSW_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define LIMSW_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define LIMSW_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define LIMSW_DRIVE_MODE_SHIFT       (0x00u)
#define LIMSW_DRIVE_MODE_MASK        (0x07u << LIMSW_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins LIMSW_H */


/* [] END OF FILE */
