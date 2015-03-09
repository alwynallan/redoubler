/*******************************************************************************
* File Name: ByteSwap_Tx.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values and API definition for the 
*  I2S Component
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(ByteSwap_Tx_H)
#define ByteSwap_Tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

void  ByteSwap_Tx_Start(void);
void  ByteSwap_Tx_Stop(void)                       ;


/***************************************
*             Registers                 
***************************************/

#define ByteSwap_Tx_CONTROL_REG   			        (* (reg8 *) ByteSwap_Tx_ControlReg__CONTROL_REG)
#define ByteSwap_Tx_CONTROL_PTR   			        (  (reg8 *) ByteSwap_Tx_ControlReg__CONTROL_REG)

#define ByteSwap_Tx_AUX_CONTROL_REG                (* (reg8 *) ByteSwap_Tx_dp_ByteSwap_u0__DP_AUX_CTL_REG)
#define ByteSwap_Tx_AUX_CONTROL_PTR                (  (reg8 *) ByteSwap_Tx_dp_ByteSwap_u0__DP_AUX_CTL_REG)

#define ByteSwap_Tx_INPUT_FIFO_0_CLR               (0x01u)
#define ByteSwap_Tx_OUTPUT_FIFO_1_CLR              (0x02u) 
#define ByteSwap_Tx_INPUT_FIFO_LEVEL_HALF_EMPTY    (0x0Cu)

#define ByteSwap_Tx_EN                             (0x01u)
#define ByteSwap_Tx_RES_CTRL_16                    (0x02u)


#endif

//[] END OF FILE
