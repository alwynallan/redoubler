/*******************************************************************************
* File Name: I2S.c
* Version 2.40
*
* Description:
*  This file contains the setup, control and status commands for the I2S
*  component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2S.h"

uint8 I2S_initVar = 0u;


/*******************************************************************************
* Function Name: I2S_Enable
********************************************************************************
*
* Summary:
*  Enables I2S interface.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void I2S_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    I2S_AUX_CONTROL_REG |= I2S_CNTR7_EN;
    CyExitCriticalSection(enableInterrupts);

    I2S_CONTROL_REG |= I2S_EN;
}


/*******************************************************************************
* Function Name: I2S_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void I2S_Init(void) 
{
    /* Writes Tx and/or Rx interrupt source values provided for customizer */
    #if(I2S_TX_DIRECTION_ENABLE)
        I2S_SetTxInterruptMode(I2S_DEFAULT_TX_INT_SOURCE);
    #endif /* (I2S_TX_DIRECTION_ENABLE) */
    
    #if(I2S_RX_DIRECTION_ENABLE)
        I2S_SetRxInterruptMode(I2S_DEFAULT_RX_INT_SOURCE);
    #endif /* (I2S_RX_DIRECTION_ENABLE) */
}


/*******************************************************************************
* Function Name: I2S_Start
********************************************************************************
*
* Summary:
*  Starts the I2S interface.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  I2S_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void I2S_Start(void) 
{
    /* Writes Tx and/or Rx interrupt source values provided for customizer */
    if(0u == I2S_initVar)
    {
        I2S_Init();
        I2S_initVar = 1u;
    }

    I2S_Enable();
}


/*******************************************************************************
* Function Name: I2S_Stop
********************************************************************************
*
* Summary:
*  Disables the I2S interface.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void I2S_Stop(void) 
{
    uint8 enableInterrupts;

    I2S_CONTROL_REG &= ((uint8) ~I2S_EN);

    enableInterrupts = CyEnterCriticalSection();
    I2S_AUX_CONTROL_REG &= ((uint8) ~I2S_CNTR7_EN);
    CyExitCriticalSection(enableInterrupts);

    /* Set counter to zero to force reload when component is enabled */
    I2S_CNT7_COUNT_REG = I2S_CNTR7_COUNT_0;

    #if(I2S_TX_DIRECTION_ENABLE)
        I2S_DisableTx();
        I2S_ClearTxFIFO();
    #endif /* (I2S_TX_DIRECTION_ENABLE) */
    
    #if(I2S_RX_DIRECTION_ENABLE)
        I2S_DisableRx();
        I2S_ClearRxFIFO();
    #endif /* (I2S_RX_DIRECTION_ENABLE) */
}


#if(I2S_TX_DIRECTION_ENABLE)
    /*******************************************************************************
    * Function Name: I2S_EnableTx
    ********************************************************************************
    *
    * Summary:
    *  Enables the Tx direction of the I2S interface.  At the next word
    *  select falling edge transmission will begin.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_EnableTx(void) 
    {
        uint8 enableInterrupts;

        I2S_CONTROL_REG |= I2S_TX_EN;

        enableInterrupts = CyEnterCriticalSection();
        I2S_TX_STATUS_AUX_CONTROL_REG |= I2S_TX_INT_EN;
        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: I2S_DisableTx
    ********************************************************************************
    *
    * Summary:
    *  Disables the Tx direction of the I2S interface.  At the next word
    *  select falling edge transmission of data will stop and a constant 0 value
    *  will be transmitted.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_DisableTx(void) 
    {
        uint8 enableInterrupts;

        I2S_CONTROL_REG &= ((uint8) ~I2S_TX_EN);

        enableInterrupts = CyEnterCriticalSection();
        I2S_TX_STATUS_AUX_CONTROL_REG &= ((uint8) ~I2S_TX_INT_EN);
        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: I2S_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt source for the I2S Tx direction interrupt.
    *
    * Parameters:
    *  Byte containing the constant for the selected interrupt sources.
    *   I2S_TX_FIFO_UNDEFLOW
    *   I2S_TX_FIFO_0_NOT_FULL
    *   I2S_TX_FIFO_1_NOT_FULL
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2S_SetTxInterruptMode(uint8 interruptSource)
                                                                
    {
        I2S_TX_STATUS_MASK_REG = (interruptSource & I2S_TX_ST_MASK);
    }


    /*******************************************************************************
    * Function Name: I2S_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns state in the I2S Tx status register.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  State of the I2S Tx status register
    *   I2S_RET_TX_FIFO_UNDERFLOW (Clear on Read)
    *   I2S_RET_TX_FIFO_0_NOT_FULL
    *   I2S_RET_TX_FIFO_1_NOT_FULL
    *
    * Side Effects:
    *  Clears the bits of I2S Tx status register that are Clear on Read.
    *
    *******************************************************************************/
    uint8 I2S_ReadTxStatus(void) 
    {
        return(I2S_TX_STATUS_REG & I2S_TX_ST_MASK);
    }


    /*******************************************************************************
    * Function Name: I2S_WriteByte
    ********************************************************************************
    *
    * Summary:
    *  Writes a single byte into the Tx FIFO.
    *
    * Parameters:
    *  wrData: Byte containing the data to transmit.
    *  wordSelect: Indicates to write to the Left (0) or Right (1) channel.  In the
    *              interleaved mode this parameter is ignored
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void I2S_WriteByte(uint8 wrData, uint8 wordSelect) 
    {
        #if(I2S_TX_DATA_INTERLEAVED)
            if(0u != wordSelect)
            {
                /* Suppress compiler warning */
            }
            
            I2S_TX_FIFO_0_REG = wrData;
            
        #else
            if(I2S_TX_LEFT_CHANNEL == wordSelect)
            {
                I2S_TX_FIFO_0_REG = wrData;
            }
            else
            {
                I2S_TX_FIFO_1_REG = wrData;
            }
            
        #endif /* (I2S_TX_DATA_INTERLEAVED) */
    }


    /*******************************************************************************
    * Function Name: I2S_ClearTxFIFO
    ********************************************************************************
    *
    * Summary:
    *  Clears out the Tx FIFO.  Any data present in the FIFO will not be
    *  sent. This call should be made only when the Tx direction is disabled.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_ClearTxFIFO(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        I2S_TX_AUX_CONTROL_REG |= ((uint8)  I2S_TX_FIFO_0_CLR);
        I2S_TX_AUX_CONTROL_REG &= ((uint8) ~I2S_TX_FIFO_0_CLR);

        #if(I2S_TX_DATA_SEPARATED)
            I2S_TX_AUX_CONTROL_REG |= ((uint8)  I2S_TX_FIFO_1_CLR);
            I2S_TX_AUX_CONTROL_REG &= ((uint8) ~I2S_TX_FIFO_1_CLR);
        #endif /* (I2S_TX_DATA_SEPARATED) */
        CyExitCriticalSection(enableInterrupts);
    }

#endif /* (I2S_TX_DIRECTION_ENABLE) */


#if(I2S_RX_DIRECTION_ENABLE)
    /*******************************************************************************
    * Function Name: I2S_EnableRx
    ********************************************************************************
    *
    * Summary:
    *  Enables the Rx direction of the I2S interface.  At the next word
    *  select falling edge reception of data will begin.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_EnableRx(void) 
    {
        uint8 enableInterrupts;

        I2S_CONTROL_REG |= I2S_RX_EN;

        enableInterrupts = CyEnterCriticalSection();
        I2S_RX_STATUS_AUX_CONTROL_REG |= I2S_RX_INT_EN;
        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: I2S_DisableRx
    ********************************************************************************
    *
    * Summary:
    *  Disables the Rx direction of the I2S interface.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_DisableRx(void) 
    {
        uint8 enableInterrupts;

        I2S_CONTROL_REG &= ((uint8) ~I2S_RX_EN);

        enableInterrupts = CyEnterCriticalSection();
        I2S_RX_STATUS_AUX_CONTROL_REG &= ((uint8) ~I2S_RX_INT_EN);
        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: I2S_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt source for the I2S Rx direction interrupt.
    *
    * Parameters:
    *  Byte containing the constant for the selected interrupt sources.
    *   I2S_RX_FIFO_OVERFLOW
    *   I2S_RX_FIFO_0_NOT_EMPTY
    *   I2S_RX_FIFO_1_NOT_EMPTY
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_SetRxInterruptMode(uint8 interruptSource)
                                                                
    {
        I2S_RX_STATUS_MASK_REG = (interruptSource & I2S_RX_ST_MASK);
    }


    /*******************************************************************************
    * Function Name: I2S_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns state in the I2S Rx status register.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  State of the I2S Rx status register
    *   I2S_RET_RX_FIFO_OVERFLOW (Clear on Read)
    *   I2S_RET_RX_FIFO_0_NOT_EMPTY
    *   I2S_RET_RX_FIFO_1_NOT_EMPTY
    *
    * Side Effects:
    *  Clears the bits of I2S Rx status register that are Clear on Read.
    *
    *******************************************************************************/
    uint8 I2S_ReadRxStatus(void) 
    {
        return(I2S_RX_STATUS_REG & I2S_RX_ST_MASK);
    }


    /*******************************************************************************
    * Function Name: I2S_ReadByte
    ********************************************************************************
    *
    * Summary:
    *  Returns a single byte from the Rx FIFO.
    *
    * Parameters:
    *  wordSelect: Indicates to read from the Left (0) or Right (1) channel. In the
    *              interleaved mode this parameter is ignored.
    *
    * Return:
    *  Byte containing the data received.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 I2S_ReadByte(uint8 wordSelect) 
    {
        uint8 result;
        
        #if(I2S_RX_DATA_INTERLEAVED)
            if(0u != wordSelect)
            {
                /* Suppress compiler warning */
            }
            
            result = I2S_RX_FIFO_0_REG;
            
        #else
            if(I2S_RX_LEFT_CHANNEL == wordSelect)
            {
                result = I2S_RX_FIFO_0_REG;
            }
            else
            {
                result = I2S_RX_FIFO_1_REG;
            }
            
        #endif /* (I2S_RX_DATA_INTERLEAVED) */
        
        return(result);
    }


    /*******************************************************************************
    * Function Name: I2S_ClearRxFIFO
    ********************************************************************************
    *
    * Summary:
    *  Clears out the Rx FIFO.  Any data present in the FIFO will be lost.
    *  This call should be made only when the Rx direction is disabled.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2S_ClearRxFIFO(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        I2S_RX_AUX_CONTROL_REG |= ((uint8)  I2S_RX_FIFO_0_CLR);
        I2S_RX_AUX_CONTROL_REG &= ((uint8) ~I2S_RX_FIFO_0_CLR);

        #if(I2S_RX_DATA_SEPARATED)
            I2S_RX_AUX_CONTROL_REG |= ((uint8)  I2S_RX_FIFO_1_CLR);
            I2S_RX_AUX_CONTROL_REG &= ((uint8) ~I2S_RX_FIFO_1_CLR);
        #endif /* (I2S_RX_DATA_SEPARATED) */
        CyExitCriticalSection(enableInterrupts);
    }
#endif /* (I2S_RX_DIRECTION_ENABLE) */


/* [] END OF FILE */
