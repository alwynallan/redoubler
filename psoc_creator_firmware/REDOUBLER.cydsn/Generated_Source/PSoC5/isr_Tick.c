/*******************************************************************************
* File Name: isr_Tick.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <isr_Tick.h>

#if !defined(isr_Tick__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START isr_Tick_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: isr_Tick_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_Start(void)
{
    /* For all we know the interrupt is active. */
    isr_Tick_Disable();

    /* Set the ISR to point to the isr_Tick Interrupt. */
    isr_Tick_SetVector(&isr_Tick_Interrupt);

    /* Set the priority. */
    isr_Tick_SetPriority((uint8)isr_Tick_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_Tick_Enable();
}


/*******************************************************************************
* Function Name: isr_Tick_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    isr_Tick_Disable();

    /* Set the ISR to point to the isr_Tick Interrupt. */
    isr_Tick_SetVector(address);

    /* Set the priority. */
    isr_Tick_SetPriority((uint8)isr_Tick_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_Tick_Enable();
}


/*******************************************************************************
* Function Name: isr_Tick_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_Stop(void)
{
    /* Disable this interrupt. */
    isr_Tick_Disable();

    /* Set the ISR to point to the passive one. */
    isr_Tick_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: isr_Tick_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for isr_Tick.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(isr_Tick_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_Tick_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: isr_Tick_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling isr_Tick_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use isr_Tick_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)isr_Tick__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: isr_Tick_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress isr_Tick_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)isr_Tick__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: isr_Tick_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling isr_Tick_Start
*   or isr_Tick_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   isr_Tick_Start or isr_Tick_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_SetPriority(uint8 priority)
{
    *isr_Tick_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: isr_Tick_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 isr_Tick_GetPriority(void)
{
    uint8 priority;


    priority = *isr_Tick_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: isr_Tick_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_Enable(void)
{
    /* Enable the general interrupt. */
    *isr_Tick_INTC_SET_EN = isr_Tick__INTC_MASK;
}


/*******************************************************************************
* Function Name: isr_Tick_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 isr_Tick_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*isr_Tick_INTC_SET_EN & (uint32)isr_Tick__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: isr_Tick_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_Disable(void)
{
    /* Disable the general interrupt. */
    *isr_Tick_INTC_CLR_EN = isr_Tick__INTC_MASK;
}


/*******************************************************************************
* Function Name: isr_Tick_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_SetPending(void)
{
    *isr_Tick_INTC_SET_PD = isr_Tick__INTC_MASK;
}


/*******************************************************************************
* Function Name: isr_Tick_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void isr_Tick_ClearPending(void)
{
    *isr_Tick_INTC_CLR_PD = isr_Tick__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
