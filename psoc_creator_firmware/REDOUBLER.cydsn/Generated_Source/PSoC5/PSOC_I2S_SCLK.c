/*******************************************************************************
* File Name: PSOC_I2S_SCLK.c  
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
#include "PSOC_I2S_SCLK.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PSOC_I2S_SCLK__PORT == 15 && ((PSOC_I2S_SCLK__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PSOC_I2S_SCLK_Write
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
void PSOC_I2S_SCLK_Write(uint8 value) 
{
    uint8 staticBits = (PSOC_I2S_SCLK_DR & (uint8)(~PSOC_I2S_SCLK_MASK));
    PSOC_I2S_SCLK_DR = staticBits | ((uint8)(value << PSOC_I2S_SCLK_SHIFT) & PSOC_I2S_SCLK_MASK);
}


/*******************************************************************************
* Function Name: PSOC_I2S_SCLK_SetDriveMode
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
void PSOC_I2S_SCLK_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PSOC_I2S_SCLK_0, mode);
}


/*******************************************************************************
* Function Name: PSOC_I2S_SCLK_Read
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
*  Macro PSOC_I2S_SCLK_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PSOC_I2S_SCLK_Read(void) 
{
    return (PSOC_I2S_SCLK_PS & PSOC_I2S_SCLK_MASK) >> PSOC_I2S_SCLK_SHIFT;
}


/*******************************************************************************
* Function Name: PSOC_I2S_SCLK_ReadDataReg
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
uint8 PSOC_I2S_SCLK_ReadDataReg(void) 
{
    return (PSOC_I2S_SCLK_DR & PSOC_I2S_SCLK_MASK) >> PSOC_I2S_SCLK_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PSOC_I2S_SCLK_INTSTAT) 

    /*******************************************************************************
    * Function Name: PSOC_I2S_SCLK_ClearInterrupt
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
    uint8 PSOC_I2S_SCLK_ClearInterrupt(void) 
    {
        return (PSOC_I2S_SCLK_INTSTAT & PSOC_I2S_SCLK_MASK) >> PSOC_I2S_SCLK_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
