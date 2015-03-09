/*******************************************************************************
* File Name: isr_RxDMADone.h
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
#if !defined(CY_ISR_isr_RxDMADone_H)
#define CY_ISR_isr_RxDMADone_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_RxDMADone_Start(void);
void isr_RxDMADone_StartEx(cyisraddress address);
void isr_RxDMADone_Stop(void);

CY_ISR_PROTO(isr_RxDMADone_Interrupt);

void isr_RxDMADone_SetVector(cyisraddress address);
cyisraddress isr_RxDMADone_GetVector(void);

void isr_RxDMADone_SetPriority(uint8 priority);
uint8 isr_RxDMADone_GetPriority(void);

void isr_RxDMADone_Enable(void);
uint8 isr_RxDMADone_GetState(void);
void isr_RxDMADone_Disable(void);

void isr_RxDMADone_SetPending(void);
void isr_RxDMADone_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_RxDMADone ISR. */
#define isr_RxDMADone_INTC_VECTOR            ((reg32 *) isr_RxDMADone__INTC_VECT)

/* Address of the isr_RxDMADone ISR priority. */
#define isr_RxDMADone_INTC_PRIOR             ((reg8 *) isr_RxDMADone__INTC_PRIOR_REG)

/* Priority of the isr_RxDMADone interrupt. */
#define isr_RxDMADone_INTC_PRIOR_NUMBER      isr_RxDMADone__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_RxDMADone interrupt. */
#define isr_RxDMADone_INTC_SET_EN            ((reg32 *) isr_RxDMADone__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_RxDMADone interrupt. */
#define isr_RxDMADone_INTC_CLR_EN            ((reg32 *) isr_RxDMADone__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_RxDMADone interrupt state to pending. */
#define isr_RxDMADone_INTC_SET_PD            ((reg32 *) isr_RxDMADone__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_RxDMADone interrupt. */
#define isr_RxDMADone_INTC_CLR_PD            ((reg32 *) isr_RxDMADone__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_RxDMADone_H */


/* [] END OF FILE */
