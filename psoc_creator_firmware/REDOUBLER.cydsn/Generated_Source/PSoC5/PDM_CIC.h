/*******************************************************************************
* File Name: PDM_CIC.h
* Version 2.0
*
* Description:
*  This header file contains definitions associated with the PDM CIC Filter component.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined (PDM_CIC_H)
#define PDM_CIC_H

#include "cyfitter.h"
#include "cytypes.h"   

/* Conditional compilation parameter for including interrupt related API's */
#define PDM_CIC_INTERRUPT_ENABLED 1

/* Decimation counter period is one less than decimation rate */
#define PDM_CIC_CNT7_PERIOD       (((uint8)(32)) - 1)

#define PDM_CIC_COMB_CTRL_AVAIL   0

#define PDM_CIC_MIC_CHANNEL       2

#define PDM_CIC_RIGHT_CHANNEL      0u
#define PDM_CIC_LEFT_CHANNEL       1u
#define PDM_CIC_STEREO_CHANNEL     2u

#define PDM_CIC_RIGHT_CHANNEL_ENABLED  (PDM_CIC_MIC_CHANNEL != PDM_CIC_LEFT_CHANNEL)
#define PDM_CIC_LEFT_CHANNEL_ENABLED   (PDM_CIC_MIC_CHANNEL != PDM_CIC_RIGHT_CHANNEL)

/***************************************
*             Registers
***************************************/

/* Address of registers holding the CIC output for each microphone channel. Note that these registers
   hold 16-bit values */
#if (PDM_CIC_RIGHT_CHANNEL_ENABLED)
	#define PDM_CIC_RIGHT_LO16_OUTPUT_REG_PTR  PDM_CIC_Comb_R_genblk2_dp32_u0__16BIT_F0_REG
	#define PDM_CIC_RIGHT_HI16_OUTPUT_REG_PTR  PDM_CIC_Comb_R_genblk2_dp32_u2__16BIT_F0_REG
#endif

#if (PDM_CIC_LEFT_CHANNEL_ENABLED)
	#define PDM_CIC_LEFT_LO16_OUTPUT_REG_PTR  PDM_CIC_Comb_L_genblk2_dp32_u0__16BIT_F0_REG
	#define PDM_CIC_LEFT_HI16_OUTPUT_REG_PTR  PDM_CIC_Comb_L_genblk2_dp32_u2__16BIT_F0_REG
#endif

/* Count7 decimation rate counter period register */
#define PDM_CIC_CNT7_PERIOD_REG   (* (reg8 *) PDM_CIC_Integrator_Counter7__PERIOD_REG)

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 Cnt7Period;
} PDM_CIC_BACKUP_STRUCT;

/***************************************
*        Function Prototypes
***************************************/

/* Starts all the components associated with the PDM CIC */
void PDM_CIC_Start(void);

/* Stops all the components associated with the PDM CIC */
void PDM_CIC_Stop(void);

/* Saves the current component configuration */
void PDM_CIC_SaveConfig(void);

/* Restores the last saved component configuration */
void PDM_CIC_RestoreConfig(void);

/* Prepares the component for low power mode entry */
void PDM_CIC_Sleep(void);

/* Restores the component after low power mode exit */
void PDM_CIC_Wakeup(void);

/* Conditional compilation of Interrupt related API's */
#if (PDM_CIC_INTERRUPT_ENABLED)
uint8 PDM_CIC_ReadInterruptStatus(void);
void  PDM_CIC_EnableInterruptGeneration(void);
void  PDM_CIC_DisableInterruptGeneration(void);
#endif

/* Integrator control register mask definitions */
#define PDM_CIC_INT_ENABLE_MASK		    (PDM_CIC_Int_Ctrl_Reg_Sync_ctrl_reg__0__MASK)

#if (PDM_CIC_COMB_CTRL_AVAIL)
	/* Comb control register mask definitions */
	#define PDM_CIC_COMB_ENABLE_MASK		    (PDM_CIC_Comb_Ctrl_Reg_Sync_ctrl_reg__0__MASK)
#endif

#if (PDM_CIC_INTERRUPT_ENABLED)
	/* Status Register mask definitions */
	#define PDM_CIC_INTEGRATOR_R_FIFO_OVERFLOW_MASK    (PDM_CIC_Status_Reg_sts_intr_sts_reg__1__MASK)
	#define PDM_CIC_COMB_R_FIFO_OVERFLOW_MASK          (PDM_CIC_Status_Reg_sts_intr_sts_reg__3__MASK)		
	#define PDM_CIC_INTEGRATOR_L_FIFO_OVERFLOW_MASK    (PDM_CIC_Status_Reg_sts_intr_sts_reg__0__MASK)
	#define PDM_CIC_COMB_L_FIFO_OVERFLOW_MASK          (PDM_CIC_Status_Reg_sts_intr_sts_reg__2__MASK)	

#endif

/* Component disabled state value */
#define PDM_CIC_DISABLED                      (0x00u)


#if (PDM_CIC_COMB_CTRL_AVAIL)
	/* Macro to check component enable state */
	#define PDM_CIC_IS_ENABLE   \
					((PDM_CIC_Int_Ctrl_Reg_Control & PDM_CIC_INT_ENABLE_MASK) && \
					(PDM_CIC_Comb_Ctrl_Reg_Control & PDM_CIC_COMB_ENABLE_MASK))
#else
	/* Macro to check component enable state */
	#define PDM_CIC_IS_ENABLE   \
					((PDM_CIC_Int_Ctrl_Reg_Control & PDM_CIC_INT_ENABLE_MASK) != 0)					
#endif

#endif /* PDM_CIC_H */
//[] END OF FILE
