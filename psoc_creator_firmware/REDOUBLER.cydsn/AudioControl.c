/*******************************************************************************
* File Name: AudioControl.c
*
* Version 1.0
*
*  Description: This file contains the Audio signal path configuration and 
*               processing code
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
#include <Device.h>
#include <Interrupts.h>
#include <project.h>
#include <USBInterface.h>

extern volatile uint8 USBFS_frequencyChanged;   /* USB audio class sampling frequency change flag */
extern volatile uint8 USBFS_currentSampleFrequency[][USBFS_SAMPLE_FREQ_LEN]; /* audio SR received from USB host */
extern volatile uint8 USBFS_interfaceSetting[]; /* current USB active interface settings */
extern volatile uint8 USBFS_transferState;      /* USB component state machine value */
extern volatile uint8 USBFS_device;             /* currently active USB device descriptor */

extern CYBIT audioClkConfigured;                 /* AudioClkGen configuration flag */
//extern CYDATA CodecRegister CodecWrite;    		 /* codec register read/write structure */ apa killed

#if(USBFS_EP_MM == USBFS__EP_DMAAUTO) 
  #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
  extern uint8 outRam[OUT_AUDIOMAXPKT];          /* USB Auto DMA mode audio OUT EP buffer */
  #endif
  #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
  extern uint8 inRam[IN_AUDIOMAXPKT];            /* USB Auto DMA mode audio IN EP buffer */
  extern uint16 inCnt;                           /* USB audio IN EP actual count (varies based on audio sample rate */
  #endif
#endif

volatile uint8 buf_8to16[2]; // buffer for assembling 16-bit values

uint8 USBOutDmaChan;            /* DMA Channel: USB EP memory to OUT circular SRAM  */
CYPDATA uint8 txDmaChan;        /* DMA Channel: OUT circular buffer to ByteSwap Tx DMA */
CYPDATA uint8 I2STxDMAChan;     /* DMA Channel: ByteSwap Tx to I2S Tx DMA */
uint8 USBInDmaChan;             /* USB IN circular SRAM memory to IN EP DMA */
CYPDATA uint8 rxDmaChan;        /* DFB  -> IN Circular buffer DMA */

CYPDATA uint8 txTd[NUM_TDS];    /* OUT circular buffer to ByteSwap Tx TDs */
CYPDATA uint8 rxTd[NUM_TDS];    /* ByteSwap Rx to circular IN buffer TDs */
uint8 I2STxTd;                  /* ByteSwap Tx to I2S Tx TD */
uint8 I2SRxTd;                  /* I2S Rx to ByteSwap Rx TD */
uint8 USBOutTd[2];              /* USB EP memory to OUT circular SRAM TDs */
uint8 USBInTd[2];               /* USB IN circular SRAM memory to IN EP TDs */

CYBIT  resetTx = 0;             /* audio OUT stream reset flag */
CYBIT  outPlaying = 0;          /* audio OUT stream (playback) active flag */
uint16 outLevel = 0;            /* audio OUT buffer level pointer */
uint16 outUsbCount = 0;         /* audio OUT USB interface count */
uint16 outUsbShadow = 0;        /* audio OUT temp count */
uint8  outBuffer[OUT_BUFSIZE];  /* audio OUT circular buffer */
uint16 outBufIndex = 0;         /* audio OUT USB DMA index */

#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
CYBIT  resetRx = 0;             /* audio IN stream reset flag */
CYBIT  inPlaying = 0;           /* audio IN stream (recording) active flag */
uint16 inLevel = IN_BUFSIZE;    /* audio IN buffer level pointer */
uint16 inUsbCount = 0;          /* audio IN USB interface count */
uint16 inUsbShadow = 0;         /* audio IN temp count */
CYBIT  clearInBuffer = 0;       /* audio IN buffer reset flag */
uint8 inBuffer[IN_BUFSIZE];     /* audio IN circular buffer */
uint16 inBufIndex = 0;          /* audio IN USB DMA index */
#endif


CYBIT lowPowerIdle = TRUE;          /* audio low power mode flag (low power = PLL etc. shut down) */

CYPDATA uint8 setRate = FREQUENCY_NOT_SET; /* Audio sample rate configured or not in AudioClkGen component */
CYBIT rateChangedWhileInactive = FALSE;    /* Sample rate changed while the system was in low power mode flag */
CYPDATA uint8 clockSwitchTimer = 0;        /* Timer for audio clock shutdown when the streaming interface is inactive */
CYBIT audioClkConfigured = FALSE;          /* AudioClkGen is configured with one or the other sample rate */

CYPDATA uint8 rate;             /* macro which holds the sample rate issues by the USB host */

#ifdef DISABLE_DFB
uint8 leftCICOutput[CIC_OUT_BUFSIZE];
uint8 rightCICOutput[CIC_OUT_BUFSIZE];
#endif

void FiReBuG_Start(void)
{
    Opamp_0_Start();
    Opamp_1_Start();
    Opamp_2_Start();
    Opamp_3_Start();
    Sample_Hold_0_Start();
    Sample_Hold_1_Start();
    Sample_Hold_2_Start();
    Sample_Hold_3_Start();
    Comp_0_Start();
    Comp_1_Start();
    Comp_2_Start();
    Comp_3_Start();
}

void FiReBuG_Stop(void)
{
    Opamp_0_Stop();
    Opamp_1_Stop();
    Opamp_2_Stop();
    Opamp_3_Stop();
    Sample_Hold_0_Stop();
    Sample_Hold_1_Stop();
    Sample_Hold_2_Stop();
    Sample_Hold_3_Stop();
    Comp_0_Stop();
    Comp_1_Stop();
    Comp_2_Stop();
    Comp_3_Stop();
}

void setup_DMA_8to16(void)
{
    /* Variable declarations for DMA_8to16 */
    /* Move these variable declarations to the top of the function */
    uint8 DMA_8to16_Chan;
    uint8 DMA_8to16_TD[2];

    /* DMA Configuration for DMA_8to16 */
    #define DMA_8to16_BYTES_PER_BURST 1
    #define DMA_8to16_REQUEST_PER_BURST 1
    #define DMA_8to16_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_8to16_DST_BASE (CYDEV_SRAM_BASE)
    DMA_8to16_Chan = DMA_8to16_DmaInitialize(DMA_8to16_BYTES_PER_BURST, DMA_8to16_REQUEST_PER_BURST, 
        HI16(DMA_8to16_SRC_BASE), HI16(DMA_8to16_DST_BASE));
    DMA_8to16_TD[0] = CyDmaTdAllocate();
    DMA_8to16_TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_8to16_TD[0], 1, DMA_8to16_TD[1], 0);
    CyDmaTdSetConfiguration(DMA_8to16_TD[1], 1, DMA_8to16_TD[0], DMA_8to16__TD_TERMOUT_EN);
    CyDmaTdSetAddress(DMA_8to16_TD[0], LO16((uint32)Status_Reg_1_Status_PTR), LO16((uint32)buf_8to16));
    CyDmaTdSetAddress(DMA_8to16_TD[1], LO16((uint32)Status_Reg_1_Status_PTR), LO16((uint32)(buf_8to16+1)));
    CyDmaChSetInitialTd(DMA_8to16_Chan, DMA_8to16_TD[0]);
    CyDmaChEnable(DMA_8to16_Chan, 1);
}

/*******************************************************************************
* Function Name: ConfigureAudioPath
********************************************************************************
* Summary:
*       This function sets up the DMA and starts USB, I2S and interrupts
*       to get the PSoC 5 device configured for audio streaming mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ConfigureAudioPath(void)
{
    uint8 index;
    
//	CyPins_SetPin(PSOC_CODEC_PWR_0); /* Enable this code only if PSOC_CODEC_PWR pin is enabled in the TopDesign */
	
	#ifdef CODEC_I2C_SUPPORTED
	I2C_Master_Start();  		/* Start I2C for codec configuration */
    #endif
	
	CyMasterClk_SetSource(CY_MASTER_SOURCE_IMO); /* Set the system clock to IMO */
	CyDelayFreq(DELAY_FREQ_PARAM_VALUE_IMO);
    CyDelayUs(100);    
    CyPLL_OUT_Stop();
    Clock_CIC_Running_Write(0u);
    FiReBuG_Stop();
        
    CY_SET_REG8((void CYXDATA *)(CYDEV_FASTCLK_PLL_CFG1), 0); /* Change the settings for the PLL filtering */

    AudioClkGen_Start();
    rate = RATE_44KHZ;
    CyPLL_OUT_SetSource(CY_PLL_SOURCE_DSI);
    
	/* Starting the MCLK always as required by some codecs */
	#ifdef MCLK_ALWAYS_ENABLED
	CyPLL_OUT_Start(0);
	AudioClkGen_SetAudioRate(RATE_48KHZ);
	#ifdef I2S_PIN_DRIVE_MODE_CHANGE_IN_IDLE_MODE
	    PSOC_I2S_MCLK_SetDriveMode(PSOC_I2S_MCLK_DM_STRONG);		
    #endif
	#endif 

    /* Audio sample SRAM to ByteSwap and vice versa DMA configuration*/
    /*______________________SRAM to ByteSwap (Out path) & DFB to SRAM (In path) DMA Config Start______________________*/
    
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    /* Set up the TX DMA, 1 byte bursts, each burst requires a request, upper addr of 0 */
    txDmaChan = TxDMA_DmaInitialize(DMA_BURSTCOUNT, RQST_PER_BURST, HI16(CYREG_SRAM_DATA_MBASE), HI16(CYDEV_PERIPH_BASE));		
    #endif
    
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
    /* Rx DMA Config, 1 byte bursts, each burst requires a request, upper addr of 0 */
    rxDmaChan = RxDMA_DmaInitialize(IN_DMA_BURSTCOUNT, RQST_PER_BURST, HI16(CYREG_SRAM_DATA_MBASE), HI16(CYREG_SRAM_DATA_MBASE));	
    #endif
    
    for (index=0; index < NUM_TDS; index++)
    {
        /* Request for a set of TDs from the pool */
        #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
        txTd[index] = CyDmaTdAllocate();
        #endif
        
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
        rxTd[index] = CyDmaTdAllocate();
        #endif
    }    
        
    for (index=0; index < NUM_TDS; index++)
    {
        #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
        /* Configure this Td chain as follows:
         * Loop through all of the TDs , Increment the source address, but not the destination address */
        CyDmaTdSetConfiguration(txTd[index], OUT_TRANS_SIZE, txTd[(index+1)%NUM_TDS], TD_INC_SRC_ADR | TxDMA__TD_TERMOUT_EN);
        #endif
        
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
        /* Configure this Td chain as follows:
         *  Loop through all of the TDs, Increment the destination address, but not the source address */
        CyDmaTdSetConfiguration(rxTd[index], IN_TRANS_SIZE, rxTd[(index+1)%NUM_TDS], TD_INC_DST_ADR | RxDMA__TD_TERMOUT_EN);
        #endif
        
        #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
        /* From the Audio Out SRAM buffer to ByteSwap component input FIFO */
        CyDmaTdSetAddress(txTd[index], LO16((uint32)outBuffer+(OUT_TRANS_SIZE*index)), LO16((uint32)ByteSwap_Tx_dp_ByteSwap_u0__F0_REG));
        #endif
        
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
        /* From the Droop Filter DFB component output holding register to Audio In SRAM buffer */
        CyDmaTdSetAddress(rxTd[index], LO16((uint32)buf_8to16), LO16((uint32)inBuffer+(IN_TRANS_SIZE*index)));	
        #endif
        setup_DMA_8to16();
    }
    /* __________________________________SRAM to ByteSwap DMA Config End_____________________________________________ */
    
    
    
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    /* __________________________________ByteSwap to I2S DMA Config Start_____________________________________________*/
    I2STxDMAChan = I2S_Tx_DMA_DmaInitialize(DMA_BURSTCOUNT, RQST_PER_BURST, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));
    I2STxTd = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(I2STxTd, I2SDMA_TRANS_SIZE, I2STxTd, I2SDMA_CONFIG);
    CyDmaTdSetAddress(I2STxTd, LO16((uint32)ByteSwap_Tx_dp_ByteSwap_u0__F1_REG), LO16((uint32)I2S_TX_FIFO_0_PTR) );		
    CyDmaChSetInitialTd(I2STxDMAChan, I2STxTd);
    /* __________________________________ByteSwap to I2S DMA Config End_______________________________________________*/
    #endif
    
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    /* USB Out DMA Config:  Entire chain is sent based on a single request from the CPU. Td's are configured later */
    USBOutDmaChan = USBOutDMA_DmaInitialize(DMA_BURSTCOUNT, USBDMA_RQST_PER_BURST, HI16(CYREG_SRAM_DATA_MBASE), HI16(CYREG_SRAM_DATA_MBASE));  
    USBOutTd[0] = CyDmaTdAllocate();
    USBOutTd[1] = CyDmaTdAllocate();
    #endif
    
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
    /* USB In DMA Config: Entire chain is sent based on a single request from the CPU. Td's are configured later    */
    USBInDmaChan = USBInDMA_DmaInitialize(DMA_BURSTCOUNT, USBDMA_RQST_PER_BURST, HI16(CYREG_SRAM_DATA_MBASE), HI16(CYREG_SRAM_DATA_MBASE)); 
    USBInTd[0] = CyDmaTdAllocate();
    USBInTd[1] = CyDmaTdAllocate();
    #endif
    
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    isr_TxDMADone_StartEx(TxDMADone_Interrupt);
    #endif
    
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
    isr_RxDMADone_StartEx(RxDMADone_Interrupt);
    isr_InDMADone_StartEx(InDMADone_Interrupt);
    #endif
    
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    /* set TX FIFO trigger to 2 bytes (half-empty) to increase timing margin */
    I2S_TX_AUX_CONTROL_REG = I2S_TX_AUX_CONTROL_REG | FIFO_HALF_EMPTY_MASK;
    #endif
    
    #ifdef ENABLE_VOLUME_CONTROL
    InitUSBVolumeLevel();
    #endif
    
    #ifdef ENABLE_PDM
        Clock_CIC_Running_Write(0u);
        Clock_CIC_Stop();
        FiReBuG_Stop();
        //PDM_CIC_Start();
        //CICOutDMA_ConfigAndStart();
        //isr_CICOverflow_StartEx(cicOverflow_Interrupt);
		
        //Droop_Filter_DALIGN_REG = 0x0C;  /* Align Data A & B holding register */
        //Droop_Filter_COHER_REG  = 0x55;  /* holding MID & staging MID for both A and B registers */
        //Droop_Filter_Start();
    #endif

   
    /* USER_CODE: [Audio Initialization] Placeholder for user code to initialize additional audio path components or 
     * external audio peripheral configuration */
}

/*******************************************************************************
* Function Name: ProcessAudioOut
********************************************************************************
* Summary:
*        Handle audio out data, setup USB DMA and trigger the DMA to transfer 
*        audio samples from SRAM USB endpoint memory to SRAM audio circular 
*        buffer. The API also starts the I2S transmit when USB audio out streaming 
*        is active
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
#ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
void ProcessAudioOut(void) 
{
	uint16 count;
    uint16 remain;
    
    if( TRUE == audioClkConfigured
        
      )
    {
        if (resetTx)         /* Check TX buffer reset condition and clear pointers if required */
        {
            outBufIndex = 0;
            outUsbCount = 0;
            resetTx = 0;
        }
        
        CyDmaChDisable(USBOutDmaChan);    /* Disable the USBOut DMA channel */
        
        count = USBFS_GetEPCount(AUDIO_OUT_ENDPOINT);
    
        /* Update of usbCount needs to be atomic */
        isr_TxDMADone_Disable();
        outUsbCount += count;
        isr_TxDMADone_Enable();
        
        if((outBufIndex + count) > sizeof(outBuffer))
        {
            remain = sizeof(outBuffer) - outBufIndex;  /* Set up TD to wrap around circular buffer */
            
            CyDmaTdSetConfiguration(USBOutTd[0], remain, USBOutTd[1], TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_AUTO_EXEC_NEXT | USBOutDMA__TD_TERMOUT_EN);	
            CyDmaTdSetConfiguration(USBOutTd[1], count-remain, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR | TD_INC_DST_ADR | USBOutDMA__TD_TERMOUT_EN );		
            CyDmaTdSetAddress(USBOutTd[0], LO16( (uint32) outRam), LO16((uint32)outBuffer+outBufIndex));	
            CyDmaTdSetAddress(USBOutTd[1], LO16( (uint32)outRam + remain), LO16((uint32)outBuffer));		

            CyDmaChSetInitialTd(USBOutDmaChan, USBOutTd[0]);
            outBufIndex = count-remain;
        }
        else 
        {
            /* Single contiguous TD */
            CyDmaTdSetConfiguration(USBOutTd[0], count, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR | TD_INC_DST_ADR | USBOutDMA__TD_TERMOUT_EN  );	
            CyDmaTdSetAddress(USBOutTd[0], LO16( (uint32)outRam), LO16((uint32)outBuffer+outBufIndex));	
            CyDmaChSetInitialTd(USBOutDmaChan, USBOutTd[0]);
            outBufIndex += count;
            if (outBufIndex == sizeof(outBuffer)) outBufIndex = 0;
        }
        
        CyDmaChEnable(USBOutDmaChan, 1);           /* Enable the USB Out DMA, don't update the Td as it progresses */
        
        CyDmaChSetRequest(USBOutDmaChan, CPU_REQ); /* Start the DMA */
    
        /* Start playing audio only when transmit buffer is more than half full */
        if(!outPlaying && outUsbCount >= OUT_HALF)
        {
            outPlaying = TRUE;
            
            I2S_ClearTxFIFO(); /* Clear the I2S internal FIFO */
            
            /* clear any potential DMA requests and re-reset TD pointer */
            while((DMAC_CH[txDmaChan].basic_status[0] & 2));
    
            CyDmaChSetRequest(txDmaChan, CPU_TERM_CHAIN);
            CyDmaChEnable(txDmaChan, 1);
    
            while((DMAC_CH[txDmaChan].basic_cfg[0] & 1));

            /* Enable the Tx DMA, initialized to start of buffer */
            CyDmaChSetInitialTd(txDmaChan, txTd[0]);
            CyDmaChEnable(txDmaChan, 1);
            
            ByteSwap_Tx_Start();
                      
            CyDmaChEnable(I2STxDMAChan, 1);   /* enable byte swap to I2S DMA channel */

            I2S_EnableTx();                   /* Unmute the Tx output */
            
            
        }
        
        /* USER_CODE: [USB audio OUT endpoint ISR] Placeholder for user code to know when an USB audio OUT packet is 
         * received from the USB host. This routine is called from an ISR, do not add time consuming tasks inside
         * this routine so that other interrupts in the system can be serviced in a timely manner */
    }
}
#endif

/*******************************************************************************
* Function Name: ProcessAudioIn
********************************************************************************
* Summary:
*        Handle USB audio in data, setup USB DMA and trigger to transfer samples 
*        from SRAM audio circular buffer to SRAM USB endpoint memory.  Start PDM 
*		 receive when USB is active.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
void ProcessAudioIn(void)
{   
	uint16 remain;
    uint16 count = IN_AUDIOMAXPKT;
    static uint8 rate44_count = 0;
    
    if( audioClkConfigured ==  TRUE )
    {
        if (resetRx)
        {
            inBufIndex = 0;
            inUsbCount = 0;
            resetRx = 0;
            rate44_count = 0;    
        }
        
        CyDmaChDisable(USBInDmaChan);
        
        switch(rate)
        {
            case RATE_48KHZ:                    
                    count = IN_AUDIOMAXPKT;        /* Count is number of bytes consumed from the buffer */
                break;
            case RATE_44KHZ:
                    if(9 == rate44_count) 
                    {                            
                        count = IN_AUDIOMAXPKT - (IN_AUDIOMAXPKT/16);  /* adjust the count to cater for 44.1kHz SR */
                        rate44_count = 0;
                    }
                    else 
                    {                            
                        count = IN_AUDIOMAXPKT - (IN_AUDIOMAXPKT/12); /* adjust the count to cater for 44.1kHz SR */
                        rate44_count++;
                    }
                break;
            //case RATE_32KHZ:          APA Not an option      
            //        count = IN_AUDIOMAXPKT - (IN_AUDIOMAXPKT/3);        
            //    break;
            default:
                break;
        }
        
        inCnt = count;
         
        /* Update of inUsbCount needs to be atomic */
        isr_RxDMADone_Disable();
        inUsbCount += count;
        isr_RxDMADone_Enable();
                
        if ((inBufIndex + count) > sizeof(inBuffer)) 
        {
            /* Set up TD to wrap around circular buffer */
            remain = sizeof(inBuffer) - inBufIndex;

            CyDmaTdSetConfiguration(USBInTd[0], remain, USBInTd[1], TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_AUTO_EXEC_NEXT);
            CyDmaTdSetConfiguration(USBInTd[1], count-remain, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR | TD_INC_DST_ADR | USBInDMA__TD_TERMOUT_EN);
            CyDmaTdSetAddress(USBInTd[0], LO16((uint32)inBuffer+inBufIndex), LO16((uint32) inRam));
            CyDmaTdSetAddress(USBInTd[1], LO16((uint32)inBuffer), LO16((uint32) inRam + remain));
             
            CyDmaChSetInitialTd(USBInDmaChan, USBInTd[0]);
            inBufIndex = count-remain;
        }
        else 
        {
            /* Single contiguous TD */
            CyDmaTdSetConfiguration(USBInTd[0], count, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR | TD_INC_DST_ADR | USBInDMA__TD_TERMOUT_EN);
            CyDmaTdSetAddress(USBInTd[0], LO16((uint32)inBuffer+inBufIndex), LO16((uint32) inRam));
            
            CyDmaChSetInitialTd(USBInDmaChan, USBInTd[0]);
            inBufIndex += count;
            if (inBufIndex == sizeof(inBuffer)) 
			{
				inBufIndex = 0;
			}	
        }
    
        /* Enable the USB In DMA, don't update the Td as it progresses */
        CyDmaChEnable(USBInDmaChan, 1);
        CyDmaChSetRequest(USBInDmaChan, CPU_REQ); /* Start the DMA now */

        /* Sending of the data on the USB interface is enabled when the interrupt indicates that the buffer 
         * has been filled. */
        if (!inPlaying && inUsbCount >= IN_HALF) 
        {    
            inPlaying = 1;
                       
            /*Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
            CyDmaChSetRequest(rxDmaChan, CPU_TERM_CHAIN);
            CyDmaChEnable(rxDmaChan, 1);
            
            /* Enable the Rx DMA, initialized back to the first TD */
            CyDmaChSetInitialTd(rxDmaChan, rxTd[0]);
            CyDmaChEnable(rxDmaChan, 1);
            
            #ifdef ENABLE_PDM
            FiReBuG_Start();
            Clock_CIC_Start(); /* This starts the CIC engine */
            Clock_CIC_Running_Write(1u);
			#endif
        }
        
        /* USER_CODE: [USB audio IN endpoint ISR] Placeholder for user code to know when an USB audio IN packet is 
         * sent to the USB host. This routine is called from an ISR, do not add time consuming tasks inside this
         * routine so that other interrupts in the system can be serviced in a timely manner */
    }
}
#endif

/*******************************************************************************
* Function Name: Stop_I2S_Tx
********************************************************************************
* Summary:
*        This function stops the I2S data transmission by disabling the I2S and 
*        transmit DMA.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Stop_I2S_Tx(void) CYREENTRANT
{
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
    if(outPlaying)
    {       
        I2S_DisableTx(); /* Stop I2S Transmit (Mute), I2S output clocks still active */
        
        CyDelayUs(20); /* Provide enough time for DMA to transfer the last audio samples completely to I2S TX FIFO */
        
        ByteSwap_Tx_Stop(); /* Terminate ByteSwap logic and hence DMA request line to TxDMA (SRAM to ByteSwap DMA) */

       
        CyDmaChDisable(txDmaChan); /* Stop/Disable DMA - Needed to reset to start of chain */
        CyDmaChDisable(I2STxDMAChan); /* Disable ByteSwap to I2S data transfer DMA channel */
        
                
        resetTx = 1;
        outLevel = 0;
        outUsbShadow = 0;
        outPlaying = 0;
        
        /* USER_CODE: [USB audio playback stops] Placeholder for user code to shutdown any of the audio OUT path 
         * components. This routine is called when USB audio OUT endpoint stops streaming audio */
    }
    #endif
}

/*******************************************************************************
* Function Name: Stop_PDM_InPath
********************************************************************************
* Summary:
*        This function stops the PDM data reception by disabling the clock to the CIC and 
*        disabling the DMA TDs.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
void Stop_PDM_InPath(void) CYREENTRANT
{
    if(inPlaying)
    {
             
        /* Terminate TD chain & Stop/Disable DMA - Needed to reset to start of chain */
        CyDmaChSetRequest(rxDmaChan, CPU_TERM_CHAIN);
                
        resetRx = 1;
        
        clearInBuffer = 1;
        
        inLevel = IN_BUFSIZE;
        inUsbShadow = 0;    
        inPlaying = 0;
        
        #ifdef ENABLE_PDM
        Clock_CIC_Running_Write(0u);
        Clock_CIC_Stop(); /* This shuts down the CIC engine completely */
        FiReBuG_Stop();
		#endif
        
        /* USER_CODE: [USB audio recording stops] Placeholder for user code to shutdown any of the audio IN path 
         * components. This routine is called when USB audio IN endpoint stops requesting audio IN samples */
    }
}
#endif

/*******************************************************************************
* Function Name: SetClockRate
********************************************************************************
* Summary:
*        This function changes the audio clocking to generate clocks for a desired 
*        sample rate.
*
* Parameters:
*  newRate: audio sample rate from list in AudioClkGen component which is to be set
*
* Return:
*  void
*
*******************************************************************************/
void SetClockRate(uint8 newRate) CYREENTRANT
{
  
        
    /* Stop I2S and PDM path before changing PLL clock */
    #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
	Stop_I2S_Tx();
    #endif 
	
    #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
	Stop_PDM_InPath();
	#endif
    
    CyMasterClk_SetSource(CY_MASTER_SOURCE_IMO);
	CyDelayFreq(DELAY_FREQ_PARAM_VALUE_IMO);
    rate = newRate;

    AudioClkGen_SetAudioRate(newRate);
	
	
	switch(newRate)
    {
        //case AudioClkGen_RATE_32KHZ: APA Not anymore
        //    #ifdef ENABLE_PDM
            //Clock_CIC_SetDividerRegister(DIVIDER_32K_SR, 0);
        //    #endif
            
        //break;
        
        case AudioClkGen_RATE_48KHZ:
            #ifdef ENABLE_PDM
            //Clock_CIC_SetDividerRegister(DIVIDER_44K_48K_SR, 0);
            #endif
            
        break;
        
        case AudioClkGen_RATE_44KHZ:
            #ifdef ENABLE_PDM
            //Clock_CIC_SetDividerRegister(DIVIDER_44K_48K_SR, 0);
            #endif
            
        break;
    }
	
    CyMasterClk_SetSource(CY_MASTER_SOURCE_PLL);
    CyDelayFreq(DELAY_FREQ_PARAM_VALUE_PLL);
	  
    /* flag to indicate audio clock active */
    audioClkConfigured = TRUE;
    
    /* CODEC is initialized when sampling frequency change request is received from the USB host (the sampling frequency
     * change event triggers the call to this routine), if the host is fast and requests for audio In samples immediately
     * after sampling frequency change request, then the CODEC interface wouldn't be ready for approximately 20ms
     * (20ms is specific to CS42L51) and the initial few milliseconds of audio IN data will be zeroes. The CODEC can be 
     * also be initialized by the user at the start of the program at the cost of little more increased current 
     * consumption */
    //InitCirrusCodec(); APA Killed, what codec?
    
	/* USER_CODE:[CODEC] If different codec is used than the Cirrus codec (CS42L51), then
	 * Comment out the function InitCirrusCodec().
	 * Add your code for codec initialization in place of InitCirrusCodec(). 
	 * Update the UpdateCodecVolume() and UpdateCodecAttenuation() functions as required by new codec. 
	 * Update the codec.h file with the I2C address of codec and the register addresses of the new codec. */
	

	/* USER_CODE: [Active mode begins]Add your code for initializing any external peripherals which requires the PSoC 5LP 
     * to be in active mode (where all the audio components and clocks are turned on). The system is operating at its 
     * maximum operating frequency at this time. This routine initializes the codec registers with proper configuration
     * when the system is in active mode for the first time. Refer to "Active Mode Clock 44.1/48KHz schematic pages
     * for system clock details. Firmware is in "Active Mode" at this point in code until asked to enter low power mode
     * by changing audio streaming interface. The sampling frequency to which the current system clock should be
     * configured depends on the parameter to this API (newRate)*/
}
 
/*******************************************************************************
* Function Name: StartAudioComponents
********************************************************************************
* Summary:
*       This function starts components for the digital audio signal path
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void StartAudioComponents(void)
{
//	CyPins_SetPin(PSOC_CODEC_PWR_0); /* Enable this line if PSOC_CODEC_PWR pin in TopDesign is enabled */

	/* Change drive mode of I2S pins to Strong Drive at the start of audio streaming */
	#ifdef I2S_PIN_DRIVE_MODE_CHANGE_IN_IDLE_MODE		
		#ifndef MCLK_ALWAYS_ENABLED
        //PSOC_I2S_MCLK_SetDriveMode(PSOC_I2S_MCLK_DM_STRONG);
		#endif 
        //PSOC_I2S_SDTO_SetDriveMode(PSOC_I2S_SDTO_DM_STRONG);
        //PSOC_I2S_SCLK_SetDriveMode(PSOC_I2S_SCLK_DM_STRONG);
        //PSOC_I2S_LRCLK_SetDriveMode(PSOC_I2S_LRCLK_DM_STRONG);
    #endif
	
	//if(!CyPins_ReadPin(PSOC_CODEC_RST_0))
    //    {
    //        CyPins_SetPin(PSOC_CODEC_RST_0);   /* Turn on CODEC by releasing reset */
    //    }
	
	#ifdef CODEC_I2C_SUPPORTED 
    	I2C_Master_CLKDIV1_REG = I2C_DIVIDER_400KHZ_OPERATION;
	#endif
		    
    //I2S_Start();
    
    /* USER_CODE: Add your custom code to enable components which should be active when Audio streaming interface
     * is active. PLL is shutdown until SetClockRate API is called on receiving a sampling frequency set event 
	 * from the USB host */
}

/*******************************************************************************
* Function Name: StopAudioComponents
********************************************************************************
* Summary:
*       This function stops components for the digital audio signal path,
*        including the crystal and PLL.  This puts them in low-power mode.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void StopAudioComponents(void)
{
	//if(codecInit)
    //{
	    #ifdef CODEC_I2C_SUPPORTED 
		/* Mute the DAC output before configuring the clocks */
        CodecWrite.address = CODEC_DAC_OUTPUT_CTRL_REGISTER;
        CodecWrite.value = 0x73;
        WriteToSlave(CODEC_I2C_ADDRESS, &CodecWrite.address, sizeof(CodecWrite));
        
        /* shutdown the power to the codec */
        CodecWrite.address = CODEC_POWER_CTRL_REGISTER;
        CodecWrite.value = 0x01; /* Power down the codec */
        WriteToSlave(CODEC_I2C_ADDRESS, &CodecWrite.address, sizeof(CodecWrite));
        
        CyDelay(5);
        CyPins_ClearPin(PSOC_CODEC_RST_0); /* Hold CODEC in reset */
		codecInit = FALSE;
		#endif	
	//} APA Complete wipe
		
    /* Change the Master clock source to IMO and turn off PLL*/
    CyMasterClk_SetSource(CY_MASTER_SOURCE_IMO);
	CyDelayFreq(DELAY_FREQ_PARAM_VALUE_IMO);
    CyDelayUs(100);
    
	#ifndef MCLK_ALWAYS_ENABLED
    CyPLL_OUT_Stop();
    Clock_CIC_Running_Write(0u);
    FiReBuG_Stop();
	#endif 
    
    //I2S_Stop();
	
	/* Changing the I2S pins drive mode to HiZ  */
	#ifdef I2S_PIN_DRIVE_MODE_CHANGE_IN_IDLE_MODE	
		#ifndef MCLK_ALWAYS_ENABLED
        //PSOC_I2S_MCLK_SetDriveMode(PSOC_I2S_MCLK_DM_DIG_HIZ);
		#endif 
        //PSOC_I2S_SDTO_SetDriveMode(PSOC_I2S_SDTO_DM_DIG_HIZ);
        //PSOC_I2S_SCLK_SetDriveMode(PSOC_I2S_SCLK_DM_DIG_HIZ);
        //PSOC_I2S_LRCLK_SetDriveMode(PSOC_I2S_LRCLK_DM_DIG_HIZ);
    #endif
       
	#ifdef CODEC_I2C_SUPPORTED 
    /* Slow down I2C operation speed when CPU is running in idle mode */
    I2C_Master_CLKDIV1_REG = I2C_DIVIDER_25KHZ_OPERATION;
	#endif
	
	//CyPins_ClearPin(PSOC_CODEC_PWR_0);	/* Uncomment this line only if PSOC_CODEC_PWR pin in TopDesign is enabled */
	
	//codecInit = FALSE;                 /* Reset CODEC initialization flag */ APA wipe
    audioClkConfigured = FALSE;        /* Audio clock reset flag */
    setRate = FREQUENCY_NOT_SET;       /* clear the current audio sampling rate set value */
    
    /* USER_CODE: Add your custom code to shutdown components or hardware blocks which need not be active when audio
     * or MIDI interface is inactive. All the audio components, DMAs and clocks are shutdown at this point in code
     * and the system will remain in this mode until audio interface is made active or StartAudioComponents and
     * SetClockRate APIs are called by user code. Refer to "Idle Mode Clock Info" schematic page for more details 
	 * on system clock in this mode */
}

/*******************************************************************************
* Function Name: HandleSamplingFrequencyChangeRequest
********************************************************************************
* Summary:
*       This function processes the sampling frequency change request from USB
*       host and updates the accessory playback sampling frequency accordingly
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleSamplingFrequencyChangeRequest(void)
{
    /* USBFS_frequencyChanged is set by the USB component when a setup token for Sampling frequency change is received
     * It takes a sometime for the host to actually send the Out token containing the updated sampling frequency.
     * Wait for USBFS_transferState to be equal to USBFS_TRANS_STATE_IDLE to make sure the updated sampling frequency 
     * is used for setting audio clocks */
     
    if(USBFS_TRANS_STATE_IDLE == USBFS_transferState && USBFS_frequencyChanged)
    {
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
        #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
        if((!inPlaying && AUDIO_OUT_ENDPOINT == USBFS_frequencyChanged) || 
            (!outPlaying && AUDIO_IN_ENDPOINT == USBFS_frequencyChanged ))
        #endif            
        #endif 
        {
            uint32 newFrequency;
            uint8 newRate = RATE_48KHZ;
            
            newFrequency = (((uint32)USBFS_currentSampleFrequency[USBFS_frequencyChanged][2] << 16) |
                              ((uint32)USBFS_currentSampleFrequency[USBFS_frequencyChanged][1] << 8) |
                              ((uint32)USBFS_currentSampleFrequency[USBFS_frequencyChanged][0]));

			USBFS_frequencyChanged = 0;
			
            if(SAMPLING_RATE_48KHZ == newFrequency)
            {
                newRate = RATE_48KHZ;
            }
            else if(SAMPLING_RATE_44KHZ == newFrequency)
            {
                newRate = RATE_44KHZ;
            }
            //else if(SAMPLING_RATE_32KHZ == newFrequency)
            //{
            //    newRate = RATE_32KHZ;
            //} Not an option anymore
                
            if(setRate != newRate)
            {   
                setRate = newRate;
                
                if(lowPowerIdle)
                {
                    rateChangedWhileInactive = TRUE;
                }
                else
                {
                    SetClockRate(setRate);
                    rateChangedWhileInactive = FALSE;              
                }
            }
            
            clockSwitchTimer = FALSE;
        }
        #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
        #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
        else
        {
            /* If another frequency change request is received when one of the audio stream is still active, clear the
             * frequency change request */
            USBFS_frequencyChanged = 0;
        }
        #endif
        #endif
    }
        
}

/*******************************************************************************
* Function Name: HandleDigitalAudioLowPowerMode
********************************************************************************
* Summary:
*       This function switches between low and high power modes for digital audio 
*       depending on whether the audio stream from USB host is active 
*       or not.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleDigitalAudioLowPowerMode(void)
{
    /* Handle STOP/START of audio stream */
    if(FALSE == lowPowerIdle)
    {                        
        if(FALSE == lowPowerIdle && IS_USB_AUDIO_INTERFACE_NOT_ACTIVE())
        {
        	if(0 == clockSwitchTimer)
            {
                clockSwitchTimer = CLOCK_SWITCHING_TIMEOUT;
            }
            /* Both Audio Interfaces are inactive for more than 500ms -> enter low power idle mode */
            if(CLOCK_SWITCH_TIMED_OUT == clockSwitchTimer)
            {
                lowPowerIdle = TRUE;
				StopAudioComponents();            /* Changes to 24 MHz IMO for USB */
				//CyPins_ClearPin(PSOC_CODEC_RST_0); /* Hold CODEC in reset */
                //codecInit = FALSE; APA wipe
            }
        }
        
        /* USER_CODE: [High -> Low power transition] Placeholder for shutting down external hardware blocks and 
         * components before going into low power mode */
    }
    
    /* Start the Audio path components only if the audio streaming interface is active and the system is in Audio low 
	 * power mode */
    if(TRUE == lowPowerIdle)
    {
        /* Audio streaming is active on atleast one interface */
        if(TRUE == lowPowerIdle && !(IS_USB_AUDIO_INTERFACE_NOT_ACTIVE()) )
        {
            lowPowerIdle = FALSE;
			StartAudioComponents();        	   /* Turn on PLL */
			//CyPins_SetPin(PSOC_CODEC_RST_0);   /* Turn on CODEC by releasing reset */
            
            if(rateChangedWhileInactive)
            {
				SetClockRate(setRate);
                rateChangedWhileInactive = FALSE;
            }
        }
      
        /* USER_CODE: [Low -> High power transition] Placeholder for turning on external hardware blocks and 
         * components before transitioning into high power mode */
    }
}

/*******************************************************************************
* Function Name: UpdateAudioStatusUI
********************************************************************************
* Summary:
*       Updates the Audio playback status on the LEDs
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void UpdateAudioStatusUI(void)
{
   	/* Turn on the STATUS LED  when Audio Out or Audio In stream is active */

	if ( ZERO
		 #ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
		 || inPlaying 
		 #endif
		 #ifndef ENABLE_DIGITAL_AUDIO_IN_ONLY
		 || outPlaying 
		 #endif
		 )
	{
		//CyPins_ClearPin(PSOC_STATUS_LED_0); /* Turn on the Status LED */
	}
	
	else
	{
		//CyPins_SetPin(PSOC_STATUS_LED_0); /* Turn off the Status LED */
	}
}

/*******************************************************************************
* Function Name: HandleAudioInBuffer
********************************************************************************
* Summary:
*       This routine clears the audio IN stream circular buffer and the audio
*       IN endpoint memory location based on the status of the audio IN stream.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
#ifndef ENABLE_DIGITAL_AUDIO_OUT_ONLY
void HandleAudioInBuffer(void)
{
    uint16 index;
    
    if(clearInBuffer)
    {
        /* Clear the IN circular buffer - This is slow and hence part of the main loop */
        for (index = 0; index < sizeof(inBuffer); index++)
        {
            if(index<IN_AUDIOMAXPKT)
            {
                inRam[index] = 0;
            }
            inBuffer[index] = 0;
        }
        clearInBuffer = 0;
    }
}
#endif

/* [] END OF FILE */
