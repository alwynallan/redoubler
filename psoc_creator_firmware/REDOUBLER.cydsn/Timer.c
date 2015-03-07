/*******************************************************************************
* File Name: Timer.c
*
* Version 1.0
*
* Description: This file contains the system timer tick event updates
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
#include <Application.h>
#include <Configuration.h>
#include <device.h>
#include <USBInterface.h>

// extern uint8 switchDebounceTimer; APA no SW

extern CYPDATA uint8 clockSwitchTimer;

extern volatile uint8 USBFS_device;

CYBIT applicationTimerTick = FALSE;

/*******************************************************************************
* Function Name: HandleApplicationTimerTick
********************************************************************************
* Summary:
*       This function updates all the Application layer timers based on sleep
*       timer tick event.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleApplicationTimerTick(void)
{
    if(applicationTimerTick)
    {
        
		#ifdef HANDLE_USB_SUSPEND
        ServiceUSBSuspend();          /*Check for USB Suspend event*/
        #endif
           
        //if(switchDebounceTimer) // APA no SW
        //{
        //    switchDebounceTimer--;
        //}
        
        if(clockSwitchTimer)
        {
            clockSwitchTimer--;
        }
		     
        /* USER_CODE: [System tick timer] Placeholder for adding additional timers for custom user timing events. This
         * routine is executed approximately at every 8ms */
        
        applicationTimerTick = FALSE;
    }
}

/* [] END OF FILE */
