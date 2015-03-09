/*******************************************************************************
* File Name: I2S_PM.c
* Version 2.40
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2S.h"

static I2S_BACKUP_STRUCT  I2S_backup =
{
    /* Generation of WS and SCK is disabled */
    I2S_DISABLED,

    /* RX and/or TX directions are disabled */
    I2S_DISABLED,

    #if(CY_UDB_V0)
        /* WS Period */
        I2S_DEFAULT_WS_PERIOD,

        #if(I2S_TX_DIRECTION_ENABLE)
            I2S_DEFAULT_TX_INT_SOURCE,
        #endif /* (I2S_TX_DIRECTION_ENABLE) */
       
        #if(I2S_RX_DIRECTION_ENABLE)
            I2S_DEFAULT_RX_INT_SOURCE
        #endif /* (I2S_RX_DIRECTION_ENABLE) */

    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: I2S_SaveConfig
********************************************************************************
*
* Summary:
*  Saves I2S configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  I2S_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void I2S_SaveConfig(void) 
{
    /* Saves CTL_REG bits to define what direction was enabled */
    I2S_backup.CtrlReg = I2S_CONTROL_REG;

    /* Saves CNT7 and STATUSI MSK/PER for UDB array version 0 */
    #if(CY_UDB_V0)
        I2S_backup.Cnt7Period = I2S_CNT7_PERIOD_REG;

        #if(I2S_TX_DIRECTION_ENABLE)
            I2S_backup.TxIntMask = I2S_TX_STATUS_MASK_REG;
        #endif /* (I2S_TX_DIRECTION_ENABLE) */
        
        #if(I2S_RX_DIRECTION_ENABLE)
            I2S_backup.RxIntMask = I2S_RX_STATUS_MASK_REG;
        #endif /* (I2S_RX_DIRECTION_ENABLE) */

    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: I2S_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores I2S configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  I2S_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void I2S_RestoreConfig(void) 
{
    /* Restores CNT7 and STATUSI MSK/PER registers for UDB array version 0 */
    #if(CY_UDB_V0)
        I2S_CNT7_PERIOD_REG = I2S_backup.Cnt7Period;

        #if(I2S_TX_DIRECTION_ENABLE)
            I2S_TX_STATUS_MASK_REG = I2S_backup.TxIntMask;
        #endif /* (I2S_TX_DIRECTION_ENABLE) */
        
        #if(I2S_RX_DIRECTION_ENABLE)
            I2S_RX_STATUS_MASK_REG = I2S_backup.RxIntMask;
        #endif /* (I2S_RX_DIRECTION_ENABLE) */

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: I2S_Sleep
********************************************************************************
*
* Summary:
*  Prepares I2S goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  I2S_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void I2S_Sleep(void) 
{
    /* Get component state */
    I2S_backup.enableState = ((uint8) I2S_IS_ENABLE);

    /* Save registers configuration */
    I2S_SaveConfig();

    /* Stop component */
    I2S_Stop();
}


/*******************************************************************************
* Function Name: I2S_Wakeup
********************************************************************************
*
* Summary:
*  Prepares I2S to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  I2S_backup - used when non-retention registers are restored.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void I2S_Wakeup(void) 
{
    /* Restore registers values */
    I2S_RestoreConfig();

    if(0u != I2S_backup.enableState)
    {
        /* Enable component's operation */
        I2S_Enable();

        /* Enable Tx/Rx direction if they were enabled before sleep */
        #if(I2S_TX_DIRECTION_ENABLE)
            if(0u != (I2S_backup.CtrlReg & I2S_TX_EN))
            {
                I2S_EnableTx();
            }
        #endif /* (I2S_TX_DIRECTION_ENABLE) */
        
        #if(I2S_RX_DIRECTION_ENABLE)
            if(0u != (I2S_backup.CtrlReg & I2S_RX_EN))
            {
                I2S_EnableRx();
            }
        #endif /* (I2S_RX_DIRECTION_ENABLE) */
    }
}


/* [] END OF FILE */
