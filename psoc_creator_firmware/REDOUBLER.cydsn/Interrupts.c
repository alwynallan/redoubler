/*******************************************************************************
* File Name: Interrupts.c
*
* Version 1.0
*
*  Description: This file contains interrupt service routines for all the interrupts
*               in the system
*
********************************************************************************
* Copyright (2008-2013), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/
#include <Application.h>
#include <AudioControl.h>
#include <Configuration.h>
#include <device.h>
#include <Interrupts.h>
#include <USBInterface.h>
extern uint16 inCnt;
extern uint16 inLevel;
extern uint16 inUsbCount;
extern uint16 inUsbShadow;
extern CYBIT applicationTimerTick;
extern uint16 outLevel;
extern uint16 outUsbCount;
extern uint16 outUsbShadow;

extern volatile uint8 USBFS_device;

#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
extern CYBIT inPlaying;
#endif

#ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
extern CYBIT outPlaying;
#endif

/*******************************************************************************
* Function Name: InDMADone_Interrupt
********************************************************************************
* Summary:
*   The Interrupt Service Routine for isr_InDMADone. Arms USB Audio In end-point
* 	for USB host to receive audio data.
*
* Parameters:  
*	InDMADone interrupt vector
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(InDMADone_Interrupt)
{
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
    /* Parameters to this API Call CHANGES DEPENDING ON DATA ENDPOINT MEMORY MODE */
    USBFS_LoadInEP(AUDIO_IN_ENDPOINT, USBFS_NULL, inCnt);
	#endif
    
    /* USER_CODE: [Audio IN EP loaded] This ISR is triggered once the required audio IN data for the next USB audio IN
     * transfer is made available at the USB audio IN endpoint memory */
}

/*******************************************************************************
* Function Name: RxDMADone_Interrupt
********************************************************************************
* Summary:
*   The Interrupt Service Routine for isr_RxDMADone. This handles the AUDIO In
*	buffer pointers and detects overflow of the buffer to stop AUDIO In. 
*
* Parameters:  
*	RxDMADone interrupt vector
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(RxDMADone_Interrupt)
{
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY 
    uint16 removed;
	
	/* Note: Care must be taken in the application code to update inUsbCount atomically */
	removed = inUsbCount - inUsbShadow;
	inLevel -= removed;
    
    #if 0
	if (inLevel <= IN_TRANS_SIZE) 
		for(;;) ;		/* Underflow should not happen */
    #endif
    
	inUsbShadow = inUsbCount;
		
	if (inLevel >= IN_BUFSIZE) 
    {
       Stop_PDM_InPath();
	}
	else 
    {
		inLevel += IN_TRANS_SIZE;
	}
    #endif
    
    /* USER_CODE: [Audio IN buffer pointers] ISR triggered by audio IN data transfer DMA (see TopDesign.sch) to track
     * the audio IN buffer pointers */
}

/*******************************************************************************
* Function Name: Tick_Interrupt
********************************************************************************
* Summary:
*   The Interrupt Service Routine for isr_Tick. Sets flag for the timer function
*	to manage all counting operations
*
* Parameters:  
*	Sleep Timer tick interrupt vector
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(Tick_Interrupt)
{
    applicationTimerTick = CY_PM_INT_SR_REG;	
	applicationTimerTick = TRUE;
}

/*******************************************************************************
* Function Name: TxDMADone_Interrupt
********************************************************************************
* Summary:
*   The Interrupt Service Routine for isr_TxDMADone. This handles the AUDIO Out
*	buffer pointers and detects underflow of the buffer to stop AUDIO out.
*
* Parameters:  
*	TxDMADone interrupt vector
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(TxDMADone_Interrupt)
{
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY 
	uint16 added;

	/* Note: Care must be taken in the application code to update outUsbCount atomically
	 * Code is currently implemented with both updaters of this value in interrupts that are
	 * the same priority so the code will not execute at the same time, but the code
	 * has been written so that this is not a requirement. */
    
	added = outUsbCount - outUsbShadow;
	outLevel += added;
    
    #if 0
	if (outLevel > OUT_BUFSIZE) 
		for(;;) ;		/* Overflow should not happen */
    #endif
    
	outUsbShadow = outUsbCount;
	
	if (outLevel <= OUT_AUDIOMAXPKT) 
	{
		/* Underflow, so disable the DMA, mute and tell the main task to reset all its structures Stop DMA */
		Stop_I2S_Tx();
	}
	else
	{
		outLevel -= OUT_TRANS_SIZE;
	}
    #endif
    
    /* USER_CODE: [Audio OUT buffer pointers] ISR triggered by audio OUT data transfer DMA (see TopDesign.sch) to track
     * the audio OUT buffer pointers */
}

/* [] END OF FILE */
