/***************************************************************************
* File Name: USBOutDMA_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <USBOutDMA_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* USBOutDMA__DRQ_CTL_REG
* 
* 
* USBOutDMA__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* USBOutDMA__NUMBEROF_TDS
* 
* Priority of this channel.
* USBOutDMA__PRIORITY
* 
* True if USBOutDMA_TERMIN_SEL is used.
* USBOutDMA__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* USBOutDMA__TERMIN_SEL
* 
* 
* True if USBOutDMA_TERMOUT0_SEL is used.
* USBOutDMA__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* USBOutDMA__TERMOUT0_SEL
* 
* 
* True if USBOutDMA_TERMOUT1_SEL is used.
* USBOutDMA__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* USBOutDMA__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of USBOutDMA dma channel */
uint8 USBOutDMA_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 USBOutDMA_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 USBOutDMA_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    USBOutDMA_DmaHandle = (uint8)USBOutDMA__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(USBOutDMA_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)USBOutDMA__TERMOUT0_SEL,
                                  (uint8)USBOutDMA__TERMOUT1_SEL,
                                  (uint8)USBOutDMA__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(USBOutDMA_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(USBOutDMA_DmaHandle, (uint8)USBOutDMA__PRIORITY);
    
    return USBOutDMA_DmaHandle;
}

/*********************************************************************
* Function Name: void USBOutDMA_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with USBOutDMA.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void USBOutDMA_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(USBOutDMA_DmaHandle);
}

