/*******************************************************************************
* File Name: isr_Tick.h
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
#if !defined(CY_ISR_isr_Tick_H)
#define CY_ISR_isr_Tick_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Tick_Start(void);
void isr_Tick_StartEx(cyisraddress address);
void isr_Tick_Stop(void);

CY_ISR_PROTO(isr_Tick_Interrupt);

void isr_Tick_SetVector(cyisraddress address);
cyisraddress isr_Tick_GetVector(void);

void isr_Tick_SetPriority(uint8 priority);
uint8 isr_Tick_GetPriority(void);

void isr_Tick_Enable(void);
uint8 isr_Tick_GetState(void);
void isr_Tick_Disable(void);

void isr_Tick_SetPending(void);
void isr_Tick_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Tick ISR. */
#define isr_Tick_INTC_VECTOR            ((reg32 *) isr_Tick__INTC_VECT)

/* Address of the isr_Tick ISR priority. */
#define isr_Tick_INTC_PRIOR             ((reg8 *) isr_Tick__INTC_PRIOR_REG)

/* Priority of the isr_Tick interrupt. */
#define isr_Tick_INTC_PRIOR_NUMBER      isr_Tick__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Tick interrupt. */
#define isr_Tick_INTC_SET_EN            ((reg32 *) isr_Tick__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Tick interrupt. */
#define isr_Tick_INTC_CLR_EN            ((reg32 *) isr_Tick__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Tick interrupt state to pending. */
#define isr_Tick_INTC_SET_PD            ((reg32 *) isr_Tick__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Tick interrupt. */
#define isr_Tick_INTC_CLR_PD            ((reg32 *) isr_Tick__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Tick_H */


/* [] END OF FILE */
