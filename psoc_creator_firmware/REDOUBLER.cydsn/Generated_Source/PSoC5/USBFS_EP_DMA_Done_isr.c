/*******************************************************************************
* File Name: USBFS_EP_DMA_Done_isr.c  
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
#include <USBFS_EP_DMA_Done_isr.h>

#if !defined(USBFS_EP_DMA_Done_isr__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START USBFS_EP_DMA_Done_isr_intc` */

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
* Function Name: USBFS_EP_DMA_Done_isr_Start
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
void USBFS_EP_DMA_Done_isr_Start(void)
{
    /* For all we know the interrupt is active. */
    USBFS_EP_DMA_Done_isr_Disable();

    /* Set the ISR to point to the USBFS_EP_DMA_Done_isr Interrupt. */
    USBFS_EP_DMA_Done_isr_SetVector(&USBFS_EP_DMA_Done_isr_Interrupt);

    /* Set the priority. */
    USBFS_EP_DMA_Done_isr_SetPriority((uint8)USBFS_EP_DMA_Done_isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    USBFS_EP_DMA_Done_isr_Enable();
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_StartEx
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
void USBFS_EP_DMA_Done_isr_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    USBFS_EP_DMA_Done_isr_Disable();

    /* Set the ISR to point to the USBFS_EP_DMA_Done_isr Interrupt. */
    USBFS_EP_DMA_Done_isr_SetVector(address);

    /* Set the priority. */
    USBFS_EP_DMA_Done_isr_SetPriority((uint8)USBFS_EP_DMA_Done_isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    USBFS_EP_DMA_Done_isr_Enable();
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_Stop
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
void USBFS_EP_DMA_Done_isr_Stop(void)
{
    /* Disable this interrupt. */
    USBFS_EP_DMA_Done_isr_Disable();

    /* Set the ISR to point to the passive one. */
    USBFS_EP_DMA_Done_isr_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for USBFS_EP_DMA_Done_isr.
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
CY_ISR(USBFS_EP_DMA_Done_isr_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START USBFS_EP_DMA_Done_isr_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling USBFS_EP_DMA_Done_isr_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use USBFS_EP_DMA_Done_isr_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void USBFS_EP_DMA_Done_isr_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)USBFS_EP_DMA_Done_isr__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_GetVector
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
cyisraddress USBFS_EP_DMA_Done_isr_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)USBFS_EP_DMA_Done_isr__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling USBFS_EP_DMA_Done_isr_Start
*   or USBFS_EP_DMA_Done_isr_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   USBFS_EP_DMA_Done_isr_Start or USBFS_EP_DMA_Done_isr_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void USBFS_EP_DMA_Done_isr_SetPriority(uint8 priority)
{
    *USBFS_EP_DMA_Done_isr_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_GetPriority
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
uint8 USBFS_EP_DMA_Done_isr_GetPriority(void)
{
    uint8 priority;


    priority = *USBFS_EP_DMA_Done_isr_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_Enable
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
void USBFS_EP_DMA_Done_isr_Enable(void)
{
    /* Enable the general interrupt. */
    *USBFS_EP_DMA_Done_isr_INTC_SET_EN = USBFS_EP_DMA_Done_isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_GetState
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
uint8 USBFS_EP_DMA_Done_isr_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*USBFS_EP_DMA_Done_isr_INTC_SET_EN & (uint32)USBFS_EP_DMA_Done_isr__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_Disable
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
void USBFS_EP_DMA_Done_isr_Disable(void)
{
    /* Disable the general interrupt. */
    *USBFS_EP_DMA_Done_isr_INTC_CLR_EN = USBFS_EP_DMA_Done_isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_SetPending
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
void USBFS_EP_DMA_Done_isr_SetPending(void)
{
    *USBFS_EP_DMA_Done_isr_INTC_SET_PD = USBFS_EP_DMA_Done_isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: USBFS_EP_DMA_Done_isr_ClearPending
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
void USBFS_EP_DMA_Done_isr_ClearPending(void)
{
    *USBFS_EP_DMA_Done_isr_INTC_CLR_PD = USBFS_EP_DMA_Done_isr__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
