/*******************************************************************************
* File Name: main.c
*
* Version 1.0
*
* Description: This file contains the entry point for the application and 
*              handles the USB audio configuration, audio event handling and 
*              communication with USB hosts (Mac/Win PC/BeagleBoneBlack/RaspberryPi
*              /Android etc).
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
#include <USBInterface.h>

void ConfigureFiReBuG(void)
{
    Comp_0_Start();
    Comp_1_Start();
    Comp_2_Start();
    Comp_3_Start();
    CyDelay(5u); // wait 5 ms for stability
    Comp_0_ZeroCal();
    Comp_1_ZeroCal();
    Comp_2_ZeroCal();
    Comp_3_ZeroCal();
    Comp_0_Stop();
    Comp_1_Stop();
    Comp_2_Stop();
    Comp_3_Stop();
}

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*        Main routine does following tasks.
*        - Initializes all the components for digital audio 
*        - Initializes all the components for user interface and other system functions
*        - Handles hot plug of USB host - Mac/PC/(any USB Host)
*		 - Handles USB host disconnection events
*        - Handles dynamic sample rate change, audio stream start/stop events
*        
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void main(void)
{
    ConfigureFiReBuG();
    
	/* Setup the Audio pipe from USB to I2S. After the call to this API, the system clock architecture changes 
      * from start up mode to idle mode. System clocks such as PLL are shutdown. Any of the application 
	  * layer components which are using PLL as the source of clock would seize to function after this function call.
      * The clocks are shutdown to minimize idle mode current consumption. The clocks are turned back on when 
	  *	Audio Input or Output stream becomes active. Details of all the system clocks in idle mode
      * are shown in "Idle Mode Clock Info" page of the TopDesign. */
    ConfigureAudioPath();
    
    /* Initialize the components other than audio components such as system timer and watchdog. 
	 * Also configure the clock sources of all these components such that these components work in both idle and active modes.
	 * Details of all the system clocks in idle mode are shown in "Idle Mode Clock Info" page of the TopDesign. */
    ConfigureApplication();
  
	/* USER_CODE: Placeholder for users to add any other application specific initialization code.
     * CAUTION: System will be in Idle mode at this point, which means some of the clocks are not active. 
	 * Details of all the system clocks in idle mode are shown in "Idle Mode Clock Info" page of the TopDesign. */

	while(FOREVER)
    {
        
        /* Check for USB enumeration with USB host */
        if(IsUSBConfigured() != FALSE)
        {
            /* Accessory initialization routine after USB enumeration completion 
			 * Also loads the EP's when audio playback/recording starts */
			ServiceUSB();  
            
            /* Enter low power mode if Audio stream is inactive. In low power mode all the audio components
             * (e.g., I2S) and some of the system clocks such as PLL are shutdown. 
			 * Details of all the system clocks in idle mode are shown in "Idle Mode Clock Info" page of the TopDesign.
			 * Details of all the system clocks in active mode are shown in "Active Mode Clock 44.1/48 kHz" page of the TopDesign. */
			HandleDigitalAudioLowPowerMode(); 
            
            /* USB audio sampling frequency change handler.
			 * Checks whether host has changed audio sampling rate.
			 * Configures AudioClkGen to generate a clock synchonized to new audio sampling rate. 
			 * Note: Change the I2C address of codec in Codec.h file, according to Codec used in your design. 
             * Currently, codec I2C address is set to Cirrus codec (CS42L51) address. */
            HandleSamplingFrequencyChangeRequest(); 
        }
        
		HandleUSBHostInterface();     /* Check for PC/Mac USB Audio device connection */
		                
        HandleApplicationTimerTick();      /* Handle all the timeout events */
        
        #ifdef ENABLE_WATCHDOG
        CyWdtClear();                      /* Service watchdog timer */
        #endif
                
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
        HandleAudioInBuffer();             /* Clear audio IN buffer when IN stream is stopped */
        #endif
    }
}

/* [] END OF FILE */
