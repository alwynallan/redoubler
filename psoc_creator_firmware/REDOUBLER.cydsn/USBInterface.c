/*******************************************************************************
* File Name: USBInterface.c
*
* Version 1.0
*
* Description: This file contains routines for handling PC/Mac/any USB Host
*              USB interface requests.
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
#include <USBInterface.h>
extern volatile uint8 USBFS_interfaceSetting[];
extern CYBIT lowPowerIdle;

extern uint8 USBFS_initVar;
extern uint8 playlistControlReport;
extern CYBIT outPlaying;
extern CYBIT inPlaying;

#ifdef WINDOWS7_WORKAROUND
extern volatile uint8 USBFS_configurationChanged;
void USBFS_Config(uint8 clearAltSetting) CYREENTRANT;
#endif

extern CYBIT codecInit;  

uint8 usbActivityCounter = 0;
CYBIT usbMiniBActive = FALSE;
uint8 USBDeviceState = USB_INTERFACE_INACTIVE;

#if(USBFS_EP_MM == USBFS__EP_DMAAUTO) 
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    uint8 outRam[OUT_AUDIOMAXPKT];
    #endif
  
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
    uint8 inRam[IN_AUDIOMAXPKT];
    uint16 inCnt;
    #endif
#endif

uint8 altSetting[NO_OF_AUDIO_STREAM_INTERFACE] = {0xFF, 0xFF};

/*******************************************************************************
* Function Name: ServiceUSB
********************************************************************************
* Summary: This routine performs tasks that should be done soon after USB 
*          enumeration is completed (configure DMA, initialize state machine etc).
*          When the USB configuration is changed, this routine reinitializes all
*          the USB endpoints as required by the application.       
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ServiceUSB(void)
{
    
	if(USB_INTERFACE_INACTIVE == USBDeviceState)
    {
        USBDeviceState = USB_INIT_AFTER_ENUMERATION_REQUIRED;
    }
	
	/* Initialization sequence for every USB host enumeration event */
    if(USBDeviceState == USB_INIT_AFTER_ENUMERATION_REQUIRED)
    {
        uint16 index = 0;
        
        USBDeviceState = USB_INIT_AFTER_ENUMERATION_COMPLETED;
        
        #if(USBFS_EP_MM == USBFS__EP_DMAAUTO)
            
			for(index=0; index< OUT_AUDIOMAXPKT; index++)
            {
                #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
                outRam[index] = 0;
                #endif
            }
			
			for(index=0; index< IN_AUDIOMAXPKT; index++)
            {
                #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
                inRam[index] = 0;
                #endif                
            }
            
			#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
            inCnt = IN_AUDIOMAXPKT;
            #endif
        #endif
        
		/* USER_CODE: [USB enumeration] placeholder for initializing custom user code after the USB host enumerates the
         * accessory. This routine will be called once per accessory connection after the host issues SET_CONFIGURATION
         * request */
    }
    
   
    /* USBFS_IsConfigurationChanged() is a clear on read status update therefore, only one read of 
     * USBFS_IsConfigurationChanged() should ever exist in user code */
    if(USBFS_IsConfigurationChanged())
    {
        
		#ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY    
        /* Get Alternate setting */
        altSetting[AUDIO_OUT_INTERFACE_INDEX] = USBFS_GetInterfaceSetting(1); 
        
        /* ByteSwap control register bit is set to 1 if alt setting 2 is selected so that  
         * Byte swap digital logic processes data as 16 bits. ByteSwap control register is set to 0 
         * if alt setting 1 is selected and byte swap processes data as 24 bits */
        if (altSetting[AUDIO_OUT_INTERFACE_INDEX]==ALT_SETTING_ACTIVE_24_BIT)
        {
            
            ByteSwap_Tx_CONTROL_REG = ByteSwap_Tx_CONTROL_REG & (~ByteSwap_Tx_RES_CTRL_16);  
        }
        else if (altSetting[AUDIO_OUT_INTERFACE_INDEX]==ALT_SETTING_ACTIVE_16_BIT)
        {
            
            ByteSwap_Tx_CONTROL_REG = ByteSwap_Tx_CONTROL_REG | ByteSwap_Tx_RES_CTRL_16;            
        }
        
        /* Arming the audio out EP if it is not zero bandwidth alt setting */
        if (altSetting[AUDIO_OUT_INTERFACE_INDEX]!= ALT_SETTING_ZERO_BANDWIDTH && 
            (CY_GET_REG8(USBFS_SIE_EP1_CR0_PTR + ((AUDIO_OUT_ENDPOINT - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT)) & USBFS_MODE_MASK) 
                                                                                    == USBFS_MODE_NAK_IN_OUT)
        {
            /* Init DMA configurations for audio OUT EP */
            USBFS_ReadOutEP(AUDIO_OUT_ENDPOINT, &outRam[0], OUT_AUDIOMAXPKT);
            USBFS_EnableOutEP(AUDIO_OUT_ENDPOINT);
        }
        #endif
        
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
            #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY 
            if(altSetting[AUDIO_IN_INTERFACE_INDEX] != USBFS_GetInterfaceSetting(2))
        {
                  altSetting[AUDIO_IN_INTERFACE_INDEX] = USBFS_GetInterfaceSetting(2);
            #else
            if(altSetting[AUDIO_IN_INTERFACE_INDEX] != USBFS_GetInterfaceSetting(1))	
        {
                  altSetting[AUDIO_IN_INTERFACE_INDEX] = USBFS_GetInterfaceSetting(1);	
            #endif
            
            /* Arming the audio in EP if it is not zero bandwidth alt setting */
            if (altSetting[AUDIO_IN_INTERFACE_INDEX]!= ALT_SETTING_ZERO_BANDWIDTH &&
                (CY_GET_REG8(USBFS_SIE_EP1_CR0_PTR + ((AUDIO_IN_ENDPOINT - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT)) & USBFS_MODE_MASK) 
                                                                                        == USBFS_MODE_NAK_IN_OUT)
            {
                /* Init DMA configurations for audio IN EP */  
                inCnt = IN_AUDIOMAXPKT;
                USBFS_LoadInEP(AUDIO_IN_ENDPOINT, &inRam[0], inCnt);
                /* Pre-arm first audio IN request */
                USBFS_LoadInEP(AUDIO_IN_ENDPOINT, USBFS_NULL, inCnt);
            }
        }
        #endif
        
        /* Configure the HID input endpoint buffer for Mac/PC playlist control */
        USBFS_LoadInEP(MAC_PC_HID_CONTROL_ENDPOINT, &playlistControlReport, sizeof(playlistControlReport));
        
        /* USER_CODE: [USB configuration changed] Placeholder for adding additional USB endpoint initialization code 
         * when the host issues either a SET_INTERFACE or SET_CONFIGURATION request to the accessory. After receiving
         * a SET_INTERFACE request from the host, the endpoint belonging to the alternate setting being configured
         * by the USB host is reset and must be reinitialized here for proper operation of the USB block */
    }
}

/*******************************************************************************
* Function Name: ServiceUSBSuspend
********************************************************************************
* Summary:
*       This function handles USB suspend event from USB host and forces PSoC 5LP 
*       to enter low power mode. Once the USB resume event is detected, PSoC 5LP 
*       wakes up and starts operating in normal mode.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
#ifdef  HANDLE_USB_SUSPEND
void ServiceUSBSuspend(void)
{
    //uint8 ledBlinkCnt = STATUS_LED_BLINK_COUNT;	
	
	if(! USBFS_initVar)
    {
      return;
    }
  
    /* Check if the host is active */
    if(USBFS_bCheckActivity() != 0 ) 
    {
      usbActivityCounter = 0;
    } 
    else 
    {
      usbActivityCounter++;
    }
        
    /* USB Suspend event is lack of greater than 3 consecutive SOF's */
    if(usbActivityCounter > USB_SUSPEND_TIME_TICKS )
    {
        /* The debounce delay is taken care by increasing the suspend time to 40ms (5 * 8ms) */                   
        if(IsUSBConfigured()) 
        {  
            /* USER_CODE: [USB suspend] Placeholder for configuring ALL the additional components added by the user in 
             * sleep mode before calling USB suspend/PSoC 3 sleep API */
                      
            /* If the accessory is not in low power mode, enter low power mode on seeing a USB suspend */
            if(!lowPowerIdle) 
            {
                lowPowerIdle = TRUE;
                StopAudioComponents();             /* Changes to 24 MHz IMO for USB */                        
            }
            
			#ifdef ENABLE_PDM 	
		        //PDM_CIC_Sleep();
				//Droop_Filter_ModifiedSleep();	
			#endif
			
			/* Blink the STATUS LED twice before entering suspend mode */
			//while(ledBlinkCnt)					   		
			//{
			//	CyDelay(100);
			//	PSOC_STATUS_LED_Write(~PSOC_STATUS_LED_Read());
			//	ledBlinkCnt--;
			//}
			
			/* Turn off the regulator to reduce suspend mode current */    
//            CyPins_ClearPin(PSOC_CODEC_PWR_0);     /* Uncomment this line only if PSOC_CODEC_PWR pin in TopDesign is enabled */
   						
            USBFS_Suspend();
			
			#ifdef CODEC_I2C_SUPPORTED
			I2C_Master_Sleep();                /* Configure I2C master block in sleep mode */ 
            #endif
			
            CyPmSaveClocks();            
            CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_PICU); /* PSoC 3 is in sleep mode */
            CyPmRestoreClocks();
			
			USBFS_Resume();
			
			#ifdef ENABLE_PDM 		
		    	//PDM_CIC_Wakeup();
				//Droop_Filter_ModifiedWakeup();
			#endif
			
			#ifdef CODEC_I2C_SUPPORTED
			I2C_Master_Wakeup();
			#endif
			
			/* Turn ON the CODEC regulator after wake up */	
//            CyPins_SetPin(PSOC_CODEC_PWR_0);      /* Uncomment this line only if PSOC_CODEC_PWR pin in TopDesign is enabled */
           
            #ifdef WINDOWS7_WORKAROUND		
            if(USBFS_GetConfiguration() != 0)
            {
                USBFS_configurationChanged = USBFS_TRUE;
                USBFS_Config(USBFS_FALSE);
            }
            #endif
     
            /* USER_CODE: [USB wakeup] Placeholder for re-configuring ALL the additional components added by the user in 
             * wakeup mode after calling USB wakeup */
        }
        usbActivityCounter = 0;
		/* After coming out of USB suspend, MIDI end point should be re-initialized */
    }
}
#endif

/****************f***************************************************************
* Function Name: HandleUSBHostInterface
********************************************************************************
* Summary: Checks if USB Host is connected/disconnected and start the USB component
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleUSBHostInterface(void)
{
    
    if(!USBFS_initVar)
    {  
        
		/* Start the USB component when PC/Mac is connected */
        USBFS_Start(PC_MAC_AUDIO_WITH_VOLUME_DEVICE, USBFS_DWR_VDDD_OPERATION);
        USBDeviceState = USB_INIT_AFTER_ENUMERATION_REQUIRED;
        usbMiniBActive = TRUE;
        
        /* USER_CODE: [USB Host connection] Placeholder for initializing components or external peripherals when the
         * accessory is plugged into a USB Host (USB VBus = High) */
    }
	
		
}

/* [] END OF FILE */
