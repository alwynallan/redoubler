/*******************************************************************************
* File Name: Comp_0.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "Comp_0.h"

static Comp_0_backupStruct Comp_0_backup;


/*******************************************************************************
* Function Name: Comp_0_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Comp_0_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comp_0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
********************************************************************************/
void Comp_0_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comp_0_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  Comp_0_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comp_0_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comp_0_ACT_PWR_EN == (Comp_0_PWRMGR & Comp_0_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comp_0_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comp_0_backup.enableState = 0u;
    }    
    
    Comp_0_Stop();
    Comp_0_SaveConfig();
}


/*******************************************************************************
* Function Name: Comp_0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Comp_0_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comp_0_Wakeup(void) 
{
    Comp_0_RestoreConfig();
    
    if(Comp_0_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comp_0_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
