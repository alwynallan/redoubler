/***************************************************************************
* File Name: TxDMA_dma.c  
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
#include <TxDMA_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* TxDMA__DRQ_CTL_REG
* 
* 
* TxDMA__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* TxDMA__NUMBEROF_TDS
* 
* Priority of this channel.
* TxDMA__PRIORITY
* 
* True if TxDMA_TERMIN_SEL is used.
* TxDMA__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* TxDMA__TERMIN_SEL
* 
* 
* True if TxDMA_TERMOUT0_SEL is used.
* TxDMA__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* TxDMA__TERMOUT0_SEL
* 
* 
* True if TxDMA_TERMOUT1_SEL is used.
* TxDMA__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* TxDMA__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of TxDMA dma channel */
uint8 TxDMA_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 TxDMA_DmaInitalize
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
uint8 TxDMA_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    TxDMA_DmaHandle = (uint8)TxDMA__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(TxDMA_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)TxDMA__TERMOUT0_SEL,
                                  (uint8)TxDMA__TERMOUT1_SEL,
                                  (uint8)TxDMA__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(TxDMA_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(TxDMA_DmaHandle, (uint8)TxDMA__PRIORITY);
    
    return TxDMA_DmaHandle;
}

/*********************************************************************
* Function Name: void TxDMA_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with TxDMA.
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
void TxDMA_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(TxDMA_DmaHandle);
}

