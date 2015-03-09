/*******************************************************************************
* File Name: Sample_Hold_4.c
* Version 1.40
*
* Description:
*  This file provides the power manager source code to the API for 
*  the SAMPLE/TRACK AND HOLD component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Sample_Hold_4.h"

static Sample_Hold_4_backupStruct  Sample_Hold_4_backup;


/*******************************************************************************
* Function Name: Sample_Hold_4_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void.
*
* Return: 
*  void.
*
*******************************************************************************/
void Sample_Hold_4_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retention registers. */
}


/*******************************************************************************
* Function Name: Sample_Hold_4_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void.
*
* Return: 
*  void
*
*******************************************************************************/
void Sample_Hold_4_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: Sample_Hold_4_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Sample_Hold_4_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Sample_Hold_4_Sleep(void) 
{
    /* Save TIA enable state */
    if((Sample_Hold_4_PM_ACT_CFG_REG & Sample_Hold_4_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Sample_Hold_4_backup.enableState = 1u;
        /* Stop the configuration */
        Sample_Hold_4_Stop();
    }
    else
    {
        /* Component is disabled */
        Sample_Hold_4_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    Sample_Hold_4_SaveConfig();
}


/*******************************************************************************
* Function Name: Sample_Hold_4_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  Sample_Hold_4_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Sample_Hold_4_Wakeup(void) 
{
    /* Restore the user configuration */
    Sample_Hold_4_RestoreConfig();
    
    /* Enable's the component operation */
    if(Sample_Hold_4_backup.enableState == 1u)
    {
        Sample_Hold_4_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
