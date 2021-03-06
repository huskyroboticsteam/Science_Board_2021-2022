/*******************************************************************************
* File Name: DBG_LED.h  
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

#if !defined(CY_PINS_DBG_LED_H) /* Pins DBG_LED_H */
#define CY_PINS_DBG_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DBG_LED_aliases.h"


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
} DBG_LED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DBG_LED_Read(void);
void    DBG_LED_Write(uint8 value);
uint8   DBG_LED_ReadDataReg(void);
#if defined(DBG_LED__PC) || (CY_PSOC4_4200L) 
    void    DBG_LED_SetDriveMode(uint8 mode);
#endif
void    DBG_LED_SetInterruptMode(uint16 position, uint16 mode);
uint8   DBG_LED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DBG_LED_Sleep(void); 
void DBG_LED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DBG_LED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DBG_LED_DRIVE_MODE_BITS        (3)
    #define DBG_LED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DBG_LED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DBG_LED_SetDriveMode() function.
         *  @{
         */
        #define DBG_LED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DBG_LED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DBG_LED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DBG_LED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DBG_LED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DBG_LED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DBG_LED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DBG_LED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DBG_LED_MASK               DBG_LED__MASK
#define DBG_LED_SHIFT              DBG_LED__SHIFT
#define DBG_LED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DBG_LED_SetInterruptMode() function.
     *  @{
     */
        #define DBG_LED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DBG_LED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DBG_LED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DBG_LED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DBG_LED__SIO)
    #define DBG_LED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DBG_LED__PC) && (CY_PSOC4_4200L)
    #define DBG_LED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DBG_LED_USBIO_DISABLE              ((uint32)(~DBG_LED_USBIO_ENABLE))
    #define DBG_LED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DBG_LED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DBG_LED_USBIO_ENTER_SLEEP          ((uint32)((1u << DBG_LED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DBG_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define DBG_LED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DBG_LED_USBIO_SUSPEND_SHIFT)))
    #define DBG_LED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DBG_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define DBG_LED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DBG_LED__PC)
    /* Port Configuration */
    #define DBG_LED_PC                 (* (reg32 *) DBG_LED__PC)
#endif
/* Pin State */
#define DBG_LED_PS                     (* (reg32 *) DBG_LED__PS)
/* Data Register */
#define DBG_LED_DR                     (* (reg32 *) DBG_LED__DR)
/* Input Buffer Disable Override */
#define DBG_LED_INP_DIS                (* (reg32 *) DBG_LED__PC2)

/* Interrupt configuration Registers */
#define DBG_LED_INTCFG                 (* (reg32 *) DBG_LED__INTCFG)
#define DBG_LED_INTSTAT                (* (reg32 *) DBG_LED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DBG_LED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DBG_LED__SIO)
    #define DBG_LED_SIO_REG            (* (reg32 *) DBG_LED__SIO)
#endif /* (DBG_LED__SIO_CFG) */

/* USBIO registers */
#if !defined(DBG_LED__PC) && (CY_PSOC4_4200L)
    #define DBG_LED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DBG_LED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DBG_LED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DBG_LED_DRIVE_MODE_SHIFT       (0x00u)
#define DBG_LED_DRIVE_MODE_MASK        (0x07u << DBG_LED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DBG_LED_H */


/* [] END OF FILE */
