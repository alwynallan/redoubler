/*******************************************************************************
* File Name: OA1m.c  
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
#include "OA1m.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 OA1m__PORT == 15 && ((OA1m__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: OA1m_Write
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
void OA1m_Write(uint8 value) 
{
    uint8 staticBits = (OA1m_DR & (uint8)(~OA1m_MASK));
    OA1m_DR = staticBits | ((uint8)(value << OA1m_SHIFT) & OA1m_MASK);
}


/*******************************************************************************
* Function Name: OA1m_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  OA1m_DM_STRONG     Strong Drive 
*  OA1m_DM_OD_HI      Open Drain, Drives High 
*  OA1m_DM_OD_LO      Open Drain, Drives Low 
*  OA1m_DM_RES_UP     Resistive Pull Up 
*  OA1m_DM_RES_DWN    Resistive Pull Down 
*  OA1m_DM_RES_UPDWN  Resistive Pull Up/Down 
*  OA1m_DM_DIG_HIZ    High Impedance Digital 
*  OA1m_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void OA1m_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(OA1m_0, mode);
}


/*******************************************************************************
* Function Name: OA1m_Read
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
*  Macro OA1m_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 OA1m_Read(void) 
{
    return (OA1m_PS & OA1m_MASK) >> OA1m_SHIFT;
}


/*******************************************************************************
* Function Name: OA1m_ReadDataReg
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
uint8 OA1m_ReadDataReg(void) 
{
    return (OA1m_DR & OA1m_MASK) >> OA1m_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(OA1m_INTSTAT) 

    /*******************************************************************************
    * Function Name: OA1m_ClearInterrupt
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
    uint8 OA1m_ClearInterrupt(void) 
    {
        return (OA1m_INTSTAT & OA1m_MASK) >> OA1m_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
