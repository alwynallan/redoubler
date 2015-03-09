/*******************************************************************************
* File Name: AudioClkGen_Clock_I2S.h
* Version 2.0
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

#if !defined(CY_CLOCK_AudioClkGen_Clock_I2S_H)
#define CY_CLOCK_AudioClkGen_Clock_I2S_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void AudioClkGen_Clock_I2S_Start(void) ;
void AudioClkGen_Clock_I2S_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void AudioClkGen_Clock_I2S_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void AudioClkGen_Clock_I2S_StandbyPower(uint8 state) ;
void AudioClkGen_Clock_I2S_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 AudioClkGen_Clock_I2S_GetDividerRegister(void) ;
void AudioClkGen_Clock_I2S_SetModeRegister(uint8 modeBitMask) ;
void AudioClkGen_Clock_I2S_ClearModeRegister(uint8 modeBitMask) ;
uint8 AudioClkGen_Clock_I2S_GetModeRegister(void) ;
void AudioClkGen_Clock_I2S_SetSourceRegister(uint8 clkSource) ;
uint8 AudioClkGen_Clock_I2S_GetSourceRegister(void) ;
#if defined(AudioClkGen_Clock_I2S__CFG3)
void AudioClkGen_Clock_I2S_SetPhaseRegister(uint8 clkPhase) ;
uint8 AudioClkGen_Clock_I2S_GetPhaseRegister(void) ;
#endif /* defined(AudioClkGen_Clock_I2S__CFG3) */

#define AudioClkGen_Clock_I2S_Enable()                       AudioClkGen_Clock_I2S_Start()
#define AudioClkGen_Clock_I2S_Disable()                      AudioClkGen_Clock_I2S_Stop()
#define AudioClkGen_Clock_I2S_SetDivider(clkDivider)         AudioClkGen_Clock_I2S_SetDividerRegister(clkDivider, 1)
#define AudioClkGen_Clock_I2S_SetDividerValue(clkDivider)    AudioClkGen_Clock_I2S_SetDividerRegister((clkDivider) - 1, 1)
#define AudioClkGen_Clock_I2S_SetMode(clkMode)               AudioClkGen_Clock_I2S_SetModeRegister(clkMode)
#define AudioClkGen_Clock_I2S_SetSource(clkSource)           AudioClkGen_Clock_I2S_SetSourceRegister(clkSource)
#if defined(AudioClkGen_Clock_I2S__CFG3)
#define AudioClkGen_Clock_I2S_SetPhase(clkPhase)             AudioClkGen_Clock_I2S_SetPhaseRegister(clkPhase)
#define AudioClkGen_Clock_I2S_SetPhaseValue(clkPhase)        AudioClkGen_Clock_I2S_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(AudioClkGen_Clock_I2S__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define AudioClkGen_Clock_I2S_CLKEN              (* (reg8 *) AudioClkGen_Clock_I2S__PM_ACT_CFG)
#define AudioClkGen_Clock_I2S_CLKEN_PTR          ((reg8 *) AudioClkGen_Clock_I2S__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define AudioClkGen_Clock_I2S_CLKSTBY            (* (reg8 *) AudioClkGen_Clock_I2S__PM_STBY_CFG)
#define AudioClkGen_Clock_I2S_CLKSTBY_PTR        ((reg8 *) AudioClkGen_Clock_I2S__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define AudioClkGen_Clock_I2S_DIV_LSB            (* (reg8 *) AudioClkGen_Clock_I2S__CFG0)
#define AudioClkGen_Clock_I2S_DIV_LSB_PTR        ((reg8 *) AudioClkGen_Clock_I2S__CFG0)
#define AudioClkGen_Clock_I2S_DIV_PTR            ((reg16 *) AudioClkGen_Clock_I2S__CFG0)

/* Clock MSB divider configuration register. */
#define AudioClkGen_Clock_I2S_DIV_MSB            (* (reg8 *) AudioClkGen_Clock_I2S__CFG1)
#define AudioClkGen_Clock_I2S_DIV_MSB_PTR        ((reg8 *) AudioClkGen_Clock_I2S__CFG1)

/* Mode and source configuration register */
#define AudioClkGen_Clock_I2S_MOD_SRC            (* (reg8 *) AudioClkGen_Clock_I2S__CFG2)
#define AudioClkGen_Clock_I2S_MOD_SRC_PTR        ((reg8 *) AudioClkGen_Clock_I2S__CFG2)

#if defined(AudioClkGen_Clock_I2S__CFG3)
/* Analog clock phase configuration register */
#define AudioClkGen_Clock_I2S_PHASE              (* (reg8 *) AudioClkGen_Clock_I2S__CFG3)
#define AudioClkGen_Clock_I2S_PHASE_PTR          ((reg8 *) AudioClkGen_Clock_I2S__CFG3)
#endif /* defined(AudioClkGen_Clock_I2S__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define AudioClkGen_Clock_I2S_CLKEN_MASK         AudioClkGen_Clock_I2S__PM_ACT_MSK
#define AudioClkGen_Clock_I2S_CLKSTBY_MASK       AudioClkGen_Clock_I2S__PM_STBY_MSK

/* CFG2 field masks */
#define AudioClkGen_Clock_I2S_SRC_SEL_MSK        AudioClkGen_Clock_I2S__CFG2_SRC_SEL_MASK
#define AudioClkGen_Clock_I2S_MODE_MASK          (~(AudioClkGen_Clock_I2S_SRC_SEL_MSK))

#if defined(AudioClkGen_Clock_I2S__CFG3)
/* CFG3 phase mask */
#define AudioClkGen_Clock_I2S_PHASE_MASK         AudioClkGen_Clock_I2S__CFG3_PHASE_DLY_MASK
#endif /* defined(AudioClkGen_Clock_I2S__CFG3) */

#endif /* CY_CLOCK_AudioClkGen_Clock_I2S_H */


/* [] END OF FILE */
