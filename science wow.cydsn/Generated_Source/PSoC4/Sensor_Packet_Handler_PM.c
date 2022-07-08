/*******************************************************************************
* File Name: Sensor_Packet_Handler_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

static Sensor_Packet_Handler_BACKUP_STRUCT Sensor_Packet_Handler_backup;


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_Sleep(void)
{
    if(0u != (Sensor_Packet_Handler_BLOCK_CONTROL_REG & Sensor_Packet_Handler_MASK))
    {
        Sensor_Packet_Handler_backup.enableState = 1u;
    }
    else
    {
        Sensor_Packet_Handler_backup.enableState = 0u;
    }

    Sensor_Packet_Handler_Stop();
    Sensor_Packet_Handler_SaveConfig();
}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Sensor_Packet_Handler_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Sensor_Packet_Handler_Wakeup(void)
{
    Sensor_Packet_Handler_RestoreConfig();

    if(0u != Sensor_Packet_Handler_backup.enableState)
    {
        Sensor_Packet_Handler_Enable();
    }
}


/* [] END OF FILE */
