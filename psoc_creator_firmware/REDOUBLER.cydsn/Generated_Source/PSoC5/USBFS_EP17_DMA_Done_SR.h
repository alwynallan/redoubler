/*******************************************************************************
* File Name: USBFS_EP17_DMA_Done_SR.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_USBFS_EP17_DMA_Done_SR_H) /* CY_STATUS_REG_USBFS_EP17_DMA_Done_SR_H */
#define CY_STATUS_REG_USBFS_EP17_DMA_Done_SR_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 USBFS_EP17_DMA_Done_SR_Read(void) ;
void USBFS_EP17_DMA_Done_SR_InterruptEnable(void) ;
void USBFS_EP17_DMA_Done_SR_InterruptDisable(void) ;
void USBFS_EP17_DMA_Done_SR_WriteMask(uint8 mask) ;
uint8 USBFS_EP17_DMA_Done_SR_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define USBFS_EP17_DMA_Done_SR_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define USBFS_EP17_DMA_Done_SR_INPUTS              7


/***************************************
*             Registers
***************************************/

/* Status Register */
#define USBFS_EP17_DMA_Done_SR_Status             (* (reg8 *) USBFS_EP17_DMA_Done_SR_sts_intr_sts_reg__STATUS_REG )
#define USBFS_EP17_DMA_Done_SR_Status_PTR         (  (reg8 *) USBFS_EP17_DMA_Done_SR_sts_intr_sts_reg__STATUS_REG )
#define USBFS_EP17_DMA_Done_SR_Status_Mask        (* (reg8 *) USBFS_EP17_DMA_Done_SR_sts_intr_sts_reg__MASK_REG )
#define USBFS_EP17_DMA_Done_SR_Status_Aux_Ctrl    (* (reg8 *) USBFS_EP17_DMA_Done_SR_sts_intr_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_USBFS_EP17_DMA_Done_SR_H */


/* [] END OF FILE */
