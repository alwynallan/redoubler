/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
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

#if !defined(CY_AUDIOCLKGEN_`$INSTANCE_NAME`_H)
#define CY_CY_AUDIOCLKGEN_`$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_RATE_48KHZ 0
#define `$INSTANCE_NAME`_RATE_44KHZ 1
#define `$INSTANCE_NAME`_RATE_32KHZ 2
#define `$INSTANCE_NAME`_RATE_16KHZ 3
#define `$INSTANCE_NAME`_RATE_8KHZ  4
#define `$INSTANCE_NAME`_RATE_11KHZ 5
#define `$INSTANCE_NAME`_RATE_22KHZ 6
#define `$INSTANCE_NAME`_RATE_96KHZ 7

/***************************************
* Conditional Compilation Parameters
***************************************/
#define `$INSTANCE_NAME`_Enable_Mclk `$Enable_Mclk`
#define `$INSTANCE_NAME`_Enable_I2Sclk `$Enable_I2Sclk`

/***********************************
* Function Porotypes
***********************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
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
void `$INSTANCE_NAME`_Start(void);

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
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
void `$INSTANCE_NAME`_Stop(void);

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDividerAudioRate
********************************************************************************
* Summary:
*  This function is used to setup all the required internal values for 
*  to generate common audio sample rate clocks from a 24 MHz input
*
* Parameters:  
*  rate: Desired audio sample rate to be fed to PLL.  
*  		 Must be one of the following:
*		`$INSTANCE_NAME`_RATE_8KHZ
*		`$INSTANCE_NAME`_RATE_11KHZ
*		`$INSTANCE_NAME`_RATE_16KHZ
*		`$INSTANCE_NAME`_RATE_22KHZ
*		`$INSTANCE_NAME`_RATE_32KHZ
*		`$INSTANCE_NAME`_RATE_44KHZ
* 		`$INSTANCE_NAME`_RATE_48KHZ
* 		`$INSTANCE_NAME`_RATE_96KHZ
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAudioRate(uint8 rate) `=ReentrantKeil("`$INSTANCE_NAME`_SetAudioRate")`;

#endif /* CY_CY_AUDIOCLKGEN_`$INSTANCE_NAME`_H */

//[] END OF FILE

