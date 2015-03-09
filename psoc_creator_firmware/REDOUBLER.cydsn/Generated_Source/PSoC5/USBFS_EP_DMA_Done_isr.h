/*******************************************************************************
* File Name: USBFS_EP_DMA_Done_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_USBFS_EP_DMA_Done_isr_H)
#define CY_ISR_USBFS_EP_DMA_Done_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void USBFS_EP_DMA_Done_isr_Start(void);
void USBFS_EP_DMA_Done_isr_StartEx(cyisraddress address);
void USBFS_EP_DMA_Done_isr_Stop(void);

CY_ISR_PROTO(USBFS_EP_DMA_Done_isr_Interrupt);

void USBFS_EP_DMA_Done_isr_SetVector(cyisraddress address);
cyisraddress USBFS_EP_DMA_Done_isr_GetVector(void);

void USBFS_EP_DMA_Done_isr_SetPriority(uint8 priority);
uint8 USBFS_EP_DMA_Done_isr_GetPriority(void);

void USBFS_EP_DMA_Done_isr_Enable(void);
uint8 USBFS_EP_DMA_Done_isr_GetState(void);
void USBFS_EP_DMA_Done_isr_Disable(void);

void USBFS_EP_DMA_Done_isr_SetPending(void);
void USBFS_EP_DMA_Done_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the USBFS_EP_DMA_Done_isr ISR. */
#define USBFS_EP_DMA_Done_isr_INTC_VECTOR            ((reg32 *) USBFS_EP_DMA_Done_isr__INTC_VECT)

/* Address of the USBFS_EP_DMA_Done_isr ISR priority. */
#define USBFS_EP_DMA_Done_isr_INTC_PRIOR             ((reg8 *) USBFS_EP_DMA_Done_isr__INTC_PRIOR_REG)

/* Priority of the USBFS_EP_DMA_Done_isr interrupt. */
#define USBFS_EP_DMA_Done_isr_INTC_PRIOR_NUMBER      USBFS_EP_DMA_Done_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable USBFS_EP_DMA_Done_isr interrupt. */
#define USBFS_EP_DMA_Done_isr_INTC_SET_EN            ((reg32 *) USBFS_EP_DMA_Done_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the USBFS_EP_DMA_Done_isr interrupt. */
#define USBFS_EP_DMA_Done_isr_INTC_CLR_EN            ((reg32 *) USBFS_EP_DMA_Done_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the USBFS_EP_DMA_Done_isr interrupt state to pending. */
#define USBFS_EP_DMA_Done_isr_INTC_SET_PD            ((reg32 *) USBFS_EP_DMA_Done_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the USBFS_EP_DMA_Done_isr interrupt. */
#define USBFS_EP_DMA_Done_isr_INTC_CLR_PD            ((reg32 *) USBFS_EP_DMA_Done_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_USBFS_EP_DMA_Done_isr_H */


/* [] END OF FILE */
