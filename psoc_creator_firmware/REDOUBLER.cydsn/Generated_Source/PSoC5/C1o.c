/*******************************************************************************
* File Name: C1o.c  
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
#include "C1o.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 C1o__PORT == 15 && ((C1o__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: C1o_Write
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
void C1o_Write(uint8 value) 
{
    uint8 staticBits = (C1o_DR & (uint8)(~C1o_MASK));
    C1o_DR = staticBits | ((uint8)(value << C1o_SHIFT) & C1o_MASK);
}


/*******************************************************************************
* Function Name: C1o_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  C1o_DM_STRONG     Strong Drive 
*  C1o_DM_OD_HI      Open Drain, Drives High 
*  C1o_DM_OD_LO      Open Drain, Drives Low 
*  C1o_DM_RES_UP     Resistive Pull Up 
*  C1o_DM_RES_DWN    Resistive Pull Down 
*  C1o_DM_RES_UPDWN  Resistive Pull Up/Down 
*  C1o_DM_DIG_HIZ    High Impedance Digital 
*  C1o_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void C1o_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(C1o_0, mode);
}


/*******************************************************************************
* Function Name: C1o_Read
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
*  Macro C1o_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 C1o_Read(void) 
{
    return (C1o_PS & C1o_MASK) >> C1o_SHIFT;
}


/*******************************************************************************
* Function Name: C1o_ReadDataReg
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
uint8 C1o_ReadDataReg(void) 
{
    return (C1o_DR & C1o_MASK) >> C1o_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(C1o_INTSTAT) 

    /*******************************************************************************
    * Function Name: C1o_ClearInterrupt
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
    uint8 C1o_ClearInterrupt(void) 
    {
        return (C1o_INTSTAT & C1o_MASK) >> C1o_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
