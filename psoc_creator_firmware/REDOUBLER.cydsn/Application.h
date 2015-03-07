/*******************************************************************************
* File Name: Application.h
*
* Version 1.0
*
*  Description: Application.h provides various function prototypes for all the
*               Application tasks
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

#if !defined(APPLICATION_H)
#define APPLICATION_H
#include <Configuration.h>

/*  Function Prototype  */
void ConfigureApplication(void);          /* Configures application clocks and timers etc. */
void HandleApplicationTimerTick(void);    /* Application timer tick process routine */
void HandleApplicationInterface(void);	  /* User application main routine */


/* Constants for USB descriptors */

#define PC_MAC_AUDIO_WITH_VOLUME_DEVICE        0x00
#define AUDIO_OUT_ENDPOINT                     0x01
#define AUDIO_IN_ENDPOINT                      0x02

/* Constants for HID button */
#define PLAY_PAUSE_MASK                        0x04

/* Constants for switch debounce */
#define SWITCH_DEBOUNCE_DELAY                  4

/* Constants for watchdog */
#define WATCHDOG_RESET_MASK                    0x08

/* Constants for playlist and volume control */
#define VOLUME_MUTE_CHANGE_MASK                0x10
#define PLAY_STATUS_MASK                       0x08
#define SIMPLE_REMOTE_TIMEOUT_INTERVAL         8

/* Constants for MAC/PC playlist control */
#define MAC_PC_PLAY_PAUSE_MASK                 0x01
#define MAC_PC_NEXT_TRACK_MASK                 0x02
#define MAC_PC_PREVIOUS_TRACK_MASK             0x04
#define MAC_PC_HID_CONTROL_ENDPOINT            0x04

/* Constants for low power timing */
#define CLOCK_SWITCHING_TIMEOUT                100
#define CLOCK_SWITCH_TIMED_OUT                 1

/* Constants for I2C  */
#define I2C_DELAY_COUNT                        200
#define I2C_DIVIDER_400KHZ_OPERATION           6  /* I2C block clock divider for 400KHz operation when BUS_CLK = 36.864 MHz */
#define I2C_DIVIDER_100KHZ_OPERATION           24 /* I2C block clock divider for 100KHz operation when BUS_CLK = 36.864 MHz */
#define I2C_DIVIDER_50KHZ_OPERATION            47 /* I2C block clock divider for 50KHz operation when BUS_CLK = 36.864 MHz */
#define I2C_DIVIDER_25KHZ_OPERATION            94 /* I2C block clock divider for 50KHz operation when BUS_CLK = 36.864 MHz */

/* Different constants used in code  */
#define TRUE                                   1
#define FALSE                                  0
#define ZERO                                   0
#define FOREVER                                1
#define ENABLE                                 1
#define DISABLE                                0
#define VALID_MODE                             1
#define INVALID_MODE                           0

/* Macro definition of Play/Pause button press*/
#define IS_PLAY_PAUSE_KEY_PRESSED()				~PSOC_SW_Read() 

/* Macro definition for MAC/PC playlist control */
#define IS_MAC_PC_PLAYLIST_CONTROL_NEEDED()		(IsUSBConfigured()  \
												 && USBFS_GetEPState(MAC_PC_HID_CONTROL_ENDPOINT) == USBFS_EVENT_PENDING && prevReport \
												 != playlistControlReport )

#endif

/* [] END OF FILE */
