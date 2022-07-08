/*******************************************************************************
* File Name: Sensor_Packet_Handler.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Sensor_Packet_Handler
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_Sensor_Packet_Handler_H)
#define CY_TCPWM_Sensor_Packet_Handler_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Sensor_Packet_Handler_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Sensor_Packet_Handler_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Sensor_Packet_Handler_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Sensor_Packet_Handler_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Sensor_Packet_Handler_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Sensor_Packet_Handler_QUAD_ENCODING_MODES            (0lu)
#define Sensor_Packet_Handler_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Sensor_Packet_Handler_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Sensor_Packet_Handler_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Sensor_Packet_Handler_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Sensor_Packet_Handler_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Sensor_Packet_Handler_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Sensor_Packet_Handler_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Sensor_Packet_Handler_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Sensor_Packet_Handler_TC_RUN_MODE                    (0lu)
#define Sensor_Packet_Handler_TC_COUNTER_MODE                (0lu)
#define Sensor_Packet_Handler_TC_COMP_CAP_MODE               (0lu)
#define Sensor_Packet_Handler_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Sensor_Packet_Handler_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Sensor_Packet_Handler_TC_COUNT_SIGNAL_MODE           (1lu)
#define Sensor_Packet_Handler_TC_START_SIGNAL_MODE           (0lu)
#define Sensor_Packet_Handler_TC_STOP_SIGNAL_MODE            (0lu)
#define Sensor_Packet_Handler_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Sensor_Packet_Handler_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Sensor_Packet_Handler_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Sensor_Packet_Handler_TC_START_SIGNAL_PRESENT        (0lu)
#define Sensor_Packet_Handler_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Sensor_Packet_Handler_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Sensor_Packet_Handler_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define Sensor_Packet_Handler_PWM_KILL_EVENT                 (0lu)
#define Sensor_Packet_Handler_PWM_STOP_EVENT                 (0lu)
#define Sensor_Packet_Handler_PWM_MODE                       (4lu)
#define Sensor_Packet_Handler_PWM_OUT_N_INVERT               (0lu)
#define Sensor_Packet_Handler_PWM_OUT_INVERT                 (0lu)
#define Sensor_Packet_Handler_PWM_ALIGN                      (0lu)
#define Sensor_Packet_Handler_PWM_RUN_MODE                   (0lu)
#define Sensor_Packet_Handler_PWM_DEAD_TIME_CYCLE            (0lu)
#define Sensor_Packet_Handler_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Sensor_Packet_Handler_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Sensor_Packet_Handler_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Sensor_Packet_Handler_PWM_START_SIGNAL_MODE          (0lu)
#define Sensor_Packet_Handler_PWM_STOP_SIGNAL_MODE           (0lu)
#define Sensor_Packet_Handler_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Sensor_Packet_Handler_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Sensor_Packet_Handler_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Sensor_Packet_Handler_PWM_START_SIGNAL_PRESENT       (0lu)
#define Sensor_Packet_Handler_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Sensor_Packet_Handler_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Sensor_Packet_Handler_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Sensor_Packet_Handler_TC_PERIOD_VALUE                (65535lu)
#define Sensor_Packet_Handler_TC_COMPARE_VALUE               (65535lu)
#define Sensor_Packet_Handler_TC_COMPARE_BUF_VALUE           (65535lu)
#define Sensor_Packet_Handler_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Sensor_Packet_Handler_PWM_PERIOD_VALUE               (65535lu)
#define Sensor_Packet_Handler_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Sensor_Packet_Handler_PWM_PERIOD_SWAP                (0lu)
#define Sensor_Packet_Handler_PWM_COMPARE_VALUE              (65535lu)
#define Sensor_Packet_Handler_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Sensor_Packet_Handler_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Sensor_Packet_Handler__LEFT 0
#define Sensor_Packet_Handler__RIGHT 1
#define Sensor_Packet_Handler__CENTER 2
#define Sensor_Packet_Handler__ASYMMETRIC 3

#define Sensor_Packet_Handler__X1 0
#define Sensor_Packet_Handler__X2 1
#define Sensor_Packet_Handler__X4 2

#define Sensor_Packet_Handler__PWM 4
#define Sensor_Packet_Handler__PWM_DT 5
#define Sensor_Packet_Handler__PWM_PR 6

#define Sensor_Packet_Handler__INVERSE 1
#define Sensor_Packet_Handler__DIRECT 0

#define Sensor_Packet_Handler__CAPTURE 2
#define Sensor_Packet_Handler__COMPARE 0

#define Sensor_Packet_Handler__TRIG_LEVEL 3
#define Sensor_Packet_Handler__TRIG_RISING 0
#define Sensor_Packet_Handler__TRIG_FALLING 1
#define Sensor_Packet_Handler__TRIG_BOTH 2

#define Sensor_Packet_Handler__INTR_MASK_TC 1
#define Sensor_Packet_Handler__INTR_MASK_CC_MATCH 2
#define Sensor_Packet_Handler__INTR_MASK_NONE 0
#define Sensor_Packet_Handler__INTR_MASK_TC_CC 3

#define Sensor_Packet_Handler__UNCONFIG 8
#define Sensor_Packet_Handler__TIMER 1
#define Sensor_Packet_Handler__QUAD 3
#define Sensor_Packet_Handler__PWM_SEL 7

#define Sensor_Packet_Handler__COUNT_UP 0
#define Sensor_Packet_Handler__COUNT_DOWN 1
#define Sensor_Packet_Handler__COUNT_UPDOWN0 2
#define Sensor_Packet_Handler__COUNT_UPDOWN1 3


/* Prescaler */
#define Sensor_Packet_Handler_PRESCALE_DIVBY1                ((uint32)(0u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY2                ((uint32)(1u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY4                ((uint32)(2u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY8                ((uint32)(3u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY16               ((uint32)(4u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY32               ((uint32)(5u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY64               ((uint32)(6u << Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_PRESCALE_DIVBY128              ((uint32)(7u << Sensor_Packet_Handler_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Sensor_Packet_Handler_MODE_TIMER_COMPARE             ((uint32)(Sensor_Packet_Handler__COMPARE         <<  \
                                                                  Sensor_Packet_Handler_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_TIMER_CAPTURE             ((uint32)(Sensor_Packet_Handler__CAPTURE         <<  \
                                                                  Sensor_Packet_Handler_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_QUAD                      ((uint32)(Sensor_Packet_Handler__QUAD            <<  \
                                                                  Sensor_Packet_Handler_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_PWM                       ((uint32)(Sensor_Packet_Handler__PWM             <<  \
                                                                  Sensor_Packet_Handler_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_PWM_DT                    ((uint32)(Sensor_Packet_Handler__PWM_DT          <<  \
                                                                  Sensor_Packet_Handler_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_PWM_PR                    ((uint32)(Sensor_Packet_Handler__PWM_PR          <<  \
                                                                  Sensor_Packet_Handler_MODE_SHIFT))

/* Quad Modes */
#define Sensor_Packet_Handler_MODE_X1                        ((uint32)(Sensor_Packet_Handler__X1              <<  \
                                                                  Sensor_Packet_Handler_QUAD_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_X2                        ((uint32)(Sensor_Packet_Handler__X2              <<  \
                                                                  Sensor_Packet_Handler_QUAD_MODE_SHIFT))
#define Sensor_Packet_Handler_MODE_X4                        ((uint32)(Sensor_Packet_Handler__X4              <<  \
                                                                  Sensor_Packet_Handler_QUAD_MODE_SHIFT))

/* Counter modes */
#define Sensor_Packet_Handler_COUNT_UP                       ((uint32)(Sensor_Packet_Handler__COUNT_UP        <<  \
                                                                  Sensor_Packet_Handler_UPDOWN_SHIFT))
#define Sensor_Packet_Handler_COUNT_DOWN                     ((uint32)(Sensor_Packet_Handler__COUNT_DOWN      <<  \
                                                                  Sensor_Packet_Handler_UPDOWN_SHIFT))
#define Sensor_Packet_Handler_COUNT_UPDOWN0                  ((uint32)(Sensor_Packet_Handler__COUNT_UPDOWN0   <<  \
                                                                  Sensor_Packet_Handler_UPDOWN_SHIFT))
#define Sensor_Packet_Handler_COUNT_UPDOWN1                  ((uint32)(Sensor_Packet_Handler__COUNT_UPDOWN1   <<  \
                                                                  Sensor_Packet_Handler_UPDOWN_SHIFT))

/* PWM output invert */
#define Sensor_Packet_Handler_INVERT_LINE                    ((uint32)(Sensor_Packet_Handler__INVERSE         <<  \
                                                                  Sensor_Packet_Handler_INV_OUT_SHIFT))
#define Sensor_Packet_Handler_INVERT_LINE_N                  ((uint32)(Sensor_Packet_Handler__INVERSE         <<  \
                                                                  Sensor_Packet_Handler_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Sensor_Packet_Handler_TRIG_RISING                    ((uint32)Sensor_Packet_Handler__TRIG_RISING)
#define Sensor_Packet_Handler_TRIG_FALLING                   ((uint32)Sensor_Packet_Handler__TRIG_FALLING)
#define Sensor_Packet_Handler_TRIG_BOTH                      ((uint32)Sensor_Packet_Handler__TRIG_BOTH)
#define Sensor_Packet_Handler_TRIG_LEVEL                     ((uint32)Sensor_Packet_Handler__TRIG_LEVEL)

/* Interrupt mask */
#define Sensor_Packet_Handler_INTR_MASK_TC                   ((uint32)Sensor_Packet_Handler__INTR_MASK_TC)
#define Sensor_Packet_Handler_INTR_MASK_CC_MATCH             ((uint32)Sensor_Packet_Handler__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Sensor_Packet_Handler_CC_MATCH_SET                   (0x00u)
#define Sensor_Packet_Handler_CC_MATCH_CLEAR                 (0x01u)
#define Sensor_Packet_Handler_CC_MATCH_INVERT                (0x02u)
#define Sensor_Packet_Handler_CC_MATCH_NO_CHANGE             (0x03u)
#define Sensor_Packet_Handler_OVERLOW_SET                    (0x00u)
#define Sensor_Packet_Handler_OVERLOW_CLEAR                  (0x04u)
#define Sensor_Packet_Handler_OVERLOW_INVERT                 (0x08u)
#define Sensor_Packet_Handler_OVERLOW_NO_CHANGE              (0x0Cu)
#define Sensor_Packet_Handler_UNDERFLOW_SET                  (0x00u)
#define Sensor_Packet_Handler_UNDERFLOW_CLEAR                (0x10u)
#define Sensor_Packet_Handler_UNDERFLOW_INVERT               (0x20u)
#define Sensor_Packet_Handler_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Sensor_Packet_Handler_PWM_MODE_LEFT                  (Sensor_Packet_Handler_CC_MATCH_CLEAR        |   \
                                                         Sensor_Packet_Handler_OVERLOW_SET           |   \
                                                         Sensor_Packet_Handler_UNDERFLOW_NO_CHANGE)
#define Sensor_Packet_Handler_PWM_MODE_RIGHT                 (Sensor_Packet_Handler_CC_MATCH_SET          |   \
                                                         Sensor_Packet_Handler_OVERLOW_NO_CHANGE     |   \
                                                         Sensor_Packet_Handler_UNDERFLOW_CLEAR)
#define Sensor_Packet_Handler_PWM_MODE_ASYM                  (Sensor_Packet_Handler_CC_MATCH_INVERT       |   \
                                                         Sensor_Packet_Handler_OVERLOW_SET           |   \
                                                         Sensor_Packet_Handler_UNDERFLOW_CLEAR)

#if (Sensor_Packet_Handler_CY_TCPWM_V2)
    #if(Sensor_Packet_Handler_CY_TCPWM_4000)
        #define Sensor_Packet_Handler_PWM_MODE_CENTER                (Sensor_Packet_Handler_CC_MATCH_INVERT       |   \
                                                                 Sensor_Packet_Handler_OVERLOW_NO_CHANGE     |   \
                                                                 Sensor_Packet_Handler_UNDERFLOW_CLEAR)
    #else
        #define Sensor_Packet_Handler_PWM_MODE_CENTER                (Sensor_Packet_Handler_CC_MATCH_INVERT       |   \
                                                                 Sensor_Packet_Handler_OVERLOW_SET           |   \
                                                                 Sensor_Packet_Handler_UNDERFLOW_CLEAR)
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */
#else
    #define Sensor_Packet_Handler_PWM_MODE_CENTER                (Sensor_Packet_Handler_CC_MATCH_INVERT       |   \
                                                             Sensor_Packet_Handler_OVERLOW_NO_CHANGE     |   \
                                                             Sensor_Packet_Handler_UNDERFLOW_CLEAR)
#endif /* (Sensor_Packet_Handler_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Sensor_Packet_Handler_CMD_CAPTURE                    (0u)
#define Sensor_Packet_Handler_CMD_RELOAD                     (8u)
#define Sensor_Packet_Handler_CMD_STOP                       (16u)
#define Sensor_Packet_Handler_CMD_START                      (24u)

/* Status */
#define Sensor_Packet_Handler_STATUS_DOWN                    (1u)
#define Sensor_Packet_Handler_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Sensor_Packet_Handler_Init(void);
void   Sensor_Packet_Handler_Enable(void);
void   Sensor_Packet_Handler_Start(void);
void   Sensor_Packet_Handler_Stop(void);

void   Sensor_Packet_Handler_SetMode(uint32 mode);
void   Sensor_Packet_Handler_SetCounterMode(uint32 counterMode);
void   Sensor_Packet_Handler_SetPWMMode(uint32 modeMask);
void   Sensor_Packet_Handler_SetQDMode(uint32 qdMode);

void   Sensor_Packet_Handler_SetPrescaler(uint32 prescaler);
void   Sensor_Packet_Handler_TriggerCommand(uint32 mask, uint32 command);
void   Sensor_Packet_Handler_SetOneShot(uint32 oneShotEnable);
uint32 Sensor_Packet_Handler_ReadStatus(void);

void   Sensor_Packet_Handler_SetPWMSyncKill(uint32 syncKillEnable);
void   Sensor_Packet_Handler_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Sensor_Packet_Handler_SetPWMDeadTime(uint32 deadTime);
void   Sensor_Packet_Handler_SetPWMInvert(uint32 mask);

void   Sensor_Packet_Handler_SetInterruptMode(uint32 interruptMask);
uint32 Sensor_Packet_Handler_GetInterruptSourceMasked(void);
uint32 Sensor_Packet_Handler_GetInterruptSource(void);
void   Sensor_Packet_Handler_ClearInterrupt(uint32 interruptMask);
void   Sensor_Packet_Handler_SetInterrupt(uint32 interruptMask);

void   Sensor_Packet_Handler_WriteCounter(uint32 count);
uint32 Sensor_Packet_Handler_ReadCounter(void);

uint32 Sensor_Packet_Handler_ReadCapture(void);
uint32 Sensor_Packet_Handler_ReadCaptureBuf(void);

void   Sensor_Packet_Handler_WritePeriod(uint32 period);
uint32 Sensor_Packet_Handler_ReadPeriod(void);
void   Sensor_Packet_Handler_WritePeriodBuf(uint32 periodBuf);
uint32 Sensor_Packet_Handler_ReadPeriodBuf(void);

void   Sensor_Packet_Handler_WriteCompare(uint32 compare);
uint32 Sensor_Packet_Handler_ReadCompare(void);
void   Sensor_Packet_Handler_WriteCompareBuf(uint32 compareBuf);
uint32 Sensor_Packet_Handler_ReadCompareBuf(void);

void   Sensor_Packet_Handler_SetPeriodSwap(uint32 swapEnable);
void   Sensor_Packet_Handler_SetCompareSwap(uint32 swapEnable);

void   Sensor_Packet_Handler_SetCaptureMode(uint32 triggerMode);
void   Sensor_Packet_Handler_SetReloadMode(uint32 triggerMode);
void   Sensor_Packet_Handler_SetStartMode(uint32 triggerMode);
void   Sensor_Packet_Handler_SetStopMode(uint32 triggerMode);
void   Sensor_Packet_Handler_SetCountMode(uint32 triggerMode);

void   Sensor_Packet_Handler_SaveConfig(void);
void   Sensor_Packet_Handler_RestoreConfig(void);
void   Sensor_Packet_Handler_Sleep(void);
void   Sensor_Packet_Handler_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Sensor_Packet_Handler_BLOCK_CONTROL_REG              (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Sensor_Packet_Handler_BLOCK_CONTROL_PTR              ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Sensor_Packet_Handler_COMMAND_REG                    (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Sensor_Packet_Handler_COMMAND_PTR                    ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Sensor_Packet_Handler_INTRRUPT_CAUSE_REG             (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Sensor_Packet_Handler_INTRRUPT_CAUSE_PTR             ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Sensor_Packet_Handler_CONTROL_REG                    (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__CTRL )
#define Sensor_Packet_Handler_CONTROL_PTR                    ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__CTRL )
#define Sensor_Packet_Handler_STATUS_REG                     (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__STATUS )
#define Sensor_Packet_Handler_STATUS_PTR                     ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__STATUS )
#define Sensor_Packet_Handler_COUNTER_REG                    (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__COUNTER )
#define Sensor_Packet_Handler_COUNTER_PTR                    ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__COUNTER )
#define Sensor_Packet_Handler_COMP_CAP_REG                   (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__CC )
#define Sensor_Packet_Handler_COMP_CAP_PTR                   ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__CC )
#define Sensor_Packet_Handler_COMP_CAP_BUF_REG               (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__CC_BUFF )
#define Sensor_Packet_Handler_COMP_CAP_BUF_PTR               ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__CC_BUFF )
#define Sensor_Packet_Handler_PERIOD_REG                     (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__PERIOD )
#define Sensor_Packet_Handler_PERIOD_PTR                     ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__PERIOD )
#define Sensor_Packet_Handler_PERIOD_BUF_REG                 (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Sensor_Packet_Handler_PERIOD_BUF_PTR                 ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Sensor_Packet_Handler_TRIG_CONTROL0_REG              (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Sensor_Packet_Handler_TRIG_CONTROL0_PTR              ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Sensor_Packet_Handler_TRIG_CONTROL1_REG              (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Sensor_Packet_Handler_TRIG_CONTROL1_PTR              ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Sensor_Packet_Handler_TRIG_CONTROL2_REG              (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Sensor_Packet_Handler_TRIG_CONTROL2_PTR              ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Sensor_Packet_Handler_INTERRUPT_REQ_REG              (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR )
#define Sensor_Packet_Handler_INTERRUPT_REQ_PTR              ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR )
#define Sensor_Packet_Handler_INTERRUPT_SET_REG              (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR_SET )
#define Sensor_Packet_Handler_INTERRUPT_SET_PTR              ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR_SET )
#define Sensor_Packet_Handler_INTERRUPT_MASK_REG             (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR_MASK )
#define Sensor_Packet_Handler_INTERRUPT_MASK_PTR             ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR_MASK )
#define Sensor_Packet_Handler_INTERRUPT_MASKED_REG           (*(reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Sensor_Packet_Handler_INTERRUPT_MASKED_PTR           ( (reg32 *) Sensor_Packet_Handler_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Sensor_Packet_Handler_MASK                           ((uint32)Sensor_Packet_Handler_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Sensor_Packet_Handler_RELOAD_CC_SHIFT                (0u)
#define Sensor_Packet_Handler_RELOAD_PERIOD_SHIFT            (1u)
#define Sensor_Packet_Handler_PWM_SYNC_KILL_SHIFT            (2u)
#define Sensor_Packet_Handler_PWM_STOP_KILL_SHIFT            (3u)
#define Sensor_Packet_Handler_PRESCALER_SHIFT                (8u)
#define Sensor_Packet_Handler_UPDOWN_SHIFT                   (16u)
#define Sensor_Packet_Handler_ONESHOT_SHIFT                  (18u)
#define Sensor_Packet_Handler_QUAD_MODE_SHIFT                (20u)
#define Sensor_Packet_Handler_INV_OUT_SHIFT                  (20u)
#define Sensor_Packet_Handler_INV_COMPL_OUT_SHIFT            (21u)
#define Sensor_Packet_Handler_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Sensor_Packet_Handler_RELOAD_CC_MASK                 ((uint32)(Sensor_Packet_Handler_1BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_RELOAD_CC_SHIFT))
#define Sensor_Packet_Handler_RELOAD_PERIOD_MASK             ((uint32)(Sensor_Packet_Handler_1BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_RELOAD_PERIOD_SHIFT))
#define Sensor_Packet_Handler_PWM_SYNC_KILL_MASK             ((uint32)(Sensor_Packet_Handler_1BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_PWM_SYNC_KILL_SHIFT))
#define Sensor_Packet_Handler_PWM_STOP_KILL_MASK             ((uint32)(Sensor_Packet_Handler_1BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_PWM_STOP_KILL_SHIFT))
#define Sensor_Packet_Handler_PRESCALER_MASK                 ((uint32)(Sensor_Packet_Handler_8BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_PRESCALER_SHIFT))
#define Sensor_Packet_Handler_UPDOWN_MASK                    ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_UPDOWN_SHIFT))
#define Sensor_Packet_Handler_ONESHOT_MASK                   ((uint32)(Sensor_Packet_Handler_1BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_ONESHOT_SHIFT))
#define Sensor_Packet_Handler_QUAD_MODE_MASK                 ((uint32)(Sensor_Packet_Handler_3BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_QUAD_MODE_SHIFT))
#define Sensor_Packet_Handler_INV_OUT_MASK                   ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_INV_OUT_SHIFT))
#define Sensor_Packet_Handler_MODE_MASK                      ((uint32)(Sensor_Packet_Handler_3BIT_MASK        <<  \
                                                                            Sensor_Packet_Handler_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Sensor_Packet_Handler_CAPTURE_SHIFT                  (0u)
#define Sensor_Packet_Handler_COUNT_SHIFT                    (2u)
#define Sensor_Packet_Handler_RELOAD_SHIFT                   (4u)
#define Sensor_Packet_Handler_STOP_SHIFT                     (6u)
#define Sensor_Packet_Handler_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Sensor_Packet_Handler_CAPTURE_MASK                   ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                  Sensor_Packet_Handler_CAPTURE_SHIFT))
#define Sensor_Packet_Handler_COUNT_MASK                     ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                  Sensor_Packet_Handler_COUNT_SHIFT))
#define Sensor_Packet_Handler_RELOAD_MASK                    ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                  Sensor_Packet_Handler_RELOAD_SHIFT))
#define Sensor_Packet_Handler_STOP_MASK                      ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                  Sensor_Packet_Handler_STOP_SHIFT))
#define Sensor_Packet_Handler_START_MASK                     ((uint32)(Sensor_Packet_Handler_2BIT_MASK        <<  \
                                                                  Sensor_Packet_Handler_START_SHIFT))

/* MASK */
#define Sensor_Packet_Handler_1BIT_MASK                      ((uint32)0x01u)
#define Sensor_Packet_Handler_2BIT_MASK                      ((uint32)0x03u)
#define Sensor_Packet_Handler_3BIT_MASK                      ((uint32)0x07u)
#define Sensor_Packet_Handler_6BIT_MASK                      ((uint32)0x3Fu)
#define Sensor_Packet_Handler_8BIT_MASK                      ((uint32)0xFFu)
#define Sensor_Packet_Handler_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Sensor_Packet_Handler_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Sensor_Packet_Handler_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Sensor_Packet_Handler_QUAD_ENCODING_MODES     << Sensor_Packet_Handler_QUAD_MODE_SHIFT))       |\
         ((uint32)(Sensor_Packet_Handler_CONFIG                  << Sensor_Packet_Handler_MODE_SHIFT)))

#define Sensor_Packet_Handler_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Sensor_Packet_Handler_PWM_STOP_EVENT          << Sensor_Packet_Handler_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Sensor_Packet_Handler_PWM_OUT_INVERT          << Sensor_Packet_Handler_INV_OUT_SHIFT))         |\
         ((uint32)(Sensor_Packet_Handler_PWM_OUT_N_INVERT        << Sensor_Packet_Handler_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Sensor_Packet_Handler_PWM_MODE                << Sensor_Packet_Handler_MODE_SHIFT)))

#define Sensor_Packet_Handler_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Sensor_Packet_Handler_PWM_RUN_MODE         << Sensor_Packet_Handler_ONESHOT_SHIFT))
            
#define Sensor_Packet_Handler_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Sensor_Packet_Handler_PWM_ALIGN            << Sensor_Packet_Handler_UPDOWN_SHIFT))

#define Sensor_Packet_Handler_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Sensor_Packet_Handler_PWM_KILL_EVENT      << Sensor_Packet_Handler_PWM_SYNC_KILL_SHIFT))

#define Sensor_Packet_Handler_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Sensor_Packet_Handler_PWM_DEAD_TIME_CYCLE  << Sensor_Packet_Handler_PRESCALER_SHIFT))

#define Sensor_Packet_Handler_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Sensor_Packet_Handler_PWM_PRESCALER        << Sensor_Packet_Handler_PRESCALER_SHIFT))

#define Sensor_Packet_Handler_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Sensor_Packet_Handler_TC_PRESCALER            << Sensor_Packet_Handler_PRESCALER_SHIFT))       |\
         ((uint32)(Sensor_Packet_Handler_TC_COUNTER_MODE         << Sensor_Packet_Handler_UPDOWN_SHIFT))          |\
         ((uint32)(Sensor_Packet_Handler_TC_RUN_MODE             << Sensor_Packet_Handler_ONESHOT_SHIFT))         |\
         ((uint32)(Sensor_Packet_Handler_TC_COMP_CAP_MODE        << Sensor_Packet_Handler_MODE_SHIFT)))
        
#define Sensor_Packet_Handler_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Sensor_Packet_Handler_QUAD_PHIA_SIGNAL_MODE   << Sensor_Packet_Handler_COUNT_SHIFT))           |\
         ((uint32)(Sensor_Packet_Handler_QUAD_INDEX_SIGNAL_MODE  << Sensor_Packet_Handler_RELOAD_SHIFT))          |\
         ((uint32)(Sensor_Packet_Handler_QUAD_STOP_SIGNAL_MODE   << Sensor_Packet_Handler_STOP_SHIFT))            |\
         ((uint32)(Sensor_Packet_Handler_QUAD_PHIB_SIGNAL_MODE   << Sensor_Packet_Handler_START_SHIFT)))

#define Sensor_Packet_Handler_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Sensor_Packet_Handler_PWM_SWITCH_SIGNAL_MODE  << Sensor_Packet_Handler_CAPTURE_SHIFT))         |\
         ((uint32)(Sensor_Packet_Handler_PWM_COUNT_SIGNAL_MODE   << Sensor_Packet_Handler_COUNT_SHIFT))           |\
         ((uint32)(Sensor_Packet_Handler_PWM_RELOAD_SIGNAL_MODE  << Sensor_Packet_Handler_RELOAD_SHIFT))          |\
         ((uint32)(Sensor_Packet_Handler_PWM_STOP_SIGNAL_MODE    << Sensor_Packet_Handler_STOP_SHIFT))            |\
         ((uint32)(Sensor_Packet_Handler_PWM_START_SIGNAL_MODE   << Sensor_Packet_Handler_START_SHIFT)))

#define Sensor_Packet_Handler_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Sensor_Packet_Handler_TC_CAPTURE_SIGNAL_MODE  << Sensor_Packet_Handler_CAPTURE_SHIFT))         |\
         ((uint32)(Sensor_Packet_Handler_TC_COUNT_SIGNAL_MODE    << Sensor_Packet_Handler_COUNT_SHIFT))           |\
         ((uint32)(Sensor_Packet_Handler_TC_RELOAD_SIGNAL_MODE   << Sensor_Packet_Handler_RELOAD_SHIFT))          |\
         ((uint32)(Sensor_Packet_Handler_TC_STOP_SIGNAL_MODE     << Sensor_Packet_Handler_STOP_SHIFT))            |\
         ((uint32)(Sensor_Packet_Handler_TC_START_SIGNAL_MODE    << Sensor_Packet_Handler_START_SHIFT)))
        
#define Sensor_Packet_Handler_TIMER_UPDOWN_CNT_USED                                                          \
                ((Sensor_Packet_Handler__COUNT_UPDOWN0 == Sensor_Packet_Handler_TC_COUNTER_MODE)                  ||\
                 (Sensor_Packet_Handler__COUNT_UPDOWN1 == Sensor_Packet_Handler_TC_COUNTER_MODE))

#define Sensor_Packet_Handler_PWM_UPDOWN_CNT_USED                                                            \
                ((Sensor_Packet_Handler__CENTER == Sensor_Packet_Handler_PWM_ALIGN)                               ||\
                 (Sensor_Packet_Handler__ASYMMETRIC == Sensor_Packet_Handler_PWM_ALIGN))               
        
#define Sensor_Packet_Handler_PWM_PR_INIT_VALUE              (1u)
#define Sensor_Packet_Handler_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Sensor_Packet_Handler_H */

/* [] END OF FILE */
