/*******************************************************************************
* File Name: PDM_CIC.c
* Version 2.0
*
* Description:
*  This file contains the function definitions associated with the PDM CIC
*  filter component
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PDM_CIC.h"
#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

#include "PDM_CIC_Int_Ctrl_Reg.h"

#if (PDM_CIC_COMB_CTRL_AVAIL)
	#include "PDM_CIC_Comb_Ctrl_Reg.h"
#endif

#if (PDM_CIC_RIGHT_CHANNEL_ENABLED)
	#include "PDM_CIC_DMA_CombD0Update_R_dma.h"
	#include "PDM_CIC_DMA_IntOut_R_dma.h"
#endif

#if (PDM_CIC_LEFT_CHANNEL_ENABLED)
	#include "PDM_CIC_DMA_CombD0Update_L_dma.h"
	#include "PDM_CIC_DMA_IntOut_L_dma.h"
#endif


#if (PDM_CIC_INTERRUPT_ENABLED)
	#include "PDM_CIC_Status_Reg.h"
#endif

#if(PDM_CIC_LEFT_CHANNEL_ENABLED)
	/* Address of registers holding the Integrator output. Note that these registers
	   hold 16-bit values */
	#define PDM_CIC_INT_L_LO16_OUTPUT_REG_PTR  PDM_CIC_Integrator_genblk2_dp32_l_u0__16BIT_F0_REG
	#define PDM_CIC_INT_L_HI16_OUTPUT_REG_PTR  PDM_CIC_Integrator_genblk2_dp32_l_u2__16BIT_F0_REG

	/* Address of registers holding the comb input for first stage. Note that these registers
	   hold 16-bit values */
	#define PDM_CIC_COMB_L_LO16_INPUT_REG_PTR  PDM_CIC_Comb_L_genblk2_dp32_u0__16BIT_A0_REG
	#define PDM_CIC_COMB_L_HI16_INPUT_REG_PTR  PDM_CIC_Comb_L_genblk2_dp32_u2__16BIT_A0_REG
#endif

#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
	/* Address of registers holding the Integrator output. Note that these registers
	   hold 16-bit values */
	#define PDM_CIC_INT_R_LO16_OUTPUT_REG_PTR  PDM_CIC_Integrator_genblk3_dp32_r_u0__16BIT_F0_REG
	#define PDM_CIC_INT_R_HI16_OUTPUT_REG_PTR  PDM_CIC_Integrator_genblk3_dp32_r_u2__16BIT_F0_REG

	/* Address of registers holding the comb input for first stage. Note that these registers
	   hold 16-bit values */
	#define PDM_CIC_COMB_R_LO16_INPUT_REG_PTR  PDM_CIC_Comb_R_genblk2_dp32_u0__16BIT_A0_REG
	#define PDM_CIC_COMB_R_HI16_INPUT_REG_PTR  PDM_CIC_Comb_R_genblk2_dp32_u2__16BIT_A0_REG
#endif

uint8 PDM_CIC_initVar = 0u;

static PDM_CIC_BACKUP_STRUCT  PDM_CIC_backup =
{
    /* Component disabled by deafult */
    PDM_CIC_DISABLED,

    /* Decimation counter period */
    PDM_CIC_CNT7_PERIOD,

};

/***************************************
*        Function Prototypes
***************************************/

static void PDM_CIC_Integrator_Init(void);
static void PDM_CIC_Comb_Init(void);

#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
	static void PDM_CIC_IntOutDma_R_Init(void);
	static void PDM_CIC_IntOutDma_R_Start(void);
	static void PDM_CIC_IntOutDma_R_Stop(void);
	static void PDM_CIC_CombD0UpdateDma_R_Init(void);
	static void PDM_CIC_CombD0UpdateDma_R_Start(void);
	static void PDM_CIC_CombD0UpdateDma_R_Stop(void);
#endif

#if(PDM_CIC_LEFT_CHANNEL_ENABLED)
	static void PDM_CIC_IntOutDma_L_Init(void);
	static void PDM_CIC_IntOutDma_L_Start(void);
	static void PDM_CIC_IntOutDma_L_Stop(void);
	static void PDM_CIC_CombD0UpdateDma_L_Init(void);
	static void PDM_CIC_CombD0UpdateDma_L_Start(void);
	static void PDM_CIC_CombD0UpdateDma_L_Stop(void);
#endif

/*******************************************************************************
* Function Name: PDM_CIC_Start
********************************************************************************
*
* Summary:
*  Starts the PDM CIC Filter component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PDM_CIC_initVar - is used to indicate initial configuration
*  of this component.  The variable is initialized to zero and set to 1
*  the first time PDM_CIC_Start() is called. This allows for component
*  initialization without re-initialization in all subsequent calls
*  to the PDM_CIC_Start() routine.
*
*
*******************************************************************************/
void PDM_CIC_Start(void)
{
    if(0u == PDM_CIC_initVar)
    {
        /* Initialize DMA's only the first time */
		
		#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
	        PDM_CIC_IntOutDma_R_Init();
			PDM_CIC_CombD0UpdateDma_R_Init();	
		#endif
		
		#if(PDM_CIC_LEFT_CHANNEL_ENABLED)
	        PDM_CIC_IntOutDma_L_Init();
			PDM_CIC_CombD0UpdateDma_L_Init();
		#endif		

        /* Set init flag */
        PDM_CIC_initVar = 1u;
    }
	
	PDM_CIC_Int_Ctrl_Reg_Control = PDM_CIC_Int_Ctrl_Reg_Control & (~PDM_CIC_INT_ENABLE_MASK);
	
	#if(PDM_CIC_COMB_CTRL_AVAIL)
		PDM_CIC_Comb_Ctrl_Reg_Control = PDM_CIC_Comb_Ctrl_Reg_Control & (~PDM_CIC_COMB_ENABLE_MASK);
	#endif /* (PDM_CIC_COMB_CTRL_AVAIL) */

	/* Initialize the comb and integrator components */
	PDM_CIC_Comb_Init();
	PDM_CIC_Integrator_Init();	
	
	#if(PDM_CIC_LEFT_CHANNEL_ENABLED)
		/*  Start the DMA channels */
		PDM_CIC_IntOutDma_L_Start();
		PDM_CIC_CombD0UpdateDma_L_Start();
	#endif
	
	#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
		/*  Start the DMA channels */
		PDM_CIC_IntOutDma_R_Start();
		PDM_CIC_CombD0UpdateDma_R_Start();	
	#endif
	
	/* Enable interrupt status generation if required */
	#if (PDM_CIC_INTERRUPT_ENABLED)
		PDM_CIC_ReadInterruptStatus(); /* Clear the status register before enabling interrupt */
		PDM_CIC_EnableInterruptGeneration();
	#endif
	
	#if(PDM_CIC_COMB_CTRL_AVAIL)
		PDM_CIC_Comb_Ctrl_Reg_Control = PDM_CIC_Comb_Ctrl_Reg_Control | PDM_CIC_COMB_ENABLE_MASK;
	#endif /* (PDM_CIC_COMB_CTRL_AVAIL) */
	
	PDM_CIC_Int_Ctrl_Reg_Control = PDM_CIC_Int_Ctrl_Reg_Control | PDM_CIC_INT_ENABLE_MASK;

}

/*******************************************************************************
* Function Name: PDM_CIC_Stop
********************************************************************************
*
* Summary:
*  Stops the PDM CIC Filter component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  None.
*
*
*******************************************************************************/
void PDM_CIC_Stop(void)
{	
	#if(PDM_CIC_LEFT_CHANNEL_ENABLED)
		/*  Stop the DMA channels */
		PDM_CIC_IntOutDma_L_Stop();
		PDM_CIC_CombD0UpdateDma_L_Stop();
	#endif
	
	#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
		/*  Stop the DMA channels */
		PDM_CIC_IntOutDma_R_Stop();
		PDM_CIC_CombD0UpdateDma_R_Stop();	
	#endif	
	
	#if(PDM_CIC_COMB_CTRL_AVAIL)
		PDM_CIC_Comb_Ctrl_Reg_Control = PDM_CIC_Comb_Ctrl_Reg_Control & (~PDM_CIC_COMB_ENABLE_MASK);
	#endif /* (PDM_CIC_COMB_CTRL_AVAIL) */	
	
	PDM_CIC_Int_Ctrl_Reg_Control = PDM_CIC_Int_Ctrl_Reg_Control & (~PDM_CIC_INT_ENABLE_MASK);
	
	/* Disable interrupt status generation if required */
	#if (PDM_CIC_INTERRUPT_ENABLED)
		PDM_CIC_DisableInterruptGeneration();
		PDM_CIC_ReadInterruptStatus(); /* Clear the status register after disabling interrupt */
	#endif
}

/*******************************************************************************
* Function Name: PDM_CIC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves PDM CIC filter configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PDM_CIC_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PDM_CIC_SaveConfig(void)
{
	PDM_CIC_backup.Cnt7Period = PDM_CIC_CNT7_PERIOD_REG;
}

/*******************************************************************************
* Function Name: PDM_CIC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores PDM CIC filter configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PDM_CIC_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PDM_CIC_RestoreConfig(void)
{
	PDM_CIC_CNT7_PERIOD_REG = PDM_CIC_backup.Cnt7Period;
}

/*******************************************************************************
* Function Name: PDM_CIC_Sleep
********************************************************************************
*
* Summary:
*  Prepares PDM CIC component to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PDM_CIC_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PDM_CIC_Sleep(void)
{
    /* Get component state */
    PDM_CIC_backup.enableState = ((uint8) PDM_CIC_IS_ENABLE);

    /* Save registers configuration */
    PDM_CIC_SaveConfig();

    /* Stop component */
    PDM_CIC_Stop();
}

/*******************************************************************************
* Function Name: PDM_CIC_Wakeup
********************************************************************************
*
* Summary:
*  Prepares PDM CIC component for wakeup.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PDM_CIC_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
/* Restores the component after low power mode exit */
void PDM_CIC_Wakeup(void)
{
    /* Restore registers values */
    PDM_CIC_RestoreConfig();

    if(0u != PDM_CIC_backup.enableState)
    {
    	/* Start component */
    	PDM_CIC_Start();
    }
}

/* Conditional compilation of Interrupt related API's */
#if (PDM_CIC_INTERRUPT_ENABLED)

	/*******************************************************************************
	* Function Name: PDM_CIC_ReadInterruptStatus
	********************************************************************************
	*
	* Summary:
	*  Returns the current value of the PDM CIC status register
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  uint8 - Status register value
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	uint8 PDM_CIC_ReadInterruptStatus()
	{
		return(PDM_CIC_Status_Reg_Read());
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_EnableInterruptGeneration
	********************************************************************************
	*
	* Summary:
	*  Enables interrupt signal generation by the status register
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	void  PDM_CIC_EnableInterruptGeneration()
	{
		PDM_CIC_Status_Reg_InterruptEnable();
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_DisableInterruptGeneration
	********************************************************************************
	*
	* Summary:
	*  Disables interrupt signal generation by the status register
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	void  PDM_CIC_DisableInterruptGeneration()
	{
		PDM_CIC_Status_Reg_InterruptDisable();
	}

#endif /* (PDM_CIC_INTERRUPT_ENABLED) */

/*******************************************************************************
* Function Name: PDM_CIC_Integrator_Init
********************************************************************************
*
* Summary:
*  Initializes the integrator
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  None.
*
*
*******************************************************************************/
static void PDM_CIC_Integrator_Init(void)
{
	uint8 enableInterrupts;	
	
	enableInterrupts = CyEnterCriticalSection();
	
	#if(PDM_CIC_LEFT_CHANNEL_ENABLED)	
		/* Reset the F0, F1 FIFO buffer pointers and status signals */
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u0__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u1__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u2__DP_AUX_CTL_REG) | 0x03 );	
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u3__DP_AUX_CTL_REG) | 0x03 );	
		
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u0__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u1__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u2__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk2_dp32_l_u3__DP_AUX_CTL_REG) & 0xFC );	
	#endif /* (PDM_CIC_LEFT_CHANNEL_ENABLED) */
	
	#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
		/* Reset the F0, F1 FIFO buffer pointers and status signals */
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u0__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u1__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u2__DP_AUX_CTL_REG) | 0x03 );	
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u3__DP_AUX_CTL_REG) | 0x03 );	
		
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u0__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u1__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u2__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_genblk3_dp32_r_u3__DP_AUX_CTL_REG) & 0xFC );	
	#endif /* (PDM_CIC_RIGHT_CHANNEL_ENABLED) */
	
	/* Enable the decimator counter module */
	CY_SET_REG8(PDM_CIC_Integrator_Counter7__CONTROL_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Integrator_Counter7__CONTROL_AUX_CTL_REG) | 0x20);
	
	CyExitCriticalSection(enableInterrupts);	
	
}

/*******************************************************************************
* Function Name: PDM_CIC_Comb_Init
********************************************************************************
*
* Summary:
*  Initializes the comb
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  None.
*
*
*******************************************************************************/
static void PDM_CIC_Comb_Init(void)
{
	uint8 enableInterrupts;	
	
	enableInterrupts = CyEnterCriticalSection();
	
	#if(PDM_CIC_LEFT_CHANNEL_ENABLED)	
		/* Reset the F0, F1 FIFO buffer pointers and status signals */
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u0__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u1__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u2__DP_AUX_CTL_REG) | 0x03 );	
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u3__DP_AUX_CTL_REG) | 0x03 );	
		
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u0__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u1__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u2__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u3__DP_AUX_CTL_REG) & 0xFC );
	#endif /* (PDM_CIC_LEFT_CHANNEL_ENABLED) */
	
	#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)	
		/* Reset the F0, F1 FIFO buffer pointers and status signals */
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u0__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u1__DP_AUX_CTL_REG) | 0x03 );
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u2__DP_AUX_CTL_REG) | 0x03 );	
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u3__DP_AUX_CTL_REG) | 0x03 );	
		
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u0__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u0__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u1__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u1__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u2__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u2__DP_AUX_CTL_REG) & 0xFC );
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u3__DP_AUX_CTL_REG, CY_GET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u3__DP_AUX_CTL_REG) & 0xFC );		
	#endif /* (PDM_CIC_RIGHT_CHANNEL_ENABLED) */
	
	CyExitCriticalSection(enableInterrupts);
	
	#if(PDM_CIC_LEFT_CHANNEL_ENABLED)	
		/* Write 0 to the 32-bit D0 register */
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u0__D0_REG, 0x00);
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u1__D0_REG, 0x00);
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u2__D0_REG, 0x00);
		CY_SET_REG8(PDM_CIC_Comb_L_genblk2_dp32_u3__D0_REG, 0x00);	
	#endif /* (PDM_CIC_LEFT_CHANNEL_ENABLED) */
	
	#if(PDM_CIC_RIGHT_CHANNEL_ENABLED)
		/* Write 0 to the 32-bit D0 register */
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u0__D0_REG, 0x00);
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u1__D0_REG, 0x00);
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u2__D0_REG, 0x00);
		CY_SET_REG8(PDM_CIC_Comb_R_genblk2_dp32_u3__D0_REG, 0x00);	
	#endif /* (PDM_CIC_RIGHT_CHANNEL_ENABLED) */

}

#if (PDM_CIC_RIGHT_CHANNEL_ENABLED)

	/*******************************************************************************
	* Function Name: PDM_CIC_IntOutDma_R_Init
	********************************************************************************
	*
	* Summary:
	*  Initializes the DMA channel associated with the right channel integrator output
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_IntOutDma_R_Init(void)
	{
		uint8 DMA_IntegratorOut_Channel, DMA_IntegratorOut_TD[2];

		/* Transfer data in 2-byte bursts since UDB spoke is 2 bytes wide.
		   requestPerBurst = 1.
		   Peripheral (UDB) to Peripheral (UDB) transfer */
		DMA_IntegratorOut_Channel = PDM_CIC_DMA_IntOut_R_DmaInitialize(2, 1, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));	
		
		DMA_IntegratorOut_TD[0] = CyDmaTdAllocate();
		DMA_IntegratorOut_TD[1] = CyDmaTdAllocate();
		
		/* Circular TD's. Each TD transfer 2 bytes. Auto execute second TD. */
		CyDmaTdSetConfiguration(DMA_IntegratorOut_TD[0], 2, DMA_IntegratorOut_TD[1], TD_AUTO_EXEC_NEXT); 
		CyDmaTdSetConfiguration(DMA_IntegratorOut_TD[1], 2, DMA_IntegratorOut_TD[0], PDM_CIC_DMA_IntOut_R__TD_TERMOUT_EN);
		
		/* Each TD transfers 16-bit FIFO value to 16-bit A0. Order TD's such that MSB datapath FIFO is read last whose status triggers the DMA */
		CyDmaTdSetAddress(DMA_IntegratorOut_TD[0], (uint16)(PDM_CIC_INT_R_LO16_OUTPUT_REG_PTR), (uint16)(PDM_CIC_COMB_R_LO16_INPUT_REG_PTR));
		CyDmaTdSetAddress(DMA_IntegratorOut_TD[1], (uint16)(PDM_CIC_INT_R_HI16_OUTPUT_REG_PTR), (uint16)(PDM_CIC_COMB_R_HI16_INPUT_REG_PTR));
		
		/* Set the initial TD for the channel */
		CyDmaChSetInitialTd(DMA_IntegratorOut_Channel, DMA_IntegratorOut_TD[0]);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_IntOutDma_R_Start
	********************************************************************************
	*
	* Summary:
	*  Starts the DMA channel associated with the right channel integrator output
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_IntOutDma_R_Start(void)
	{	
		CyDmaClearPendingDrq(PDM_CIC_DMA_IntOut_R_DmaHandle);
		
		CyDmaChEnable(PDM_CIC_DMA_IntOut_R_DmaHandle, 1);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_IntOutDma_R_Stop
	********************************************************************************
	*
	* Summary:
	*  Stops (and disables) the DMA channel associated with the right channel integrator output
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_IntOutDma_R_Stop(void)
	{	
		/* Terminate the TD chain which also disables the channel */
		CyDmaChSetRequest(PDM_CIC_DMA_IntOut_R_DmaHandle , CPU_TERM_CHAIN);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_CombD0UpdateDma_R_Init
	********************************************************************************
	*
	* Summary:
	*  Initializes the DMA channel associated with the Comb D0 register update
	*  for right channel
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_CombD0UpdateDma_R_Init(void)
	{
		uint8 DMA_CombD0Update_Channel, DMA_CombD0Update_TD[2];

		/* Transfer data in 2-byte bursts since UDB spoke is 2 bytes wide.
			requestPerBurst = 1.
		   Peripheral (UDB) to Peripheral (UDB) transfer */
		DMA_CombD0Update_Channel = PDM_CIC_DMA_CombD0Update_R_DmaInitialize(2, 1, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));
		DMA_CombD0Update_TD[0] = CyDmaTdAllocate();
		DMA_CombD0Update_TD[1] = CyDmaTdAllocate();
		
		/* Circular TD's. Each TD transfer 2 bytes. Auto execute second TD. */
		CyDmaTdSetConfiguration(DMA_CombD0Update_TD[0], 2, DMA_CombD0Update_TD[1], TD_AUTO_EXEC_NEXT);
		CyDmaTdSetConfiguration(DMA_CombD0Update_TD[1], 2, DMA_CombD0Update_TD[0], PDM_CIC_DMA_CombD0Update_R__TD_TERMOUT_EN);
		
		/* Each TD transfers 16-bit A1 value to 16-bit D0. */
		CyDmaTdSetAddress(DMA_CombD0Update_TD[0], (uint16)PDM_CIC_Comb_R_genblk2_dp32_u0__16BIT_A1_REG, (uint16)PDM_CIC_Comb_R_genblk2_dp32_u0__16BIT_D0_REG);
		CyDmaTdSetAddress(DMA_CombD0Update_TD[1], (uint16)PDM_CIC_Comb_R_genblk2_dp32_u2__16BIT_A1_REG, (uint16)PDM_CIC_Comb_R_genblk2_dp32_u2__16BIT_D0_REG);
		
		/* Set the initial TD for the channel */
		CyDmaChSetInitialTd(DMA_CombD0Update_Channel, DMA_CombD0Update_TD[0]);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_CombD0UpdateDma_R_Start
	********************************************************************************
	*
	* Summary:
	*  Starts the DMA channel associated with the Comb D0 register update for right
	*  channel
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_CombD0UpdateDma_R_Start(void)
	{	
		CyDmaClearPendingDrq(PDM_CIC_DMA_CombD0Update_R_DmaHandle);	
		CyDmaChEnable(PDM_CIC_DMA_CombD0Update_R_DmaHandle, 1);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_CombD0UpdateDma_R_Stop
	********************************************************************************
	*
	* Summary:
	*  Stops (and disables) the DMA channel associated with the Comb D0 register update
	*  for the right channel
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_CombD0UpdateDma_R_Stop(void)
	{	
		/* Terminate the TD chain which also disables the channel */
		CyDmaChSetRequest(PDM_CIC_DMA_CombD0Update_R_DmaHandle , CPU_TERM_CHAIN);
	}
#endif /* (PDM_CIC_RIGHT_CHANNEL_ENABLED) */

#if (PDM_CIC_LEFT_CHANNEL_ENABLED)
	/*******************************************************************************
	* Function Name: PDM_CIC_IntOutDma_L_Init
	********************************************************************************
	*
	* Summary:
	*  Initializes the DMA channel associated with the left channel integrator output
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_IntOutDma_L_Init(void)
	{
		uint8 DMA_IntegratorOut_Channel, DMA_IntegratorOut_TD[2];

		/* Transfer data in 2-byte bursts since UDB spoke is 2 bytes wide.
		   requestPerBurst = 1.
		   Peripheral (UDB) to Peripheral (UDB) transfer */
		DMA_IntegratorOut_Channel = PDM_CIC_DMA_IntOut_L_DmaInitialize(2, 1, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));	
		
		DMA_IntegratorOut_TD[0] = CyDmaTdAllocate();
		DMA_IntegratorOut_TD[1] = CyDmaTdAllocate();
		
		/* Circular TD's. Each TD transfer 2 bytes. Auto execute second TD. */
		CyDmaTdSetConfiguration(DMA_IntegratorOut_TD[0], 2, DMA_IntegratorOut_TD[1], TD_AUTO_EXEC_NEXT); 
		CyDmaTdSetConfiguration(DMA_IntegratorOut_TD[1], 2, DMA_IntegratorOut_TD[0], PDM_CIC_DMA_IntOut_L__TD_TERMOUT_EN);
		
		/* Each TD transfers 16-bit FIFO value to 16-bit A0. Order TD's such that MSB datapath FIFO is read last whose status triggers the DMA */
		CyDmaTdSetAddress(DMA_IntegratorOut_TD[0], (uint16)(PDM_CIC_INT_L_LO16_OUTPUT_REG_PTR), (uint16)(PDM_CIC_COMB_L_LO16_INPUT_REG_PTR));
		CyDmaTdSetAddress(DMA_IntegratorOut_TD[1], (uint16)(PDM_CIC_INT_L_HI16_OUTPUT_REG_PTR), (uint16)(PDM_CIC_COMB_L_HI16_INPUT_REG_PTR));
		
		/* Set the initial TD for the channel */
		CyDmaChSetInitialTd(DMA_IntegratorOut_Channel, DMA_IntegratorOut_TD[0]);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_IntOutDma_L_Start
	********************************************************************************
	*
	* Summary:
	*  Starts the DMA channel associated with the left channel integrator output
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_IntOutDma_L_Start(void)
	{	
		CyDmaClearPendingDrq(PDM_CIC_DMA_IntOut_L_DmaHandle);
		
		CyDmaChEnable(PDM_CIC_DMA_IntOut_L_DmaHandle, 1);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_IntOutDma_L_Stop
	********************************************************************************
	*
	* Summary:
	*  Stops (and disables) the DMA channel associated with the left channel integrator output
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_IntOutDma_L_Stop(void)
	{	
		/* Terminate the TD chain which also disables the channel */
		CyDmaChSetRequest(PDM_CIC_DMA_IntOut_L_DmaHandle , CPU_TERM_CHAIN);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_CombD0UpdateDma_L_Init
	********************************************************************************
	*
	* Summary:
	*  Initializes the DMA channel associated with the Comb D0 register update
	*  for left channel
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_CombD0UpdateDma_L_Init(void)
	{
		uint8 DMA_CombD0Update_Channel, DMA_CombD0Update_TD[2];

		/* Transfer data in 2-byte bursts since UDB spoke is 2 bytes wide.
			requestPerBurst = 1.
		   Peripheral (UDB) to Peripheral (UDB) transfer */
		DMA_CombD0Update_Channel = PDM_CIC_DMA_CombD0Update_L_DmaInitialize(2, 1, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));
		DMA_CombD0Update_TD[0] = CyDmaTdAllocate();
		DMA_CombD0Update_TD[1] = CyDmaTdAllocate();
		
		/* Circular TD's. Each TD transfer 2 bytes. Auto execute second TD. */
		CyDmaTdSetConfiguration(DMA_CombD0Update_TD[0], 2, DMA_CombD0Update_TD[1], TD_AUTO_EXEC_NEXT);
		CyDmaTdSetConfiguration(DMA_CombD0Update_TD[1], 2, DMA_CombD0Update_TD[0], PDM_CIC_DMA_CombD0Update_L__TD_TERMOUT_EN);
		
		/* Each TD transfers 16-bit A1 value to 16-bit D0. */
		CyDmaTdSetAddress(DMA_CombD0Update_TD[0], (uint16)PDM_CIC_Comb_L_genblk2_dp32_u0__16BIT_A1_REG, (uint16)PDM_CIC_Comb_L_genblk2_dp32_u0__16BIT_D0_REG);
		CyDmaTdSetAddress(DMA_CombD0Update_TD[1], (uint16)PDM_CIC_Comb_L_genblk2_dp32_u2__16BIT_A1_REG, (uint16)PDM_CIC_Comb_L_genblk2_dp32_u2__16BIT_D0_REG);
		
		/* Set the initial TD for the channel */
		CyDmaChSetInitialTd(DMA_CombD0Update_Channel, DMA_CombD0Update_TD[0]);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_CombD0UpdateDma_L_Start
	********************************************************************************
	*
	* Summary:
	*  Starts the DMA channel associated with the Comb D0 register update for left
	*  channel
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_CombD0UpdateDma_L_Start(void)
	{	
		CyDmaClearPendingDrq(PDM_CIC_DMA_CombD0Update_L_DmaHandle);	
		CyDmaChEnable(PDM_CIC_DMA_CombD0Update_L_DmaHandle, 1);
	}

	/*******************************************************************************
	* Function Name: PDM_CIC_CombD0UpdateDma_L_Stop
	********************************************************************************
	*
	* Summary:
	*  Stops (and disables) the DMA channel associated with the Comb D0 register update
	*  for the left channel
	*
	* Parameters:
	*  None.
	*
	* Return:
	*  None.
	*
	* Global Variables:
	*  None.
	*
	*
	*******************************************************************************/
	static void PDM_CIC_CombD0UpdateDma_L_Stop(void)
	{	
		/* Terminate the TD chain which also disables the channel */
		CyDmaChSetRequest(PDM_CIC_DMA_CombD0Update_L_DmaHandle , CPU_TERM_CHAIN);
	}
#endif /* (PDM_CIC_LEFT_CHANNEL_ENABLED) */


/* [] END OF FILE */
