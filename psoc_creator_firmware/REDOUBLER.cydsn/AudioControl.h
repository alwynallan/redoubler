/*******************************************************************************
* File Name: AudioControl.h
*
* Version 1.0
*
*  Description:  This file contains the Audio signal path configuration routine
*                declarations and constants.
*
********************************************************************************
* Copyright (2008-2013), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
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

#if !defined(AUDIOCONTROL_H)
#define AUDIOCONTROL_H
#include <Configuration.h>
#include <cytypes.h>
#include <USBFS.h>

/* Constants and routines for PDM design */
#define FILTER_SOURCE_REG_POINTER                    Droop_Filter_HOLDA_PTR
#define DIVIDER_32K_SR                               2 /* For 32k SR, PDM clock = PLL/3 */			
#define DIVIDER_44K_48K_SR                           1 /* For 44 and 48k SR, PDM clock = PLL/2 */	

/* Droop_Filter state retention API fix definitions */
#define Droop_Filter_CUSTOM_ENABLED               (0x01u)
#define Droop_Filter_CUSTOM_DISABLED              (0x00u)
#define Droop_Filter_CUSTOM_RUN_MASK              (0x01u)

/* Droop_Filter state retention structure */
typedef struct _Droop_Filter_Custom_backupStruct 
{
    uint8 enableState;
    uint8 cr;
    uint8 sr;
    uint8 sema;
}   Droop_Filter_Custom_BACKUP_STRUCT;

void CICOutDMA_ConfigAndStart(void);
/* End of constants and routines for PDM design */


#define I2S_PIN_DRIVE_MODE_CHANGE_IN_IDLE_MODE /* Comment this line if drive mode change for I2S pins in idle mode is 
                                                * not required */

#if(USBFS_EP_MM != USBFS__EP_DMAAUTO) 
#define NUM_TDS 8
#define OUT_TRANS_SIZE 96
#define OUT_BUFSIZE (OUT_TRANS_SIZE*NUM_TDS)
#define OUT_HALF (OUT_BUFSIZE/2)
#define IN_TRANS_SIZE 96
#define IN_BUFSIZE (IN_TRANS_SIZE*NUM_TDS)
#define IN_HALF (IN_BUFSIZE/2)
#else
#define NUM_TDS 8
#define OUT_TRANS_SIZE 144
#define OUT_BUFSIZE (OUT_TRANS_SIZE*NUM_TDS)
#define OUT_HALF (OUT_BUFSIZE/2)
#define IN_TRANS_SIZE 96
#define IN_BUFSIZE (IN_TRANS_SIZE*NUM_TDS)
#define IN_HALF (IN_BUFSIZE/2)
#endif

#define IN_AUDIOMAXPKT  (IN_BUFSIZE/4)
#define OUT_AUDIOMAXPKT (OUT_BUFSIZE/4)
#define CIC_OUT_BUFSIZE	960
/* Clock Rates */
#define RATE_48KHZ                                   AudioClkGen_RATE_48KHZ
#define RATE_44KHZ                                   AudioClkGen_RATE_44KHZ

#define BUS_CLOCK_DIVIDE_BY_8                        0x07
#define BUS_CLOCK_DIVIDE_BY_16                       0x0F
#define BUS_CLOCK_DIVIDE_BY_2                        0x01

#define ANALOG_AUX_INPUT                             0

#define SAMPLING_RATE_48KHZ                          48000
#define SAMPLING_RATE_44KHZ                          44100

#define EXTERNAL_CRYSTAL                             1
#define INTERNAL_IMO                                 0

#define FIFO_HALF_EMPTY_MASK                         0x0C

#define BLUETOOTH_TO_I2S_OUT                         0x03
#define FM_TO_I2S_OUT                                0x02
#define I2S_IN_TO_I2S_OUT                            0x01
#define I2S_OUT_TO_I2S_OUT                           0x00

#define DELAY_FREQ_PARAM_VALUE_PLL                   45000000
#define DELAY_FREQ_PARAM_VALUE_IMO                   24000000

#define IN_DMA_BURSTCOUNT                            0x02
#define DMA_BURSTCOUNT								 0x01
#define RQST_PER_BURST								 0x01
#define USBDMA_RQST_PER_BURST						 0x00

#define I2SDMA_TRANS_SIZE							 0x01
#define I2SDMA_CONFIG								 0x00

#define FREQUENCY_NOT_SET                            0xFF

#define MAC_WITH_MIDI_SUPPORT_USB_DEVICE_DESCRIPTOR  1


#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
	#ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
	#define IS_USB_AUDIO_INTERFACE_NOT_ACTIVE()            ( (0 == USBFS_interfaceSetting[1]) && (0 == USBFS_interfaceSetting[2]) )
	#else
	#define IS_USB_AUDIO_INTERFACE_NOT_ACTIVE()            (0 == USBFS_interfaceSetting[1])  
	#endif
#else
#define IS_USB_AUDIO_INTERFACE_NOT_ACTIVE()          (0 == USBFS_interfaceSetting[1])
#endif        

void ProcessAudioOut(void);
void ProcessAudioIn(void);
void SetClockRate(uint8 newRate) CYREENTRANT;
void Stop_PDM_InPath(void) CYREENTRANT;
void Stop_I2S_Tx(void) CYREENTRANT;
void HandleDigitalAudioLowPowerMode(void);
void HandleSamplingFrequencyChangeRequest(void);
void ConfigureAudioPath(void);
void StartAudioComponents(void);
void StopAudioComponents(void);
void UpdateAudioStatusUI(void);
void HandleSamplingFrequencyChangeInAuxMode(void);
void HandleAudioInBuffer(void);

/* Droop Filter modified PM APIs */
void Droop_Filter_ModifiedSleep(void);
void Droop_Filter_ModifiedWakeup(void);
void Droop_Filter_ModifiedSaveConfig(void);
void Droop_Filter_ModifiedRestoreConfig(void);
void Droop_Filter_ModifiedLoadReg32(reg32 regAddress[], const uint32 source[], uint8 count);
void Droop_Filter_ModifiedZeroReg32(reg32 regAddress[], uint8 count);

#endif

/* [] END OF FILE */
