/*******************************************************************************
* File Name: AudioClkGen_Ref.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_AudioClkGen_Ref_H)
#define CY_CLOCK_AudioClkGen_Ref_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void AudioClkGen_Ref_Start(void) ;
void AudioClkGen_Ref_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void AudioClkGen_Ref_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void AudioClkGen_Ref_StandbyPower(uint8 state) ;
void AudioClkGen_Ref_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 AudioClkGen_Ref_GetDividerRegister(void) ;
void AudioClkGen_Ref_SetModeRegister(uint8 modeBitMask) ;
void AudioClkGen_Ref_ClearModeRegister(uint8 modeBitMask) ;
uint8 AudioClkGen_Ref_GetModeRegister(void) ;
void AudioClkGen_Ref_SetSourceRegister(uint8 clkSource) ;
uint8 AudioClkGen_Ref_GetSourceRegister(void) ;
#if defined(AudioClkGen_Ref__CFG3)
void AudioClkGen_Ref_SetPhaseRegister(uint8 clkPhase) ;
uint8 AudioClkGen_Ref_GetPhaseRegister(void) ;
#endif /* defined(AudioClkGen_Ref__CFG3) */

#define AudioClkGen_Ref_Enable()                       AudioClkGen_Ref_Start()
#define AudioClkGen_Ref_Disable()                      AudioClkGen_Ref_Stop()
#define AudioClkGen_Ref_SetDivider(clkDivider)         AudioClkGen_Ref_SetDividerRegister(clkDivider, 1u)
#define AudioClkGen_Ref_SetDividerValue(clkDivider)    AudioClkGen_Ref_SetDividerRegister((clkDivider) - 1u, 1u)
#define AudioClkGen_Ref_SetMode(clkMode)               AudioClkGen_Ref_SetModeRegister(clkMode)
#define AudioClkGen_Ref_SetSource(clkSource)           AudioClkGen_Ref_SetSourceRegister(clkSource)
#if defined(AudioClkGen_Ref__CFG3)
#define AudioClkGen_Ref_SetPhase(clkPhase)             AudioClkGen_Ref_SetPhaseRegister(clkPhase)
#define AudioClkGen_Ref_SetPhaseValue(clkPhase)        AudioClkGen_Ref_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(AudioClkGen_Ref__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define AudioClkGen_Ref_CLKEN              (* (reg8 *) AudioClkGen_Ref__PM_ACT_CFG)
#define AudioClkGen_Ref_CLKEN_PTR          ((reg8 *) AudioClkGen_Ref__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define AudioClkGen_Ref_CLKSTBY            (* (reg8 *) AudioClkGen_Ref__PM_STBY_CFG)
#define AudioClkGen_Ref_CLKSTBY_PTR        ((reg8 *) AudioClkGen_Ref__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define AudioClkGen_Ref_DIV_LSB            (* (reg8 *) AudioClkGen_Ref__CFG0)
#define AudioClkGen_Ref_DIV_LSB_PTR        ((reg8 *) AudioClkGen_Ref__CFG0)
#define AudioClkGen_Ref_DIV_PTR            ((reg16 *) AudioClkGen_Ref__CFG0)

/* Clock MSB divider configuration register. */
#define AudioClkGen_Ref_DIV_MSB            (* (reg8 *) AudioClkGen_Ref__CFG1)
#define AudioClkGen_Ref_DIV_MSB_PTR        ((reg8 *) AudioClkGen_Ref__CFG1)

/* Mode and source configuration register */
#define AudioClkGen_Ref_MOD_SRC            (* (reg8 *) AudioClkGen_Ref__CFG2)
#define AudioClkGen_Ref_MOD_SRC_PTR        ((reg8 *) AudioClkGen_Ref__CFG2)

#if defined(AudioClkGen_Ref__CFG3)
/* Analog clock phase configuration register */
#define AudioClkGen_Ref_PHASE              (* (reg8 *) AudioClkGen_Ref__CFG3)
#define AudioClkGen_Ref_PHASE_PTR          ((reg8 *) AudioClkGen_Ref__CFG3)
#endif /* defined(AudioClkGen_Ref__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define AudioClkGen_Ref_CLKEN_MASK         AudioClkGen_Ref__PM_ACT_MSK
#define AudioClkGen_Ref_CLKSTBY_MASK       AudioClkGen_Ref__PM_STBY_MSK

/* CFG2 field masks */
#define AudioClkGen_Ref_SRC_SEL_MSK        AudioClkGen_Ref__CFG2_SRC_SEL_MASK
#define AudioClkGen_Ref_MODE_MASK          (~(AudioClkGen_Ref_SRC_SEL_MSK))

#if defined(AudioClkGen_Ref__CFG3)
/* CFG3 phase mask */
#define AudioClkGen_Ref_PHASE_MASK         AudioClkGen_Ref__CFG3_PHASE_DLY_MASK
#endif /* defined(AudioClkGen_Ref__CFG3) */

#endif /* CY_CLOCK_AudioClkGen_Ref_H */


/* [] END OF FILE */
