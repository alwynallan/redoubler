/***************************************************************************
* File Name: PDM_CIC_DMA_CombD0Update_L_dma.c  
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
#include <PDM_CIC_DMA_CombD0Update_L_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* PDM_CIC_DMA_CombD0Update_L__DRQ_CTL_REG
* 
* 
* PDM_CIC_DMA_CombD0Update_L__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* PDM_CIC_DMA_CombD0Update_L__NUMBEROF_TDS
* 
* Priority of this channel.
* PDM_CIC_DMA_CombD0Update_L__PRIORITY
* 
* True if PDM_CIC_DMA_CombD0Update_L_TERMIN_SEL is used.
* PDM_CIC_DMA_CombD0Update_L__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* PDM_CIC_DMA_CombD0Update_L__TERMIN_SEL
* 
* 
* True if PDM_CIC_DMA_CombD0Update_L_TERMOUT0_SEL is used.
* PDM_CIC_DMA_CombD0Update_L__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* PDM_CIC_DMA_CombD0Update_L__TERMOUT0_SEL
* 
* 
* True if PDM_CIC_DMA_CombD0Update_L_TERMOUT1_SEL is used.
* PDM_CIC_DMA_CombD0Update_L__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* PDM_CIC_DMA_CombD0Update_L__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of PDM_CIC_DMA_CombD0Update_L dma channel */
uint8 PDM_CIC_DMA_CombD0Update_L_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 PDM_CIC_DMA_CombD0Update_L_DmaInitalize
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
uint8 PDM_CIC_DMA_CombD0Update_L_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    PDM_CIC_DMA_CombD0Update_L_DmaHandle = (uint8)PDM_CIC_DMA_CombD0Update_L__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(PDM_CIC_DMA_CombD0Update_L_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)PDM_CIC_DMA_CombD0Update_L__TERMOUT0_SEL,
                                  (uint8)PDM_CIC_DMA_CombD0Update_L__TERMOUT1_SEL,
                                  (uint8)PDM_CIC_DMA_CombD0Update_L__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(PDM_CIC_DMA_CombD0Update_L_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(PDM_CIC_DMA_CombD0Update_L_DmaHandle, (uint8)PDM_CIC_DMA_CombD0Update_L__PRIORITY);
    
    return PDM_CIC_DMA_CombD0Update_L_DmaHandle;
}

/*********************************************************************
* Function Name: void PDM_CIC_DMA_CombD0Update_L_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with PDM_CIC_DMA_CombD0Update_L.
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
void PDM_CIC_DMA_CombD0Update_L_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(PDM_CIC_DMA_CombD0Update_L_DmaHandle);
}

