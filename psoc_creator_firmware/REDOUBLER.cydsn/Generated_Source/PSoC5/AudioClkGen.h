/*******************************************************************************
* File Name: AudioClkGen.h
* Version 0.83 - works with I2S v2_4
*
* Description:
*  This file contains API to enable firmware control of divider settings and audio clock generation.
*
* Note: Only includes support for digital audio.
*
********************************************************************************
* Copyright 2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

#if !defined(CY_AUDIOCLKGEN_AudioClkGen_H)
#define CY_CY_AUDIOCLKGEN_AudioClkGen_H

#define AudioClkGen_RATE_48KHZ 0
#define AudioClkGen_RATE_44KHZ 1
#define AudioClkGen_RATE_32KHZ 2
#define AudioClkGen_RATE_16KHZ 3
#define AudioClkGen_RATE_8KHZ  4
#define AudioClkGen_RATE_11KHZ 5
#define AudioClkGen_RATE_22KHZ 6
#define AudioClkGen_RATE_96KHZ 7

/***************************************
* Conditional Compilation Parameters
***************************************/
#define AudioClkGen_Enable_Mclk 1
#define AudioClkGen_Enable_I2Sclk 1

/***********************************
* Function Porotypes
***********************************/

/*******************************************************************************
* Function Name: AudioClkGen_Start
********************************************************************************
* Summary:
*  The start function initializes the fractional divider with the default values.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void AudioClkGen_Start(void);

/*******************************************************************************
* Function Name: AudioClkGen_Stop
********************************************************************************
* Summary:
*  The stop function halts the fractional divider.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void AudioClkGen_Stop(void);

/*******************************************************************************
* Function Name: AudioClkGen_SetDividerAudioRate
********************************************************************************
* Summary:
*  This function is used to setup all the required internal values for 
*  to generate common audio sample rate clocks from a 24 MHz input
*
* Parameters:  
*  rate: Desired audio sample rate to be fed to PLL.  
*  		 Must be one of the following:
*		AudioClkGen_RATE_8KHZ
*		AudioClkGen_RATE_11KHZ
*		AudioClkGen_RATE_16KHZ
*		AudioClkGen_RATE_22KHZ
*		AudioClkGen_RATE_32KHZ
*		AudioClkGen_RATE_44KHZ
* 		AudioClkGen_RATE_48KHZ
* 		AudioClkGen_RATE_96KHZ
*
* Return: 
*  void
*
*******************************************************************************/
void AudioClkGen_SetAudioRate(uint8 rate) ;

#endif /* CY_CY_AUDIOCLKGEN_AudioClkGen_H */

//[] END OF FILE

