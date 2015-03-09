/*******************************************************************************
* File Name: Sample_Hold_3.c
* Version 1.40
*
* Description:
*  This file provides the source code to the API for the SAMPLE/TRACK AND HOLD 
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Sample_Hold_3.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

uint8 Sample_Hold_3_initVar = 0u;

/* static Sample_Hold_3_backupStruct  Sample_Hold_3_backup; */
#if (CY_PSOC5A)
    static Sample_Hold_3_backupStruct  Sample_Hold_3_P5backup;
#endif /* CY_PSOC5A */



/*******************************************************************************   
* Function Name: Sample_Hold_3_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Sample_Hold_3_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Sample_Hold_3_Init(void) 
{   
    /* Configure SC Block based on selected Sample/Track type */
    #if (Sample_Hold_3_SAMPLE_TRACK_MODE == Sample_Hold_3_SAMPLEANDHOLD) /* Sample and hold mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Sample_Hold_3_CR0_REG = Sample_Hold_3_MODE_SAMPLEANDHOLD;
        
        /* SC Block CR1 */ 
        Sample_Hold_3_CR1_REG = (Sample_Hold_3_COMP_4P35PF  |
                                Sample_Hold_3_GAIN_0DB);
        #if(Sample_Hold_3_SAMPLE_CLOCK_EDGE == Sample_Hold_3_EDGE_POSITIVENEGATIVE)
            Sample_Hold_3_CR1_REG =  Sample_Hold_3_CR1_REG  | Sample_Hold_3_DIV2_DISABLE ;
        #else
            Sample_Hold_3_CR1_REG =  Sample_Hold_3_CR1_REG  | Sample_Hold_3_DIV2_ENABLE ;
        #endif
         
        #if(Sample_Hold_3_VREF_TYPE == Sample_Hold_3_EXTERNAL)
            Sample_Hold_3_CR2_REG = Sample_Hold_3_BIAS_LOW |
                                       Sample_Hold_3_REDC_00 | 
                                       Sample_Hold_3_GNDVREF_DI;
        #else
            Sample_Hold_3_CR2_REG = Sample_Hold_3_BIAS_LOW |
                                       Sample_Hold_3_REDC_00 | 
                                       Sample_Hold_3_GNDVREF_E;
        #endif
    #else
        /* Track and Hold Mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Sample_Hold_3_CR0_REG = Sample_Hold_3_MODE_TRACKANDHOLD; 
        
        /* SC Block CR1 */ 
        Sample_Hold_3_CR1_REG = Sample_Hold_3_COMP_4P35PF  |
                                   Sample_Hold_3_DIV2_ENABLE |
                                   Sample_Hold_3_GAIN_0DB;
                                
        /* SC Block CR2 */
        Sample_Hold_3_CR2_REG = Sample_Hold_3_BIAS_LOW |
                                   Sample_Hold_3_REDC_00 |
                                   Sample_Hold_3_GNDVREF_E;
    #endif /* end if - Sample/Track Type */
    
    /* Enable SC Block clocking */
    Sample_Hold_3_CLK_REG |= Sample_Hold_3_CLK_EN;
    
    /* Set default power */
    Sample_Hold_3_SetPower(Sample_Hold_3_INIT_POWER);
}


/*******************************************************************************   
* Function Name: Sample_Hold_3_Enable
********************************************************************************
*
* Summary:
*  Enables the Sample/Track and Hold block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Sample_Hold_3_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(Sample_Hold_3_P5backup.enableState == 1u)
        {
            Sample_Hold_3_CR1_REG = Sample_Hold_3_P5backup.scCR1Reg;
            Sample_Hold_3_CR2_REG = Sample_Hold_3_P5backup.scCR2Reg;
            Sample_Hold_3_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    Sample_Hold_3_PM_ACT_CFG_REG |= Sample_Hold_3_ACT_PWR_EN;
    
    /* Enable power to SC block in Alternative active mode */
    Sample_Hold_3_PM_STBY_CFG_REG |= Sample_Hold_3_STBY_PWR_EN;

    Sample_Hold_3_PUMP_CR1_REG |= Sample_Hold_3_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                Sample_Hold_3_BSTCLK_REG &= (uint8)(~Sample_Hold_3_BST_CLK_INDEX_MASK);
                Sample_Hold_3_BSTCLK_REG |= Sample_Hold_3_BST_CLK_EN | CyScBoostClk__INDEX;
                Sample_Hold_3_SC_MISC_REG |= Sample_Hold_3_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                Sample_Hold_3_BSTCLK_REG &= (uint8)(~Sample_Hold_3_BST_CLK_EN);
                Sample_Hold_3_SC_MISC_REG &= (uint8)(~Sample_Hold_3_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: Sample_Hold_3_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Sample and Hold with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Sample_Hold_3_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Sample_Hold_3_initVar == 0u)
    {
        Sample_Hold_3_Init();
        Sample_Hold_3_initVar = 1u;
    }
    Sample_Hold_3_Enable();
}


/*******************************************************************************
* Function Name: Sample_Hold_3_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Sample_Hold_3_Stop(void) 
{   
    /* Disble power to the Amp in Active mode template */
    Sample_Hold_3_PM_ACT_CFG_REG &= (uint8)(~Sample_Hold_3_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    Sample_Hold_3_PM_STBY_CFG_REG &= (uint8)(~Sample_Hold_3_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            Sample_Hold_3_BSTCLK_REG &= (uint8)(~Sample_Hold_3_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((Sample_Hold_3_PM_ACT_CFG_REG & Sample_Hold_3_PM_ACT_CFG_MASK) == 0u)
            {
                Sample_Hold_3_SC_MISC_REG &= (uint8)(~Sample_Hold_3_PUMP_FORCE);
                Sample_Hold_3_PUMP_CR1_REG &= (uint8)(~Sample_Hold_3_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
 
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        Sample_Hold_3_P5backup.scCR1Reg = Sample_Hold_3_CR1_REG;
        Sample_Hold_3_P5backup.scCR2Reg = Sample_Hold_3_CR2_REG;
        Sample_Hold_3_CR1_REG = 0x00u;
        Sample_Hold_3_CR2_REG = 0x00u;
        Sample_Hold_3_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Sample_Hold_3_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the Sample/Track and Hold.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void Sample_Hold_3_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */
    tmpCR = Sample_Hold_3_CR1_REG & (uint8)(~Sample_Hold_3_DRIVE_MASK);
    tmpCR |= (power & Sample_Hold_3_DRIVE_MASK);
    Sample_Hold_3_CR1_REG = tmpCR;
}


/* [] END OF FILE */
