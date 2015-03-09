/*******************************************************************************
* File Name: Droop_Filter.h
* Version 1.20
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the DFB Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DFB_Droop_Filter_H) /* DFB Header File */
#define CY_DFB_Droop_Filter_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component DFB_v1_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 Droop_Filter_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Droop_Filter_OPTIMIZE_ASSEMBLY      (0u)
#define Droop_Filter_INIT_INTERRUPT_MODE    (0u)
#define Droop_Filter_INIT_DMA_MODE          (1u)
#define Droop_Filter_INIT_OUT1_SOURCE       (0u)
#define Droop_Filter_INIT_OUT2_SOURCE       (0u)

/* Sizes of current DFB program */
#define Droop_Filter_DA_RAM_SIZE_CUR        (0x80u)
#define Droop_Filter_DB_RAM_SIZE_CUR        (0x80u)
#define Droop_Filter_CSA_RAM_SIZE_CUR       (0x40u)
#define Droop_Filter_CSB_RAM_SIZE_CUR       (0x40u)
#define Droop_Filter_CFSM_RAM_SIZE_CUR      (0x16u)
#define Droop_Filter_ACU_RAM_SIZE_CUR       (0x0Eu)


/***************************************
*     Data Types Definitions
***************************************/

#if (Droop_Filter_OPTIMIZE_ASSEMBLY)
    extern const uint32 CYCODE Droop_Filter_cstoreA[Droop_Filter_CSA_RAM_SIZE_CUR];
    extern const uint32 CYCODE Droop_Filter_cstoreB[Droop_Filter_CSB_RAM_SIZE_CUR];
#else
    extern const uint32 CYCODE Droop_Filter_control[Droop_Filter_CSA_RAM_SIZE_CUR];
#endif /* Droop_Filter_OPTIMIZE_ASSEMBLY */

extern const uint32 CYCODE Droop_Filter_data_a[Droop_Filter_DA_RAM_SIZE_CUR];
extern const uint32 CYCODE Droop_Filter_data_b[Droop_Filter_DB_RAM_SIZE_CUR];
extern const uint32 CYCODE Droop_Filter_cfsm[Droop_Filter_CFSM_RAM_SIZE_CUR];
extern const uint32 CYCODE Droop_Filter_acu[Droop_Filter_ACU_RAM_SIZE_CUR];

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
} Droop_Filter_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void   Droop_Filter_Init(void) ;
void   Droop_Filter_Enable(void) ;
void   Droop_Filter_Start(void) ;
void   Droop_Filter_Stop(void) ;
void   Droop_Filter_Pause(void) ;
void   Droop_Filter_Resume(void) ;
void   Droop_Filter_SetCoherency(uint8 coherencyKeyByte) ;
void   Droop_Filter_SetDalign(uint8 dalignKeyByte) ;
uint8  Droop_Filter_LoadDataRAMA(const int32 ptr[], uint32 addr[], uint8 size)
        ;
uint8  Droop_Filter_LoadDataRAMB(const int32 ptr[], uint32 addr[], uint8 size)
        ;
void   Droop_Filter_LoadInputValue(uint8 channel, int32 sample)
        ;
int32  Droop_Filter_GetOutputValue(uint8 channel) ;
void   Droop_Filter_SetInterruptMode(uint8 events) ;
uint8  Droop_Filter_GetInterruptSource(void) ;
void   Droop_Filter_ClearInterrupt(uint8 interruptMask) ;
void   Droop_Filter_SetDMAMode(uint8 events) ;
void   Droop_Filter_SetSemaphores(uint8 mask) ;
uint8  Droop_Filter_GetSemaphores(void) ;
void   Droop_Filter_ClearSemaphores(uint8 mask) ;
void   Droop_Filter_SetOutput1Source(uint8 source) ;
void   Droop_Filter_SetOutput2Source(uint8 source) ;
void   Droop_Filter_Sleep(void) ;
void   Droop_Filter_Wakeup(void) ;
void   Droop_Filter_SaveConfig(void) ;
void   Droop_Filter_RestoreConfig(void) ;

/* Macros */
#define Droop_Filter_ClearInterruptSource(event) \
do { \
    Droop_Filter_SR_REG = (uint8) (((event) & Droop_Filter_EVENT_MASK) << Droop_Filter_SR_EVENT_SHIFT); \
} while (0)


/***************************************
*           API Constants
***************************************/

/* Channel Definitions */
#define Droop_Filter_CHANNEL_A              (1u)
#define Droop_Filter_CHANNEL_B              (0u)

/* Sizes of DFB memories */
#define Droop_Filter_DA_RAM_SIZE            (0x80u)
#define Droop_Filter_DB_RAM_SIZE            (0x80u)
#define Droop_Filter_CSA_RAM_SIZE           (0x40u)
#define Droop_Filter_CSB_RAM_SIZE           (0x40u)
#define Droop_Filter_CFSM_RAM_SIZE          (0x40u)
#define Droop_Filter_ACU_RAM_SIZE           (0x10u)

#define Droop_Filter_SUCCESS                (CYRET_SUCCESS)
#define Droop_Filter_DATA_OUT_OF_RANGE      (0xFEu)
#define Droop_Filter_ADDRESS_OUT_OF_RANGE   (0xFFu)


/***************************************
*             Registers
***************************************/

/* RAM memory map offsets */
#define Droop_Filter_DA_RAM_REG             (* (reg32 *) (Droop_Filter_DFB__DPA_SRAM_DATA))
#define Droop_Filter_DA_RAM_PTR             (  (reg32 *) (Droop_Filter_DFB__DPA_SRAM_DATA))
#define Droop_Filter_DB_RAM_REG             (* (reg32 *) (Droop_Filter_DFB__DPB_SRAM_DATA))
#define Droop_Filter_DB_RAM_PTR             (  (reg32 *) (Droop_Filter_DFB__DPB_SRAM_DATA))
#define Droop_Filter_CSA_RAM_REG            (* (reg32 *) (Droop_Filter_DFB__CSA_SRAM_DATA))
#define Droop_Filter_CSA_RAM_PTR            (  (reg32 *) (Droop_Filter_DFB__CSA_SRAM_DATA))
#define Droop_Filter_CSB_RAM_REG            (* (reg32 *) (Droop_Filter_DFB__CSB_SRAM_DATA))
#define Droop_Filter_CSB_RAM_PTR            (  (reg32 *) (Droop_Filter_DFB__CSB_SRAM_DATA))
#define Droop_Filter_CFSM_RAM_REG           (* (reg32 *) (Droop_Filter_DFB__FSM_SRAM_DATA))
#define Droop_Filter_CFSM_RAM_PTR           (  (reg32 *) (Droop_Filter_DFB__FSM_SRAM_DATA))
#define Droop_Filter_ACU_RAM_REG            (* (reg32 *) (Droop_Filter_DFB__ACU_SRAM_DATA))
#define Droop_Filter_ACU_RAM_PTR            (  (reg32 *) (Droop_Filter_DFB__ACU_SRAM_DATA))

#define Droop_Filter_SEM_REG                (* (reg8 *) Droop_Filter_DFB__SEMA)
#define Droop_Filter_SEM_PTR                (  (reg8 *) Droop_Filter_DFB__SEMA)
#define Droop_Filter_CR_REG                 (* (reg8 *) Droop_Filter_DFB__CR)
#define Droop_Filter_CR_PTR                 (  (reg8 *) Droop_Filter_DFB__CR)
#define Droop_Filter_SR_REG                 (* (reg8 *) Droop_Filter_DFB__SR)
#define Droop_Filter_SR_PTR                 (  (reg8 *) Droop_Filter_DFB__SR)
#define Droop_Filter_INT_CTRL_REG           (* (reg8 *) Droop_Filter_DFB__INT_CTRL)
#define Droop_Filter_INT_CTRL_PTR           (  (reg8 *) Droop_Filter_DFB__INT_CTRL)
#define Droop_Filter_DMA_CTRL_REG           (* (reg8 *) Droop_Filter_DFB__DMA_CTRL)
#define Droop_Filter_DMA_CTRL_PTR           (  (reg8 *) Droop_Filter_DFB__DMA_CTRL)
#define Droop_Filter_RAM_DIR_REG            (* (reg8 *) Droop_Filter_DFB__RAM_DIR)
#define Droop_Filter_RAM_DIR_PTR            (  (reg8 *) Droop_Filter_DFB__RAM_DIR)

#define Droop_Filter_DALIGN_REG             (* (reg8 *) Droop_Filter_DFB__DALIGN)
#define Droop_Filter_DALIGN_PTR             (  (reg8 *) Droop_Filter_DFB__DALIGN)
#define Droop_Filter_DSI_CTRL_REG           (* (reg8 *) Droop_Filter_DFB__DSI_CTRL)
#define Droop_Filter_DSI_CTRL_PTR           (  (reg8 *) Droop_Filter_DFB__DSI_CTRL)
#define Droop_Filter_HOLDA_REG              (* (reg8 *) Droop_Filter_DFB__HOLDA)
#define Droop_Filter_HOLDA_PTR              (  (reg8 *) Droop_Filter_DFB__HOLDA)
#define Droop_Filter_HOLDAH_REG             (* (reg8 *) Droop_Filter_DFB__HOLDAH)
#define Droop_Filter_HOLDAH_PTR             (  (reg8 *) Droop_Filter_DFB__HOLDAH)
#define Droop_Filter_HOLDAM_REG             (* (reg8 *) Droop_Filter_DFB__HOLDAM)
#define Droop_Filter_HOLDAM_PTR             (  (reg8 *) Droop_Filter_DFB__HOLDAM)
#define Droop_Filter_HOLDB_REG              (* (reg8 *) Droop_Filter_DFB__HOLDB)
#define Droop_Filter_HOLDB_PTR              (  (reg8 *) Droop_Filter_DFB__HOLDB)
#define Droop_Filter_HOLDBH_REG             (* (reg8 *) Droop_Filter_DFB__HOLDBH)
#define Droop_Filter_HOLDBH_PTR             (  (reg8 *) Droop_Filter_DFB__HOLDBH)
#define Droop_Filter_HOLDBM_REG             (* (reg8 *) Droop_Filter_DFB__HOLDBM)
#define Droop_Filter_HOLDBM_PTR             (  (reg8 *) Droop_Filter_DFB__HOLDBM)
#define Droop_Filter_PM_ACT_CFG_REG         (* (reg8 *) Droop_Filter_DFB__PM_ACT_CFG)
#define Droop_Filter_PM_ACT_CFG_PTR         (  (reg8 *) Droop_Filter_DFB__PM_ACT_CFG)
#define Droop_Filter_PM_STBY_CFG_REG        (* (reg8 *) Droop_Filter_DFB__PM_STBY_CFG)
#define Droop_Filter_PM_STBY_CFG_PTR        (  (reg8 *) Droop_Filter_DFB__PM_STBY_CFG)
#define Droop_Filter_RAM_EN_REG             (* (reg8 *) Droop_Filter_DFB__RAM_EN)
#define Droop_Filter_RAM_EN_PTR             (  (reg8 *) Droop_Filter_DFB__RAM_EN)
#define Droop_Filter_STAGEA_REG             (* (reg8 *) Droop_Filter_DFB__STAGEA)
#define Droop_Filter_STAGEA_PTR             (  (reg8 *) Droop_Filter_DFB__STAGEA)
#define Droop_Filter_STAGEAH_REG            (* (reg8 *) Droop_Filter_DFB__STAGEAH)
#define Droop_Filter_STAGEAH_PTR            (  (reg8 *) Droop_Filter_DFB__STAGEAH)
#define Droop_Filter_STAGEAM_REG            (* (reg8 *) Droop_Filter_DFB__STAGEAM)
#define Droop_Filter_STAGEAM_PTR            (  (reg8 *) Droop_Filter_DFB__STAGEAM)
#define Droop_Filter_STAGEB_REG             (* (reg8 *) Droop_Filter_DFB__STAGEB)
#define Droop_Filter_STAGEB_PTR             (  (reg8 *) Droop_Filter_DFB__STAGEB)
#define Droop_Filter_STAGEBH_REG            (* (reg8 *) Droop_Filter_DFB__STAGEBH)
#define Droop_Filter_STAGEBH_PTR            (  (reg8 *) Droop_Filter_DFB__STAGEBH)
#define Droop_Filter_STAGEBM_REG            (* (reg8 *) Droop_Filter_DFB__STAGEBM)
#define Droop_Filter_STAGEBM_PTR            (  (reg8 *) Droop_Filter_DFB__STAGEBM)
#define Droop_Filter_COHER_REG              (* (reg8 *) Droop_Filter_DFB__COHER)
#define Droop_Filter_COHER_PTR              (  (reg8 *) Droop_Filter_DFB__COHER)

#define Droop_Filter_DA_RAM_LAST_ELEM_PTR   (  (reg32 *) (Droop_Filter_DFB__DPB_SRAM_DATA - 4u))
#define Droop_Filter_DB_RAM_LAST_ELEM_PTR   (  (reg32 *) (Droop_Filter_DFB__CSA_SRAM_DATA - 4u))


/***************************************
*       Register Constants
***************************************/

#define Droop_Filter_PM_ACT_MSK             (Droop_Filter_DFB__PM_ACT_MSK)
#define Droop_Filter_PM_STBY_MSK            (Droop_Filter_DFB__PM_STBY_MSK)

#define Droop_Filter_RUN_MASK               (0x01u)
#define Droop_Filter_CORECLK_DISABLE        (0x04u)
#define Droop_Filter_RAM_DIR_BUS            (0x3Fu)
#define Droop_Filter_RAM_DIR_DFB            (0x00u)
#define Droop_Filter_RAM_DPA_DIR            (0x10u)
#define Droop_Filter_RAM_DPB_DIR            (0x20u)

/* Mask for bits within DFB Coherency Register */
#define Droop_Filter_STGA_KEY_SHIFT         (0x00u)
#define Droop_Filter_STGB_KEY_SHIFT         (0x02u)
#define Droop_Filter_HOLDA_KEY_SHIFT        (0x04u)
#define Droop_Filter_HOLDB_KEY_SHIFT        (0x06u)

#define Droop_Filter_STGA_KEY_LOW           ((uint8) (0x00u << Droop_Filter_STGA_KEY_SHIFT))
#define Droop_Filter_STGA_KEY_MID           ((uint8) (0x01u << Droop_Filter_STGA_KEY_SHIFT))
#define Droop_Filter_STGA_KEY_HIGH          ((uint8) (0x02u << Droop_Filter_STGA_KEY_SHIFT))
#define Droop_Filter_STGB_KEY_LOW           ((uint8) (0x00u << Droop_Filter_STGB_KEY_SHIFT))
#define Droop_Filter_STGB_KEY_MID           ((uint8) (0x01u << Droop_Filter_STGB_KEY_SHIFT))
#define Droop_Filter_STGB_KEY_HIGH          ((uint8) (0x02u << Droop_Filter_STGB_KEY_SHIFT))
#define Droop_Filter_HOLDA_KEY_LOW          ((uint8) (0x00u << Droop_Filter_HOLDA_KEY_SHIFT))
#define Droop_Filter_HOLDA_KEY_MID          ((uint8) (0x01u << Droop_Filter_HOLDA_KEY_SHIFT))
#define Droop_Filter_HOLDA_KEY_HIGH         ((uint8) (0x02u << Droop_Filter_HOLDA_KEY_SHIFT))
#define Droop_Filter_HOLDB_KEY_LOW          ((uint8) (0x00u << Droop_Filter_HOLDB_KEY_SHIFT))
#define Droop_Filter_HOLDB_KEY_MID          ((uint8) (0x01u << Droop_Filter_HOLDB_KEY_SHIFT))
#define Droop_Filter_HOLDB_KEY_HIGH         ((uint8) (0x02u << Droop_Filter_HOLDB_KEY_SHIFT))

/* Mask for bits within DFB Data Alignment Register */
#define Droop_Filter_STGA_DALIGN_SHIFT      (0x00u)
#define Droop_Filter_STGB_DALIGN_SHIFT      (0x01u)
#define Droop_Filter_HOLDA_DALIGN_SHIFT     (0x02u)
#define Droop_Filter_HOLDB_DALIGN_SHIFT     (0x03u)

#define Droop_Filter_STGA_DALIGN_LOW        ((uint8) (0x00u << Droop_Filter_STGA_DALIGN_SHIFT))
#define Droop_Filter_STGA_DALIGN_HIGH       ((uint8) (0x01u << Droop_Filter_STGA_DALIGN_SHIFT))
#define Droop_Filter_STGB_DALIGN_LOW        ((uint8) (0x00u << Droop_Filter_STGB_DALIGN_SHIFT))
#define Droop_Filter_STGB_DALIGN_HIGH       ((uint8) (0x01u << Droop_Filter_STGB_DALIGN_SHIFT))
#define Droop_Filter_HOLDA_DALIGN_LOW       ((uint8) (0x00u << Droop_Filter_HOLDA_DALIGN_SHIFT))
#define Droop_Filter_HOLDA_DALIGN_HIGH      ((uint8) (0x01u << Droop_Filter_HOLDA_DALIGN_SHIFT))
#define Droop_Filter_HOLDB_DALIGN_LOW       ((uint8) (0x00u << Droop_Filter_HOLDB_DALIGN_SHIFT))
#define Droop_Filter_HOLDB_DALIGN_HIGH      ((uint8) (0x01u << Droop_Filter_HOLDB_DALIGN_SHIFT))

/* Mask for bits within DFB Interrupt Control and Status Registers */
#define Droop_Filter_SEM_MASK               (0x07u)
#define Droop_Filter_SEM_ENABLE_SHIFT       (0x04u)
#define Droop_Filter_EVENT_MASK             (0x1Fu)
#define Droop_Filter_SR_EVENT_SHIFT         (0x03u)

#define Droop_Filter_HOLDA_SHIFT            (0x00u)
#define Droop_Filter_HOLDB_SHIFT            (0x01u)
#define Droop_Filter_SEMA0_SHIFT            (0x02u)
#define Droop_Filter_SEMA1_SHIFT            (0x03u)
#define Droop_Filter_SEMA2_SHIFT            (0x04u)

#define Droop_Filter_HOLDA                  ((uint8) (0x01u << Droop_Filter_HOLDA_SHIFT))
#define Droop_Filter_HOLDB                  ((uint8) (0x01u << Droop_Filter_HOLDB_SHIFT))
#define Droop_Filter_SEMA0                  ((uint8) (0x01u << Droop_Filter_SEMA0_SHIFT))
#define Droop_Filter_SEMA1                  ((uint8) (0x01u << Droop_Filter_SEMA1_SHIFT))
#define Droop_Filter_SEMA2                  ((uint8) (0x01u << Droop_Filter_SEMA2_SHIFT))

/* Mask for bits within DFB DMAREQ Control Register */
#define Droop_Filter_DMA_CTRL_MASK          (0x0Fu)
#define Droop_Filter_DMAREQ1_DISABLED       (0x00u)
#define Droop_Filter_DMAREQ1_HOLDA          (0x01u)
#define Droop_Filter_DMAREQ1_SEM0           (0x02u)
#define Droop_Filter_DMAREQ1_SEM1           (0x03u)
#define Droop_Filter_DMAREQ2_DISABLED       (0x00u)
#define Droop_Filter_DMAREQ2_HOLDB          (0x04u)
#define Droop_Filter_DMAREQ2_SEM0           (0x08u)
#define Droop_Filter_DMAREQ2_SEM1           (0x0Cu)

/* Mask for bits within DFB Semaphore Register */
#define Droop_Filter_SEMAPHORE0             (0x01u)
#define Droop_Filter_SEMAPHORE1             (0x02u)
#define Droop_Filter_SEMAPHORE2             (0x04u)

/* Mask for bits within Global Control Register */
#define Droop_Filter_DFB_RUN                (0x00u)
#define Droop_Filter_SEM0                   (0x01u)
#define Droop_Filter_SEM1                   (0x02u)
#define Droop_Filter_DFB_INTR               (0x03u)
#define Droop_Filter_SEM2                   (0x00u)
#define Droop_Filter_DPSIGN                 (0x04u)
#define Droop_Filter_DPTHRESH               (0x08u)
#define Droop_Filter_DPEQ                   (0x0Cu)
#define Droop_Filter_DFB_GBL1_OUT_MASK      (0xFCu)
#define Droop_Filter_DFB_GBL2_OUT_MASK      (0xF3u)

#endif /* End DFB Header File */


/* [] END OF FILE */

