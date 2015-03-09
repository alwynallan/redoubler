/***************************************************************************
* File Name: USBFS_ep7_dma.c  
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
#include <USBFS_ep7_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* USBFS_ep7__DRQ_CTL_REG
* 
* 
* USBFS_ep7__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* USBFS_ep7__NUMBEROF_TDS
* 
* Priority of this channel.
* USBFS_ep7__PRIORITY
* 
* True if USBFS_ep7_TERMIN_SEL is used.
* USBFS_ep7__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* USBFS_ep7__TERMIN_SEL
* 
* 
* True if USBFS_ep7_TERMOUT0_SEL is used.
* USBFS_ep7__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* USBFS_ep7__TERMOUT0_SEL
* 
* 
* True if USBFS_ep7_TERMOUT1_SEL is used.
* USBFS_ep7__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* USBFS_ep7__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of USBFS_ep7 dma channel */
uint8 USBFS_ep7_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 USBFS_ep7_DmaInitalize
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
uint8 USBFS_ep7_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    USBFS_ep7_DmaHandle = (uint8)USBFS_ep7__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(USBFS_ep7_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)USBFS_ep7__TERMOUT0_SEL,
                                  (uint8)USBFS_ep7__TERMOUT1_SEL,
                                  (uint8)USBFS_ep7__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(USBFS_ep7_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(USBFS_ep7_DmaHandle, (uint8)USBFS_ep7__PRIORITY);
    
    return USBFS_ep7_DmaHandle;
}

/*********************************************************************
* Function Name: void USBFS_ep7_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with USBFS_ep7.
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
void USBFS_ep7_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(USBFS_ep7_DmaHandle);
}

