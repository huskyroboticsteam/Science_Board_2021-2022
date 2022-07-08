/*******************************************************************************
* File Name: Sensor_Packet_Handler.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Sensor_Packet_Handler
*  component
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

#include "Sensor_Packet_Handler.h"

uint8 Sensor_Packet_Handler_initVar = 0u;


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Sensor_Packet_Handler configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Sensor_Packet_Handler__QUAD == Sensor_Packet_Handler_CONFIG)
        Sensor_Packet_Handler_CONTROL_REG = Sensor_Packet_Handler_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Sensor_Packet_Handler_TRIG_CONTROL1_REG  = Sensor_Packet_Handler_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Sensor_Packet_Handler_SetInterruptMode(Sensor_Packet_Handler_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Sensor_Packet_Handler_SetCounterMode(Sensor_Packet_Handler_COUNT_DOWN);
        Sensor_Packet_Handler_WritePeriod(Sensor_Packet_Handler_QUAD_PERIOD_INIT_VALUE);
        Sensor_Packet_Handler_WriteCounter(Sensor_Packet_Handler_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Sensor_Packet_Handler__QUAD == Sensor_Packet_Handler_CONFIG) */

    #if (Sensor_Packet_Handler__TIMER == Sensor_Packet_Handler_CONFIG)
        Sensor_Packet_Handler_CONTROL_REG = Sensor_Packet_Handler_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Sensor_Packet_Handler_TRIG_CONTROL1_REG  = Sensor_Packet_Handler_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Sensor_Packet_Handler_SetInterruptMode(Sensor_Packet_Handler_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Sensor_Packet_Handler_WritePeriod(Sensor_Packet_Handler_TC_PERIOD_VALUE );

        #if (Sensor_Packet_Handler__COMPARE == Sensor_Packet_Handler_TC_COMP_CAP_MODE)
            Sensor_Packet_Handler_WriteCompare(Sensor_Packet_Handler_TC_COMPARE_VALUE);

            #if (1u == Sensor_Packet_Handler_TC_COMPARE_SWAP)
                Sensor_Packet_Handler_SetCompareSwap(1u);
                Sensor_Packet_Handler_WriteCompareBuf(Sensor_Packet_Handler_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Sensor_Packet_Handler_TC_COMPARE_SWAP) */
        #endif  /* (Sensor_Packet_Handler__COMPARE == Sensor_Packet_Handler_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Sensor_Packet_Handler_CY_TCPWM_V2 && Sensor_Packet_Handler_TIMER_UPDOWN_CNT_USED && !Sensor_Packet_Handler_CY_TCPWM_4000)
            Sensor_Packet_Handler_WriteCounter(1u);
        #elif(Sensor_Packet_Handler__COUNT_DOWN == Sensor_Packet_Handler_TC_COUNTER_MODE)
            Sensor_Packet_Handler_WriteCounter(Sensor_Packet_Handler_TC_PERIOD_VALUE);
        #else
            Sensor_Packet_Handler_WriteCounter(0u);
        #endif /* (Sensor_Packet_Handler_CY_TCPWM_V2 && Sensor_Packet_Handler_TIMER_UPDOWN_CNT_USED && !Sensor_Packet_Handler_CY_TCPWM_4000) */
    #endif  /* (Sensor_Packet_Handler__TIMER == Sensor_Packet_Handler_CONFIG) */

    #if (Sensor_Packet_Handler__PWM_SEL == Sensor_Packet_Handler_CONFIG)
        Sensor_Packet_Handler_CONTROL_REG = Sensor_Packet_Handler_CTRL_PWM_BASE_CONFIG;

        #if (Sensor_Packet_Handler__PWM_PR == Sensor_Packet_Handler_PWM_MODE)
            Sensor_Packet_Handler_CONTROL_REG |= Sensor_Packet_Handler_CTRL_PWM_RUN_MODE;
            Sensor_Packet_Handler_WriteCounter(Sensor_Packet_Handler_PWM_PR_INIT_VALUE);
        #else
            Sensor_Packet_Handler_CONTROL_REG |= Sensor_Packet_Handler_CTRL_PWM_ALIGN | Sensor_Packet_Handler_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Sensor_Packet_Handler_CY_TCPWM_V2 && Sensor_Packet_Handler_PWM_UPDOWN_CNT_USED && !Sensor_Packet_Handler_CY_TCPWM_4000)
                Sensor_Packet_Handler_WriteCounter(1u);
            #elif (Sensor_Packet_Handler__RIGHT == Sensor_Packet_Handler_PWM_ALIGN)
                Sensor_Packet_Handler_WriteCounter(Sensor_Packet_Handler_PWM_PERIOD_VALUE);
            #else 
                Sensor_Packet_Handler_WriteCounter(0u);
            #endif  /* (Sensor_Packet_Handler_CY_TCPWM_V2 && Sensor_Packet_Handler_PWM_UPDOWN_CNT_USED && !Sensor_Packet_Handler_CY_TCPWM_4000) */
        #endif  /* (Sensor_Packet_Handler__PWM_PR == Sensor_Packet_Handler_PWM_MODE) */

        #if (Sensor_Packet_Handler__PWM_DT == Sensor_Packet_Handler_PWM_MODE)
            Sensor_Packet_Handler_CONTROL_REG |= Sensor_Packet_Handler_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Sensor_Packet_Handler__PWM_DT == Sensor_Packet_Handler_PWM_MODE) */

        #if (Sensor_Packet_Handler__PWM == Sensor_Packet_Handler_PWM_MODE)
            Sensor_Packet_Handler_CONTROL_REG |= Sensor_Packet_Handler_CTRL_PWM_PRESCALER;
        #endif  /* (Sensor_Packet_Handler__PWM == Sensor_Packet_Handler_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Sensor_Packet_Handler_TRIG_CONTROL1_REG  = Sensor_Packet_Handler_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Sensor_Packet_Handler_SetInterruptMode(Sensor_Packet_Handler_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Sensor_Packet_Handler__PWM_PR == Sensor_Packet_Handler_PWM_MODE)
            Sensor_Packet_Handler_TRIG_CONTROL2_REG =
                    (Sensor_Packet_Handler_CC_MATCH_NO_CHANGE    |
                    Sensor_Packet_Handler_OVERLOW_NO_CHANGE      |
                    Sensor_Packet_Handler_UNDERFLOW_NO_CHANGE);
        #else
            #if (Sensor_Packet_Handler__LEFT == Sensor_Packet_Handler_PWM_ALIGN)
                Sensor_Packet_Handler_TRIG_CONTROL2_REG = Sensor_Packet_Handler_PWM_MODE_LEFT;
            #endif  /* ( Sensor_Packet_Handler_PWM_LEFT == Sensor_Packet_Handler_PWM_ALIGN) */

            #if (Sensor_Packet_Handler__RIGHT == Sensor_Packet_Handler_PWM_ALIGN)
                Sensor_Packet_Handler_TRIG_CONTROL2_REG = Sensor_Packet_Handler_PWM_MODE_RIGHT;
            #endif  /* ( Sensor_Packet_Handler_PWM_RIGHT == Sensor_Packet_Handler_PWM_ALIGN) */

            #if (Sensor_Packet_Handler__CENTER == Sensor_Packet_Handler_PWM_ALIGN)
                Sensor_Packet_Handler_TRIG_CONTROL2_REG = Sensor_Packet_Handler_PWM_MODE_CENTER;
            #endif  /* ( Sensor_Packet_Handler_PWM_CENTER == Sensor_Packet_Handler_PWM_ALIGN) */

            #if (Sensor_Packet_Handler__ASYMMETRIC == Sensor_Packet_Handler_PWM_ALIGN)
                Sensor_Packet_Handler_TRIG_CONTROL2_REG = Sensor_Packet_Handler_PWM_MODE_ASYM;
            #endif  /* (Sensor_Packet_Handler__ASYMMETRIC == Sensor_Packet_Handler_PWM_ALIGN) */
        #endif  /* (Sensor_Packet_Handler__PWM_PR == Sensor_Packet_Handler_PWM_MODE) */

        /* Set other values from customizer */
        Sensor_Packet_Handler_WritePeriod(Sensor_Packet_Handler_PWM_PERIOD_VALUE );
        Sensor_Packet_Handler_WriteCompare(Sensor_Packet_Handler_PWM_COMPARE_VALUE);

        #if (1u == Sensor_Packet_Handler_PWM_COMPARE_SWAP)
            Sensor_Packet_Handler_SetCompareSwap(1u);
            Sensor_Packet_Handler_WriteCompareBuf(Sensor_Packet_Handler_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Sensor_Packet_Handler_PWM_COMPARE_SWAP) */

        #if (1u == Sensor_Packet_Handler_PWM_PERIOD_SWAP)
            Sensor_Packet_Handler_SetPeriodSwap(1u);
            Sensor_Packet_Handler_WritePeriodBuf(Sensor_Packet_Handler_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Sensor_Packet_Handler_PWM_PERIOD_SWAP) */
    #endif  /* (Sensor_Packet_Handler__PWM_SEL == Sensor_Packet_Handler_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_Enable
********************************************************************************
*
* Summary:
*  Enables the Sensor_Packet_Handler.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Sensor_Packet_Handler_BLOCK_CONTROL_REG |= Sensor_Packet_Handler_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Sensor_Packet_Handler__PWM_SEL == Sensor_Packet_Handler_CONFIG)
        #if (0u == Sensor_Packet_Handler_PWM_START_SIGNAL_PRESENT)
            Sensor_Packet_Handler_TriggerCommand(Sensor_Packet_Handler_MASK, Sensor_Packet_Handler_CMD_START);
        #endif /* (0u == Sensor_Packet_Handler_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Sensor_Packet_Handler__PWM_SEL == Sensor_Packet_Handler_CONFIG) */

    #if (Sensor_Packet_Handler__TIMER == Sensor_Packet_Handler_CONFIG)
        #if (0u == Sensor_Packet_Handler_TC_START_SIGNAL_PRESENT)
            Sensor_Packet_Handler_TriggerCommand(Sensor_Packet_Handler_MASK, Sensor_Packet_Handler_CMD_START);
        #endif /* (0u == Sensor_Packet_Handler_TC_START_SIGNAL_PRESENT) */
    #endif /* (Sensor_Packet_Handler__TIMER == Sensor_Packet_Handler_CONFIG) */
    
    #if (Sensor_Packet_Handler__QUAD == Sensor_Packet_Handler_CONFIG)
        #if (0u != Sensor_Packet_Handler_QUAD_AUTO_START)
            Sensor_Packet_Handler_TriggerCommand(Sensor_Packet_Handler_MASK, Sensor_Packet_Handler_CMD_RELOAD);
        #endif /* (0u != Sensor_Packet_Handler_QUAD_AUTO_START) */
    #endif  /* (Sensor_Packet_Handler__QUAD == Sensor_Packet_Handler_CONFIG) */
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_Start
********************************************************************************
*
* Summary:
*  Initializes the Sensor_Packet_Handler with default customizer
*  values when called the first time and enables the Sensor_Packet_Handler.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Sensor_Packet_Handler_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Sensor_Packet_Handler_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Sensor_Packet_Handler_Start() routine.
*
*******************************************************************************/
void Sensor_Packet_Handler_Start(void)
{
    if (0u == Sensor_Packet_Handler_initVar)
    {
        Sensor_Packet_Handler_Init();
        Sensor_Packet_Handler_initVar = 1u;
    }

    Sensor_Packet_Handler_Enable();
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_Stop
********************************************************************************
*
* Summary:
*  Disables the Sensor_Packet_Handler.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_BLOCK_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Sensor_Packet_Handler. This function is used when
*  configured as a generic Sensor_Packet_Handler and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Sensor_Packet_Handler to operate in
*   Values:
*   - Sensor_Packet_Handler_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Sensor_Packet_Handler_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Sensor_Packet_Handler_MODE_QUAD - Quadrature decoder
*         - Sensor_Packet_Handler_MODE_PWM - PWM
*         - Sensor_Packet_Handler_MODE_PWM_DT - PWM with dead time
*         - Sensor_Packet_Handler_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_MODE_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Sensor_Packet_Handler_MODE_X1 - Counts on phi 1 rising
*         - Sensor_Packet_Handler_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Sensor_Packet_Handler_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_QUAD_MODE_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Sensor_Packet_Handler_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Sensor_Packet_Handler_PRESCALE_DIVBY2    - Divide by 2
*         - Sensor_Packet_Handler_PRESCALE_DIVBY4    - Divide by 4
*         - Sensor_Packet_Handler_PRESCALE_DIVBY8    - Divide by 8
*         - Sensor_Packet_Handler_PRESCALE_DIVBY16   - Divide by 16
*         - Sensor_Packet_Handler_PRESCALE_DIVBY32   - Divide by 32
*         - Sensor_Packet_Handler_PRESCALE_DIVBY64   - Divide by 64
*         - Sensor_Packet_Handler_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_PRESCALER_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Sensor_Packet_Handler runs
*  continuously or stops when terminal count is reached.  By default the
*  Sensor_Packet_Handler operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_ONESHOT_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= ((uint32)((oneShotEnable & Sensor_Packet_Handler_1BIT_MASK) <<
                                                               Sensor_Packet_Handler_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPWMMode(uint32 modeMask)
{
    Sensor_Packet_Handler_TRIG_CONTROL2_REG = (modeMask & Sensor_Packet_Handler_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_PWM_SYNC_KILL_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= ((uint32)((syncKillEnable & Sensor_Packet_Handler_1BIT_MASK)  <<
                                               Sensor_Packet_Handler_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_PWM_STOP_KILL_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= ((uint32)((stopOnKillEnable & Sensor_Packet_Handler_1BIT_MASK)  <<
                                                         Sensor_Packet_Handler_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_PRESCALER_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= ((uint32)((deadTime & Sensor_Packet_Handler_8BIT_MASK) <<
                                                          Sensor_Packet_Handler_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - Sensor_Packet_Handler_INVERT_LINE   - Inverts the line output
*         - Sensor_Packet_Handler_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_INV_OUT_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Sensor_Packet_Handler_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_WriteCounter(uint32 count)
{
    Sensor_Packet_Handler_COUNTER_REG = (count & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadCounter(void)
{
    return (Sensor_Packet_Handler_COUNTER_REG & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Sensor_Packet_Handler_COUNT_UP       - Counts up
*     - Sensor_Packet_Handler_COUNT_DOWN     - Counts down
*     - Sensor_Packet_Handler_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Sensor_Packet_Handler_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_UPDOWN_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_WritePeriod(uint32 period)
{
    Sensor_Packet_Handler_PERIOD_REG = (period & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadPeriod(void)
{
    return (Sensor_Packet_Handler_PERIOD_REG & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_RELOAD_CC_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= (swapEnable & Sensor_Packet_Handler_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_WritePeriodBuf(uint32 periodBuf)
{
    Sensor_Packet_Handler_PERIOD_BUF_REG = (periodBuf & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadPeriodBuf(void)
{
    return (Sensor_Packet_Handler_PERIOD_BUF_REG & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_CONTROL_REG &= (uint32)~Sensor_Packet_Handler_RELOAD_PERIOD_MASK;
    Sensor_Packet_Handler_CONTROL_REG |= ((uint32)((swapEnable & Sensor_Packet_Handler_1BIT_MASK) <<
                                                            Sensor_Packet_Handler_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Sensor_Packet_Handler_WriteCompare(uint32 compare)
{
    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */

    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        currentMode = ((Sensor_Packet_Handler_CONTROL_REG & Sensor_Packet_Handler_UPDOWN_MASK) >> Sensor_Packet_Handler_UPDOWN_SHIFT);

        if (((uint32)Sensor_Packet_Handler__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Sensor_Packet_Handler__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */
    
    Sensor_Packet_Handler_COMP_CAP_REG = (compare & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadCompare(void)
{
    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */

    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        currentMode = ((Sensor_Packet_Handler_CONTROL_REG & Sensor_Packet_Handler_UPDOWN_MASK) >> Sensor_Packet_Handler_UPDOWN_SHIFT);
        
        regVal = Sensor_Packet_Handler_COMP_CAP_REG;
        
        if (((uint32)Sensor_Packet_Handler__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Sensor_Packet_Handler__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Sensor_Packet_Handler_16BIT_MASK);
    #else
        return (Sensor_Packet_Handler_COMP_CAP_REG & Sensor_Packet_Handler_16BIT_MASK);
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Sensor_Packet_Handler_WriteCompareBuf(uint32 compareBuf)
{
    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */

    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        currentMode = ((Sensor_Packet_Handler_CONTROL_REG & Sensor_Packet_Handler_UPDOWN_MASK) >> Sensor_Packet_Handler_UPDOWN_SHIFT);

        if (((uint32)Sensor_Packet_Handler__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Sensor_Packet_Handler__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */
    
    Sensor_Packet_Handler_COMP_CAP_BUF_REG = (compareBuf & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadCompareBuf(void)
{
    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */

    #if (Sensor_Packet_Handler_CY_TCPWM_4000)
        currentMode = ((Sensor_Packet_Handler_CONTROL_REG & Sensor_Packet_Handler_UPDOWN_MASK) >> Sensor_Packet_Handler_UPDOWN_SHIFT);

        regVal = Sensor_Packet_Handler_COMP_CAP_BUF_REG;
        
        if (((uint32)Sensor_Packet_Handler__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Sensor_Packet_Handler__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Sensor_Packet_Handler_16BIT_MASK);
    #else
        return (Sensor_Packet_Handler_COMP_CAP_BUF_REG & Sensor_Packet_Handler_16BIT_MASK);
    #endif /* (Sensor_Packet_Handler_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadCapture(void)
{
    return (Sensor_Packet_Handler_COMP_CAP_REG & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadCaptureBuf(void)
{
    return (Sensor_Packet_Handler_COMP_CAP_BUF_REG & Sensor_Packet_Handler_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Sensor_Packet_Handler_TRIG_LEVEL     - Level
*     - Sensor_Packet_Handler_TRIG_RISING    - Rising edge
*     - Sensor_Packet_Handler_TRIG_FALLING   - Falling edge
*     - Sensor_Packet_Handler_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_TRIG_CONTROL1_REG &= (uint32)~Sensor_Packet_Handler_CAPTURE_MASK;
    Sensor_Packet_Handler_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Sensor_Packet_Handler_TRIG_LEVEL     - Level
*     - Sensor_Packet_Handler_TRIG_RISING    - Rising edge
*     - Sensor_Packet_Handler_TRIG_FALLING   - Falling edge
*     - Sensor_Packet_Handler_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_TRIG_CONTROL1_REG &= (uint32)~Sensor_Packet_Handler_RELOAD_MASK;
    Sensor_Packet_Handler_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Sensor_Packet_Handler_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Sensor_Packet_Handler_TRIG_LEVEL     - Level
*     - Sensor_Packet_Handler_TRIG_RISING    - Rising edge
*     - Sensor_Packet_Handler_TRIG_FALLING   - Falling edge
*     - Sensor_Packet_Handler_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_TRIG_CONTROL1_REG &= (uint32)~Sensor_Packet_Handler_START_MASK;
    Sensor_Packet_Handler_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Sensor_Packet_Handler_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Sensor_Packet_Handler_TRIG_LEVEL     - Level
*     - Sensor_Packet_Handler_TRIG_RISING    - Rising edge
*     - Sensor_Packet_Handler_TRIG_FALLING   - Falling edge
*     - Sensor_Packet_Handler_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_TRIG_CONTROL1_REG &= (uint32)~Sensor_Packet_Handler_STOP_MASK;
    Sensor_Packet_Handler_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Sensor_Packet_Handler_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Sensor_Packet_Handler_TRIG_LEVEL     - Level
*     - Sensor_Packet_Handler_TRIG_RISING    - Rising edge
*     - Sensor_Packet_Handler_TRIG_FALLING   - Falling edge
*     - Sensor_Packet_Handler_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_TRIG_CONTROL1_REG &= (uint32)~Sensor_Packet_Handler_COUNT_MASK;
    Sensor_Packet_Handler_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Sensor_Packet_Handler_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - Sensor_Packet_Handler_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Sensor_Packet_Handler_CMD_RELOAD     - Trigger Reload/Index command
*     - Sensor_Packet_Handler_CMD_STOP       - Trigger Stop/Kill command
*     - Sensor_Packet_Handler_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Sensor_Packet_Handler_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Sensor_Packet_Handler.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Sensor_Packet_Handler_STATUS_DOWN    - Set if counting down
*     - Sensor_Packet_Handler_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_ReadStatus(void)
{
    return ((Sensor_Packet_Handler_STATUS_REG >> Sensor_Packet_Handler_RUNNING_STATUS_SHIFT) |
            (Sensor_Packet_Handler_STATUS_REG & Sensor_Packet_Handler_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Sensor_Packet_Handler_INTR_MASK_TC       - Terminal count mask
*     - Sensor_Packet_Handler_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetInterruptMode(uint32 interruptMask)
{
    Sensor_Packet_Handler_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - Sensor_Packet_Handler_INTR_MASK_TC       - Terminal count mask
*     - Sensor_Packet_Handler_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_GetInterruptSourceMasked(void)
{
    return (Sensor_Packet_Handler_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - Sensor_Packet_Handler_INTR_MASK_TC       - Terminal count mask
*     - Sensor_Packet_Handler_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Sensor_Packet_Handler_GetInterruptSource(void)
{
    return (Sensor_Packet_Handler_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Sensor_Packet_Handler_INTR_MASK_TC       - Terminal count mask
*     - Sensor_Packet_Handler_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_ClearInterrupt(uint32 interruptMask)
{
    Sensor_Packet_Handler_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Sensor_Packet_Handler_INTR_MASK_TC       - Terminal count mask
*     - Sensor_Packet_Handler_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SetInterrupt(uint32 interruptMask)
{
    Sensor_Packet_Handler_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
