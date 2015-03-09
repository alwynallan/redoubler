/*******************************************************************************
* File Name: I2S.h
* Version 2.40
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  I2S Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_I2S_I2S_H)
#define CY_I2S_I2S_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component I2S_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define I2S_DIRECTION              (2u)
#define I2S_RX_DATA_INTERLEAVING   (1u)
#define I2S_TX_DATA_INTERLEAVING   (1u)

/* Direction enum. */
#define I2S_DIR_RX         (0x01u)
#define I2S_DIR_TX         (0x02u)
#define I2S_DIR_RX_AND_TX  (0x03u)

#define I2S_RX_DIRECTION_ENABLE    (0u != (I2S_DIR_RX & I2S_DIRECTION))
#define I2S_TX_DIRECTION_ENABLE    (0u != (I2S_DIR_TX & I2S_DIRECTION))

#define I2S_TX_DATA_SEPARATED      (0u == I2S_TX_DATA_INTERLEAVING)
#define I2S_TX_DATA_INTERLEAVED    (0u != I2S_TX_DATA_INTERLEAVING)

#define I2S_RX_DATA_SEPARATED      (0u == I2S_RX_DATA_INTERLEAVING)
#define I2S_RX_DATA_INTERLEAVED    (0u != I2S_RX_DATA_INTERLEAVING)

/* Data Interleaving enum. */
#define I2S_DATA_SEPARATE      (0x00u)
#define I2S_DATA_INTERLEAVED   (0x01u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 CtrlReg;

    #if(CY_UDB_V0)
        uint8 Cnt7Period;

        #if(I2S_TX_DIRECTION_ENABLE)
            uint8 TxIntMask;
        #endif /* (I2S_TX_DIRECTION_ENABLE) */
        
        #if(I2S_RX_DIRECTION_ENABLE)
            uint8 RxIntMask;
        #endif /* (I2S_RX_DIRECTION_ENABLE) */
    #endif     /* (CY_UDB_V0) */
} I2S_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  I2S_Start(void)                  ;
void  I2S_Stop(void)                   ;
void  I2S_Sleep(void)                  ;
void  I2S_Wakeup(void)                 ;
void  I2S_Enable(void)                 ;
void  I2S_Init(void)                   ;
void  I2S_SaveConfig(void)             ;
void  I2S_RestoreConfig(void)          ;

#if(I2S_TX_DIRECTION_ENABLE)
    void   I2S_EnableTx(void)          ;
    void   I2S_DisableTx(void)         ;
    void   I2S_WriteByte(uint8 wrData, uint8 wordSelect) \
                                                    ;
    void   I2S_ClearTxFIFO(void)       ;
    void   I2S_SetTxInterruptMode(uint8 interruptSource) \
                                                    ;
    uint8  I2S_ReadTxStatus(void)      ;
#endif /* (I2S_TX_DIRECTION_ENABLE) */

#if(I2S_RX_DIRECTION_ENABLE)
    void   I2S_EnableRx(void)          ;
    void   I2S_DisableRx(void)         ;
    void   I2S_SetRxInterruptMode(uint8 interruptSource) \
                                                    ;
    uint8  I2S_ReadRxStatus(void)      ;
    uint8  I2S_ReadByte(uint8 wordSelect) \
                                                    ;
    void   I2S_ClearRxFIFO(void)       ;
#endif /* (I2S_RX_DIRECTION_ENABLE) */


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 I2S_initVar;


/***************************************
*           API Constants
***************************************/

#if(I2S_TX_DIRECTION_ENABLE)
    #define I2S_TX_LEFT_CHANNEL           (0x00u)
    #define I2S_TX_RIGHT_CHANNEL          (0x01u)

    #define I2S_TX_FIFO_UNDERFLOW         (0x01u)
    #define I2S_TX_FIFO_0_NOT_FULL        (0x02u)
    #define I2S_TX_FIFO_1_NOT_FULL        (0x04u)

    #define I2S_RET_TX_FIFO_UNDERFLOW     (0x01u)
    #define I2S_RET_TX_FIFO_0_NOT_FULL    (0x02u)
    #define I2S_RET_TX_FIFO_1_NOT_FULL    (0x04u)
#endif /* (I2S_TX_DIRECTION_ENABLE) */

#if(I2S_RX_DIRECTION_ENABLE)
    #define I2S_RX_FIFO_OVERFLOW          (0x01u)
    #define I2S_RX_FIFO_0_NOT_EMPTY       (0x02u)
    #define I2S_RX_FIFO_1_NOT_EMPTY       (0x04u)

    #define I2S_RET_RX_FIFO_OVERFLOW      (0x01u)
    #define I2S_RET_RX_FIFO_0_NOT_EMPTY   (0x02u)
    #define I2S_RET_RX_FIFO_1_NOT_EMPTY   (0x04u)
    #define I2S_RX_LEFT_CHANNEL           (0x00u)
#endif /* (I2S_RX_DIRECTION_ENABLE) */

#define I2S_WORD_SEL_MASK                 (0x01u)
#define I2S_DISABLED                      (0x00u)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Default interrupt source */
#define I2S_DEFAULT_INT_SOURCE     (0u)

#define I2S_RX_INT_SOURCE_SHIFT    (3u)

#define I2S_DEFAULT_RX_INT_SOURCE  ((uint8) (I2S_DEFAULT_INT_SOURCE >> \
                                                                                  I2S_RX_INT_SOURCE_SHIFT))
#define I2S_DEFAULT_TX_INT_SOURCE  (I2S_DEFAULT_INT_SOURCE & I2S_TX_ST_MASK)

/* Word Select period. Set as ((period * 2) - 1): multiply by two because of 2X input clock */
#define I2S_WORD_SELECT            (64u)
#define I2S_DEFAULT_WS_PERIOD      (((uint8) (I2S_WORD_SELECT << 1u)) - 1u)


/***************************************
*             Registers
***************************************/

#define I2S_CONTROL_REG       (* (reg8 *) I2S_Sync_CtlReg__CONTROL_REG)
#define I2S_CONTROL_PTR       (  (reg8 *) I2S_Sync_CtlReg__CONTROL_REG)

#define I2S_AUX_CONTROL_REG   (* (reg8 *) I2S_BitCounter__CONTROL_AUX_CTL_REG)
#define I2S_AUX_CONTROL_PTR   (  (reg8 *) I2S_BitCounter__CONTROL_AUX_CTL_REG)

#define I2S_CNT7_PERIOD_REG   (* (reg8 *) I2S_BitCounter__PERIOD_REG)
#define I2S_CNT7_PERIOD_PTR   (  (reg8 *) I2S_BitCounter__PERIOD_REG)

#define I2S_CNT7_COUNT_REG    (* (reg8 *) I2S_BitCounter__COUNT_REG)
#define I2S_CNT7_COUNT_PTR    (  (reg8 *) I2S_BitCounter__COUNT_REG)

#if(I2S_TX_DIRECTION_ENABLE)
    #define I2S_TX_REG                     (* (reg8 *) I2S_Tx_dpTx_u0__A0_REG)
    #define I2S_TX_PTR                     (  (reg8 *) I2S_Tx_dpTx_u0__A0_REG)

    #define I2S_TX_FIFO_0_REG              (* (reg8 *) I2S_Tx_dpTx_u0__F0_REG)
    #define I2S_TX_FIFO_0_PTR              (  (reg8 *) I2S_Tx_dpTx_u0__F0_REG)

    #define I2S_TX_FIFO_1_REG              (* (reg8 *) I2S_Tx_dpTx_u0__F1_REG)
    #define I2S_TX_FIFO_1_PTR              (  (reg8 *) I2S_Tx_dpTx_u0__F1_REG)

    #define I2S_TX_AUX_CONTROL_REG         (* (reg8 *) I2S_Tx_dpTx_u0__DP_AUX_CTL_REG)
    #define I2S_TX_AUX_CONTROL_PTR         (  (reg8 *) I2S_Tx_dpTx_u0__DP_AUX_CTL_REG)

    #define I2S_TX_STATUS_REG              (* (reg8 *) I2S_Tx_TxStsReg__STATUS_REG)
    #define I2S_TX_STATUS_PTR              (  (reg8 *) I2S_Tx_TxStsReg__STATUS_REG)

    #define I2S_TX_STATUS_MASK_REG         (* (reg8 *) I2S_Tx_TxStsReg__MASK_REG)
    #define I2S_TX_STATUS_MASK_PTR         (  (reg8 *) I2S_Tx_TxStsReg__MASK_REG)

    #define I2S_TX_STATUS_AUX_CONTROL_REG  (* (reg8 *) I2S_Tx_TxStsReg__STATUS_AUX_CTL_REG)
    #define I2S_TX_STATUS_AUX_CONTROL_PTR  (  (reg8 *) I2S_Tx_TxStsReg__STATUS_AUX_CTL_REG)
#endif /* (I2S_TX_DIRECTION_ENABLE) */

#if(I2S_RX_DIRECTION_ENABLE)
    #define I2S_RX_REG                     (* (reg8 *) I2S_Rx_dpRx_u0__A0_REG)
    #define I2S_RX_PTR                     (  (reg8 *) I2S_Rx_dpRx_u0__A0_REG)

    #define I2S_RX_FIFO_0_REG              (* (reg8 *) I2S_Rx_dpRx_u0__F0_REG)
    #define I2S_RX_FIFO_0_PTR              (  (reg8 *) I2S_Rx_dpRx_u0__F0_REG)

    #define I2S_RX_FIFO_1_REG              (* (reg8 *) I2S_Rx_dpRx_u0__F1_REG)
    #define I2S_RX_FIFO_1_PTR              (  (reg8 *) I2S_Rx_dpRx_u0__F1_REG)

    #define I2S_RX_AUX_CONTROL_REG         (* (reg8 *) I2S_Rx_dpRx_u0__DP_AUX_CTL_REG)
    #define I2S_RX_AUX_CONTROL_PTR         (  (reg8 *) I2S_Rx_dpRx_u0__DP_AUX_CTL_REG)

    #define I2S_RX_STATUS_REG              (* (reg8 *) I2S_Rx_RxStsReg__STATUS_REG)
    #define I2S_RX_STATUS_PTR              (  (reg8 *) I2S_Rx_RxStsReg__STATUS_REG)

    #define I2S_RX_STATUS_MASK_REG         (* (reg8 *) I2S_Rx_RxStsReg__MASK_REG)
    #define I2S_RX_STATUS_MASK_PTR         (  (reg8 *) I2S_Rx_RxStsReg__MASK_REG)

    #define I2S_RX_STATUS_AUX_CONTROL_REG  (* (reg8 *) I2S_Rx_RxStsReg__STATUS_AUX_CTL_REG)
    #define I2S_RX_STATUS_AUX_CONTROL_PTR  (  (reg8 *) I2S_Rx_RxStsReg__STATUS_AUX_CTL_REG)
#endif /* (I2S_RX_DIRECTION_ENABLE) */


/***************************************
*       Register Constants
***************************************/

/* Control register definitions */
#define I2S_TX_EN          (0x01u)
#define I2S_RX_EN          (0x02u)
#define I2S_EN             (0x04u)

/* TX direction definitions */
#define I2S_TX_ST_MASK     (0x07u)

#define I2S_TX_FIFO_0_CLR  (0x01u)
#define I2S_TX_FIFO_1_CLR  (0x02u)

#define I2S_TX_INT_EN      (0x10u)

/* RX direction definitions */
#define I2S_RX_ST_MASK     (0x07u)

#define I2S_RX_FIFO_0_CLR  (0x01u)
#define I2S_RX_FIFO_1_CLR  (0x02u)

#define I2S_RX_INT_EN      (0x10u)

/* Enables 7-bit counter in aux */
#define I2S_CNTR7_EN       (0x20u)
#define I2S_CNTR7_COUNT_0  (0x00u)


/***************************************
*       Macros
***************************************/

#define I2S_IS_ENABLE      (0u != (I2S_CONTROL_REG & I2S_EN))


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from I2S 2.40 
 */

/* Derection enum. */
#define I2S__TX        (I2S_DIR_TX)
#define I2S__RX        (I2S_DIR_RX)
#define I2S__RX_AND_TX (I2S_DIR_RX_AND_TX)

/* Data interleaving enum. */
#define I2S__SEPARATE      (I2S_DATA_SEPARATE)
#define I2S__INTERLEAVED   (I2S_DATA_INTERLEAVED)

#endif /* CY_I2S_I2S_H */


/* [] END OF FILE */
