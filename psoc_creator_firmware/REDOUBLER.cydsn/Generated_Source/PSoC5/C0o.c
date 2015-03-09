/*******************************************************************************
* File Name: C0o.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "C0o.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 C0o__PORT == 15 && ((C0o__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: C0o_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void C0o_Write(uint8 value) 
{
    uint8 staticBits = (C0o_DR & (uint8)(~C0o_MASK));
    C0o_DR = staticBits | ((uint8)(value << C0o_SHIFT) & C0o_MASK);
}


/*******************************************************************************
* Function Name: C0o_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  C0o_DM_STRONG     Strong Drive 
*  C0o_DM_OD_HI      Open Drain, Drives High 
*  C0o_DM_OD_LO      Open Drain, Drives Low 
*  C0o_DM_RES_UP     Resistive Pull Up 
*  C0o_DM_RES_DWN    Resistive Pull Down 
*  C0o_DM_RES_UPDWN  Resistive Pull Up/Down 
*  C0o_DM_DIG_HIZ    High Impedance Digital 
*  C0o_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void C0o_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(C0o_0, mode);
}


/*******************************************************************************
* Function Name: C0o_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro C0o_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 C0o_Read(void) 
{
    return (C0o_PS & C0o_MASK) >> C0o_SHIFT;
}


/*******************************************************************************
* Function Name: C0o_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 C0o_ReadDataReg(void) 
{
    return (C0o_DR & C0o_MASK) >> C0o_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(C0o_INTSTAT) 

    /*******************************************************************************
    * Function Name: C0o_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 C0o_ClearInterrupt(void) 
    {
        return (C0o_INTSTAT & C0o_MASK) >> C0o_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
