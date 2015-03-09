/***************************************************************************
* File Name: RxDMA_dma.c  
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
#include <RxDMA_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* RxDMA__DRQ_CTL_REG
* 
* 
* RxDMA__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* RxDMA__NUMBEROF_TDS
* 
* Priority of this channel.
* RxDMA__PRIORITY
* 
* True if RxDMA_TERMIN_SEL is used.
* RxDMA__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* RxDMA__TERMIN_SEL
* 
* 
* True if RxDMA_TERMOUT0_SEL is used.
* RxDMA__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* RxDMA__TERMOUT0_SEL
* 
* 
* True if RxDMA_TERMOUT1_SEL is used.
* RxDMA__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* RxDMA__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of RxDMA dma channel */
uint8 RxDMA_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 RxDMA_DmaInitalize
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
uint8 RxDMA_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    RxDMA_DmaHandle = (uint8)RxDMA__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(RxDMA_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)RxDMA__TERMOUT0_SEL,
                                  (uint8)RxDMA__TERMOUT1_SEL,
                                  (uint8)RxDMA__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(RxDMA_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(RxDMA_DmaHandle, (uint8)RxDMA__PRIORITY);
    
    return RxDMA_DmaHandle;
}

/*********************************************************************
* Function Name: void RxDMA_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with RxDMA.
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
void RxDMA_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(RxDMA_DmaHandle);
}

