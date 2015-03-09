/*******************************************************************************
* File Name: Opamp_1_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Opamp_1.h"

static Opamp_1_BACKUP_STRUCT  Opamp_1_backup;


/*******************************************************************************  
* Function Name: Opamp_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void Opamp_1_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Opamp_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Opamp_1_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Opamp_1_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Opamp_1_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Opamp_1_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((Opamp_1_PM_ACT_CFG_REG & Opamp_1_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Opamp_1_backup.enableState = 1u;
         /* Stops the component */
         Opamp_1_Stop();
    }
    else
    {
        /* Component is disabled */
        Opamp_1_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Opamp_1_SaveConfig();
}


/*******************************************************************************  
* Function Name: Opamp_1_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Opamp_1_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Opamp_1_Wakeup(void) 
{
    /* Restore the user configuration */
    Opamp_1_RestoreConfig();

    /* Enables the component operation */
    if(Opamp_1_backup.enableState == 1u)
    {
        Opamp_1_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
