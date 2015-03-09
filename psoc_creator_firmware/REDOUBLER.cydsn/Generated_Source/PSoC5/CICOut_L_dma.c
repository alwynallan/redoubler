/***************************************************************************
* File Name: CICOut_L_dma.c  
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
#include <CICOut_L_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* CICOut_L__DRQ_CTL_REG
* 
* 
* CICOut_L__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* CICOut_L__NUMBEROF_TDS
* 
* Priority of this channel.
* CICOut_L__PRIORITY
* 
* True if CICOut_L_TERMIN_SEL is used.
* CICOut_L__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* CICOut_L__TERMIN_SEL
* 
* 
* True if CICOut_L_TERMOUT0_SEL is used.
* CICOut_L__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* CICOut_L__TERMOUT0_SEL
* 
* 
* True if CICOut_L_TERMOUT1_SEL is used.
* CICOut_L__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* CICOut_L__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of CICOut_L dma channel */
uint8 CICOut_L_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 CICOut_L_DmaInitalize
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
uint8 CICOut_L_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    CICOut_L_DmaHandle = (uint8)CICOut_L__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(CICOut_L_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)CICOut_L__TERMOUT0_SEL,
                                  (uint8)CICOut_L__TERMOUT1_SEL,
                                  (uint8)CICOut_L__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(CICOut_L_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(CICOut_L_DmaHandle, (uint8)CICOut_L__PRIORITY);
    
    return CICOut_L_DmaHandle;
}

/*********************************************************************
* Function Name: void CICOut_L_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with CICOut_L.
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
void CICOut_L_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(CICOut_L_DmaHandle);
}

