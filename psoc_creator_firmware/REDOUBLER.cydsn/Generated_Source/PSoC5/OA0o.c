/*******************************************************************************
* File Name: OA0o.c  
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
#include "OA0o.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 OA0o__PORT == 15 && ((OA0o__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: OA0o_Write
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
void OA0o_Write(uint8 value) 
{
    uint8 staticBits = (OA0o_DR & (uint8)(~OA0o_MASK));
    OA0o_DR = staticBits | ((uint8)(value << OA0o_SHIFT) & OA0o_MASK);
}


/*******************************************************************************
* Function Name: OA0o_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  OA0o_DM_STRONG     Strong Drive 
*  OA0o_DM_OD_HI      Open Drain, Drives High 
*  OA0o_DM_OD_LO      Open Drain, Drives Low 
*  OA0o_DM_RES_UP     Resistive Pull Up 
*  OA0o_DM_RES_DWN    Resistive Pull Down 
*  OA0o_DM_RES_UPDWN  Resistive Pull Up/Down 
*  OA0o_DM_DIG_HIZ    High Impedance Digital 
*  OA0o_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void OA0o_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(OA0o_0, mode);
}


/*******************************************************************************
* Function Name: OA0o_Read
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
*  Macro OA0o_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 OA0o_Read(void) 
{
    return (OA0o_PS & OA0o_MASK) >> OA0o_SHIFT;
}


/*******************************************************************************
* Function Name: OA0o_ReadDataReg
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
uint8 OA0o_ReadDataReg(void) 
{
    return (OA0o_DR & OA0o_MASK) >> OA0o_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(OA0o_INTSTAT) 

    /*******************************************************************************
    * Function Name: OA0o_ClearInterrupt
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
    uint8 OA0o_ClearInterrupt(void) 
    {
        return (OA0o_INTSTAT & OA0o_MASK) >> OA0o_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
