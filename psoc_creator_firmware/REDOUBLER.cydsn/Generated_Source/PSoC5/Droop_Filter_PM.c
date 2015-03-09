/*******************************************************************************
* File Name: Droop_Filter_PM.c
* Version 1.20
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Droop_Filter.h"

static Droop_Filter_BACKUP_STRUCT Droop_Filter_backup = { 0u };


/*******************************************************************************
* Function Name: Droop_Filter_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the user configuration of the DFB non-retention registers. This routine
*  is called by DFB_Sleep() to save the component configuration before entering
*  sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Droop_Filter_SaveConfig(void) 
{
    /* */
}


/*******************************************************************************
* Function Name: Droop_Filter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of the DFB non-retention registers. This
*  routine is called by DFB_Wakeup() to restore the component configuration when
*  exiting sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Droop_Filter_RestoreConfig(void) 
{
    /* */
}


/*******************************************************************************
* Function Name: Droop_Filter_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep. The
*  Droop_Filter_Sleep() routine saves the current component state. Then it
*  calls the DFB_Stop() function and calls Droop_Filter_SaveConfig() to save
*  the hardware configuration. Call the Droop_Filter_Sleep() function before
*  calling the CyPmSleep() or the CyPmHibernate() function. Refer to the PSoC
*  Creator System Reference Guide for more information about power management
*  functions.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Droop_Filter_Sleep(void) 
{
    if (0u != (Droop_Filter_CR_REG & Droop_Filter_RUN_MASK))
    {
        Droop_Filter_backup.enableState = 1u;
    }
    else /* The DFB block is disabled */
    {
        Droop_Filter_backup.enableState = 0u;
    }

    /* Disables the clock to the entire core of the block */
    Droop_Filter_CR_REG |= Droop_Filter_CORECLK_DISABLE;

    Droop_Filter_Pause();
}


/*******************************************************************************
* Function Name: Droop_Filter_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  Droop_Filter_Sleep() was called. The Droop_Filter_Wakeup() function
*  calls the Droop_Filter_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  Droop_Filter_Sleep() function was called, the Droop_Filter_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Calling the Droop_Filter_Wakeup() function without first calling the
*  Droop_Filter_Sleep() or Droop_Filter_SaveConfig() function may
*  produce unexpected behavior.
*
*******************************************************************************/
void Droop_Filter_Wakeup(void) 
{
   Droop_Filter_RestoreConfig();

    /* Enables the clock to the entire core of the block */
    Droop_Filter_CR_REG &= (uint8) (~Droop_Filter_CORECLK_DISABLE);

    if (Droop_Filter_backup.enableState != 0u)
    {
        /* Enables component's operation */
        Droop_Filter_Resume();
    } /* Left Run Bit in off state if component's block was disabled before */
    else
    {
        /* Takes DFB RAM off the bus */
        Droop_Filter_RAM_DIR_REG = Droop_Filter_RAM_DIR_DFB;
        /* Clears any pending interrupts */
        Droop_Filter_SR_REG = 0xFFu;
    }
}


/* [] END OF FILE */
