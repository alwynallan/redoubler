/*******************************************************************************
* File Name: PDM_CIC_Int_Ctrl_Reg.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PDM_CIC_Int_Ctrl_Reg.h"

#if !defined(PDM_CIC_Int_Ctrl_Reg_Sync_ctrl_reg__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
* Function Name: PDM_CIC_Int_Ctrl_Reg_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void PDM_CIC_Int_Ctrl_Reg_Write(uint8 control) 
{
    PDM_CIC_Int_Ctrl_Reg_Control = control;
}


/*******************************************************************************
* Function Name: PDM_CIC_Int_Ctrl_Reg_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 PDM_CIC_Int_Ctrl_Reg_Read(void) 
{
    return PDM_CIC_Int_Ctrl_Reg_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
