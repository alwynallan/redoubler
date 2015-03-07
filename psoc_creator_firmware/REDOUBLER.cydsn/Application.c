/*******************************************************************************
* File Name: Application.c
*
* Version 1.0
*
*  Description: This file contains all the application layer code for
*               user interface handling routines
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
#include <AudioControl.h>
#include <Configuration.h>
#include <device.h>
#include <Interrupts.h>
#include <stdio.h>
#include <USBInterface.h>

/* Extern declarations */
extern uint8 USBFS_initVar;
extern volatile uint8 USBFS_currentVolume[];
extern volatile uint8 USBFS_currentMute;

extern CYBIT codecInit;
extern CYBIT outPlaying;

/* Global variables used for playlist-control buttons */
uint8 buttonStatus = 0;
uint32 buttonMask;
CYBIT applicationInitiate = TRUE;
uint8 playlistControlReport = 0;
uint8 prevReport = 0;

/* Global variables used for the switch "PSOC_SW", which is used for Play/Pause */
// uint8 switchDebounceTimer = 0; APA no switch

/*******************************************************************************
* Function Name: ConfigureApplication
********************************************************************************
* Summary:
*        This function configures the application layer hardware modules and
*        clocks to be in sync with the audio clock updates done in 
*        ConfigureAudioPath API
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ConfigureApplication(void)
{
    CYGlobalIntEnable;
	
    /* Configure the I2C clock speed for 400kHz operation */
	#ifdef CODEC_I2C_SUPPORTED
	I2C_Master_CLKDIV1_REG = I2C_DIVIDER_400KHZ_OPERATION;
	#endif
            
    /* Enable 8ms tick sleep ISR */
    SystemTickTimer_Start();
    isr_Tick_StartEx(Tick_Interrupt);
    
    #ifdef ENABLE_WATCHDOG
    /* Watchdog timer is clocked from internal 1KHz ILO, for USB Operation 100KHz ILO is selected in the clock
     * configuration wizard, explicitly enable 1KHz ILO for WDT */
    CyILO_Start1K();
    
    /* Enable Watchdog for recovering from unresponsive system, The time for WDT is set to two 1sec tick events */
    CyWdtStart(CYWDT_1024_TICKS, CYWDT_LPMODE_DISABLED);
    #endif
    
    /* USER_CODE: [Accessory Initialization] Placeholder for initializing additional user added components and 
     * external peripherals. This block of code is called once after accessory reset event and the system clocks 
     * will be in idle mode (See TopDesign.cysch for idle mode clock details) */
}

/* [] END OF FILE */
