/*******************************************************************************
* File Name: USBInterface.h
*
* Version 1.0
*
*  Description: USBInterface.h exposes USB interface handling routines like
*               USB Suspend, USB Host connection/disconnection event handler etc.
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

#if !defined(USBINTERFACE_H)
#define USBINTERFACE_H

#include <Configuration.h>
#include <project.h>

#define NO_OF_AUDIO_STREAM_INTERFACE            2
#define AUDIO_OUT_INTERFACE_INDEX               0
#define AUDIO_IN_INTERFACE_INDEX                1
#define ALT_SETTING_ZERO_BANDWIDTH              0
#define ALT_SETTING_ACTIVE_24_BIT               2               
#define ALT_SETTING_ACTIVE_16_BIT               1

#define IsUSBConfigured()                        USBFS_bGetConfiguration()

#define NAK_IN_INTERRUPT_ENABLE_MASK             0x20
#define ACKED_TRANSACTION_MASK                   0x10

#define USB_SUSPEND_TIME_TICKS                   5 /* Amount of time after detecting USB no activity the firmware
                                                    * enters USB suspend mode. Set this value to 0 to make suspend equal
                                                    * to sleep timer inerval */

#define USB_INTERFACE_INACTIVE                   0x00
#define USB_INIT_AFTER_ENUMERATION_REQUIRED      0x01
#define USB_INIT_AFTER_ENUMERATION_COMPLETED     0x02

#define SIE_EP_CONTROL_REG_ADDRESS_OFFSET        16

#define STATUS_LED_BLINK_COUNT					 4

#define WINDOWS7_WORKAROUND /* Windows 7 64 bit OS doesn't issue a USB Set configuration command after the host comes
                             * out of USB suspend mode. The PSoC 3 wakeup code should take care of handling this use 
                             * case so that there are no data corruption after PSoC 3 comes out of sleep/suspend mode */

void ServiceUSB(void);
void ServiceUSBSuspend(void);
void HandleUSBHostInterface(void);
void EnableNAKBulkIN(uint8 bEPNumber);
void DisableNAKBulkIN(uint8 bEPNumber);

extern CYBIT usbMiniBActive;
extern uint8 USBDeviceState;

#endif

/* [] END OF FILE */
