/*******************************************************************************
* File Name: PSOC_CODEC_RST.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PSOC_CODEC_RST.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PSOC_CODEC_RST__PORT == 15 && ((PSOC_CODEC_RST__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PSOC_CODEC_RST_Write
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
void PSOC_CODEC_RST_Write(uint8 value) 
{
    uint8 staticBits = (PSOC_CODEC_RST_DR & (uint8)(~PSOC_CODEC_RST_MASK));
    PSOC_CODEC_RST_DR = staticBits | ((uint8)(value << PSOC_CODEC_RST_SHIFT) & PSOC_CODEC_RST_MASK);
}


/*******************************************************************************
* Function Name: PSOC_CODEC_RST_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void PSOC_CODEC_RST_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PSOC_CODEC_RST_0, mode);
}


/*******************************************************************************
* Function Name: PSOC_CODEC_RST_Read
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
*  Macro PSOC_CODEC_RST_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PSOC_CODEC_RST_Read(void) 
{
    return (PSOC_CODEC_RST_PS & PSOC_CODEC_RST_MASK) >> PSOC_CODEC_RST_SHIFT;
}


/*******************************************************************************
* Function Name: PSOC_CODEC_RST_ReadDataReg
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
uint8 PSOC_CODEC_RST_ReadDataReg(void) 
{
    return (PSOC_CODEC_RST_DR & PSOC_CODEC_RST_MASK) >> PSOC_CODEC_RST_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PSOC_CODEC_RST_INTSTAT) 

    /*******************************************************************************
    * Function Name: PSOC_CODEC_RST_ClearInterrupt
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
    uint8 PSOC_CODEC_RST_ClearInterrupt(void) 
    {
        return (PSOC_CODEC_RST_INTSTAT & PSOC_CODEC_RST_MASK) >> PSOC_CODEC_RST_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
