/*******************************************************************************
* File Name: ShiftReg_1_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ShiftReg_1.h"

static ShiftReg_1_BACKUP_STRUCT ShiftReg_1_backup =
{
    ShiftReg_1_DISABLED,

    ((uint16) ShiftReg_1_DEFAULT_A0),
    ((uint16) ShiftReg_1_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint16) ShiftReg_1_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ShiftReg_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
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
void ShiftReg_1_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ShiftReg_1_backup.saveSrA0Reg   = CY_GET_REG16(ShiftReg_1_SHIFT_REG_LSB_PTR);
    ShiftReg_1_backup.saveSrA1Reg   = CY_GET_REG16(ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ShiftReg_1_backup.saveSrIntMask = ShiftReg_1_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_1_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG16(ShiftReg_1_SHIFT_REG_LSB_PTR, ShiftReg_1_backup.saveSrA0Reg);
    CY_SET_REG16(ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_1_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ShiftReg_1_SR_STATUS_MASK = ((uint8) ShiftReg_1_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_1_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
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
void ShiftReg_1_Sleep(void) 
{
    ShiftReg_1_backup.enableState = ((uint8) ShiftReg_1_IS_ENABLED);

    ShiftReg_1_Stop();
    ShiftReg_1_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_1_Wakeup(void) 
{
    ShiftReg_1_RestoreConfig();

    if(0u != ShiftReg_1_backup.enableState)
    {
        ShiftReg_1_Enable();
    }
}


/* [] END OF FILE */
