/*******************************************************************************
* File Name: Configuration.h
*
* Version 1.0
*
*  Description: Configuration.h provides various configuration options for user 
*               to enable/disable and control different features provided by firmware 
*
********************************************************************************
* Copyright (2008-2013), Cypress Semiconductor Corporation.
********************************************************************************
* This software is  by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CONFIGURATION_H)
#define CONFIGURATION_H
#include <cytypes.h>
#include <project.h>

/* Compiler directives for enabling different firmware features */

//#define CODEC_I2C_SUPPORTED		    /* Uncommenting this macro enables I2C configuration code for codecs that support I2C */
									/* interface for configurations such as volume control  */

/* Enable Volume update only when codec I2C is supported */
#ifdef CODEC_I2C_SUPPORTED			
	#define ENABLE_VOLUME_CONTROL     /* Volume control through USB enabled */
#endif

#define ENABLE_WATCHDOG          /* Enable watchdog for recovering from system faults */

/* Some of the codecs requires audio master clock (MCLK) to be always ON (even when audio streaming is inactive).
 * Uncomment MCLK_ALWAYS_ENABLED directive to support such a codec/design. */
//#define MCLK_ALWAYS_ENABLED 

/* In USB bus powered mode, uncomment HANDLE_USB_SUSPEND directive to support USB suspend and wakeup features */
#define HANDLE_USB_SUSPEND    

/* Enable ENABLE_DIGITAL_AUDIO_OUT_ONLY directive when audio out stream alone is supported (Speaker docks for example).
 * Enabling ENABLE_DIGITAL_AUDIO_OUT_ONLY disables all the code related to audio in stream handling.
 * If you wish to support both audio in and out streams, then comment out both "ENABLE_DIGITAL_AUDIO_OUT_ONLY" and 
 * "ENABLE_DIGITAL_AUDIO_IN_ONLY" directives. */
//#define ENABLE_DIGITAL_AUDIO_OUT_ONLY  /* USBFS_OUT_ONLY component must be used when this macro is enabled */

/* Enable ENABLE_DIGITAL_AUDIO_IN_ONLY directive when audio in stream alone is supported (Microphone design for example).
 * Enabling ENABLE_DIGITAL_AUDIO_IN_ONLY disables all the code related to audio out stream handling.
 * If you wish to support both audio in and out streams, then comment out both "ENABLE_DIGITAL_AUDIO_OUT_ONLY" and 
 * "ENABLE_DIGITAL_AUDIO_IN_ONLY" directives. */
#define ENABLE_DIGITAL_AUDIO_IN_ONLY  /* USBFS_IN_ONLY component must be used when this macro is enabled */


/* PDM Microphone related macros - START (These macros are for debugging purpose) */
#define ENABLE_PDM					/* Enables the PDM microphone code*/
//#define DISABLE_DFB				/* Uncomment this macro if Droop filter compensation feature is not needed */
/* PDM Microphone macros - END*/

#endif

/* [] END OF FILE */
