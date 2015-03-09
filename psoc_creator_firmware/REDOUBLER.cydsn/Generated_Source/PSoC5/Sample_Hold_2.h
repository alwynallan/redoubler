/*******************************************************************************
* File Name: Sample_Hold_2.c
* Version 1.40
*
* Description:
*  This file contains the function prototypes and constants used in
*  the SAMPLE/TRACK AND HOLD component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SAMPLE_HOLD_Sample_Hold_2_H) 
#define CY_SAMPLE_HOLD_Sample_Hold_2_H 

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Sample_Hold_v1_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


#if(!CY_PSOC5A)
    #if(CYDEV_VARIABLE_VDDA == 1)
        #if (!defined(CY_LIB_SC_BST_CLK_EN))
            #error Component Sample_Hold_v1_40 requires cy_boot v3.30 or later
        #endif /* (!defined(CY_LIB_SC_BST_CLK_EN)) */
    #endif /* CYDEV_VARIABLE_VDDA == 1 */
#endif /* (!CY_PSOC5A) */

/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
    uint8   scCR0Reg;
    uint8   scCR1Reg;
    uint8   scCR2Reg;
}   Sample_Hold_2_backupStruct;

/* compinent init state */
extern uint8 Sample_Hold_2_initVar;


/***************************************
*        Function Prototypes 
***************************************/
    
void Sample_Hold_2_Init(void)                ;
void Sample_Hold_2_Enable(void)              ;
void Sample_Hold_2_Start(void)               ;
void Sample_Hold_2_Stop(void)                ;
void Sample_Hold_2_SetPower(uint8 power)     ;
void Sample_Hold_2_Sleep(void)               ;
void Sample_Hold_2_Wakeup(void)              ;
void Sample_Hold_2_SaveConfig(void)          ;
void Sample_Hold_2_RestoreConfig(void)       ;


/***************************************
*            API Constants        
***************************************/

/* Constants for Mixer Type */
#define Sample_Hold_2_SAMPLEANDHOLD          (0x01u)
#define Sample_Hold_2_TRACKANDHOLD           (0x02u)

/* Power constants for SetPower function */
#define Sample_Hold_2_MINPOWER               (0x00u)
#define Sample_Hold_2_LOWPOWER               (0x01u)
#define Sample_Hold_2_MEDPOWER               (0x02u)
#define Sample_Hold_2_HIGHPOWER              (0x03u)

/* Vref constats */
#define Sample_Hold_2_INTERNAL               (0x01u)
#define Sample_Hold_2_EXTERNAL               (0x02u)

/* Clock edge constats */
#define Sample_Hold_2_EDGE_NEGATIVE          (0x01u)
#define Sample_Hold_2_EDGE_POSITIVENEGATIVE  (0x02u)


/***************************************
*       Initialization Values
***************************************/

#define Sample_Hold_2_INIT_POWER             (3u)
#define Sample_Hold_2_SAMPLE_TRACK_MODE      (2u)
#define Sample_Hold_2_SAMPLE_CLOCK_EDGE      (1u)
#define Sample_Hold_2_VddaVal                (5u)
#define Sample_Hold_2_VREF_TYPE              (2u)


/***************************************
*              Registers        
***************************************/

#define Sample_Hold_2_CR0_REG                (* (reg8 *) Sample_Hold_2_SC__CR0 )
#define Sample_Hold_2_CR0_PTR                (  (reg8 *) Sample_Hold_2_SC__CR0 )
#define Sample_Hold_2_CR1_REG                (* (reg8 *) Sample_Hold_2_SC__CR1 )
#define Sample_Hold_2_CR1_PTR                (  (reg8 *) Sample_Hold_2_SC__CR1 )
#define Sample_Hold_2_CR2_REG                (* (reg8 *) Sample_Hold_2_SC__CR2 )
#define Sample_Hold_2_CR2_PTR                (  (reg8 *) Sample_Hold_2_SC__CR2 )
#define Sample_Hold_2_CLK_REG                (* (reg8 *) Sample_Hold_2_SC__CLK )  /* SC Block clk control */
#define Sample_Hold_2_CLK_PTR                (  (reg8 *) Sample_Hold_2_SC__CLK )
#define Sample_Hold_2_BSTCLK_REG             (* (reg8 *) Sample_Hold_2_SC__BST )
#define Sample_Hold_2_BSTCLK_PTR             (  (reg8 *) Sample_Hold_2_SC__BST )
#define Sample_Hold_2_PM_ACT_CFG_REG         (* (reg8 *) Sample_Hold_2_SC__PM_ACT_CFG )  /* Power manager */
#define Sample_Hold_2_PM_ACT_CFG_PTR         (  (reg8 *) Sample_Hold_2_SC__PM_ACT_CFG )
#define Sample_Hold_2_PM_STBY_CFG_REG        (* (reg8 *) Sample_Hold_2_SC__PM_STBY_CFG )  /* Power manager */
#define Sample_Hold_2_PM_STBY_CFG_PTR        (  (reg8 *) Sample_Hold_2_SC__PM_STBY_CFG )

/* Pump clock selectin register */
#define Sample_Hold_2_PUMP_CR1_REG           (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)   
#define Sample_Hold_2_PUMP_CR1_PTR           (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define Sample_Hold_2_SC_MISC_REG            (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define Sample_Hold_2_SC_MISC_PTR            (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* Power manager */
/* Active mode power enable register */
#define Sample_Hold_2_ACLK_PM_ACT_CFG_REG    (* (reg8 *) Sample_Hold_2_PM_ACT_CFG ) 
#define Sample_Hold_2_ACLK_PM_ACT_CFG_PTR    (  (reg8 *) Sample_Hold_2_PM_ACT_CFG ) 

/* Power manager */
/* Alternative Active mode power enable register */
#define Sample_Hold_2_ACLK_PM_STBY_CFG_REG   (* (reg8 *) Sample_Hold_2_PM_STBY_CFG )
#define Sample_Hold_2_ACLK_PM_STBY_CFG_PTR   (  (reg8 *) Sample_Hold_2_PM_STBY_CFG ) 

/* PM_ACT_CFG (Active Power Mode CFG Register)mask */ 
#define Sample_Hold_2_ACT_PWR_EN             Sample_Hold_2_SC__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register)mask */ 
#define Sample_Hold_2_STBY_PWR_EN            Sample_Hold_2_SC__PM_STBY_MSK /* Power enable mask */


/***************************************
*            Register Constants        
***************************************/

/* ANIF.PUMP.CR1 Constants */
#define Sample_Hold_2_PUMP_CR1_SC_CLKSEL     (0x80u)

/* SC_MISC constants */
#define Sample_Hold_2_PUMP_FORCE             (0x20u)
#define Sample_Hold_2_PUMP_AUTO              (0x10u)
#define Sample_Hold_2_DIFF_PGA_1_3           (0x02u)
#define Sample_Hold_2_DIFF_PGA_0_2           (0x01u)

/* CR0 SC/CT Control Register 0 definitions */

/* Bit Field SC_MODE_ENUM - SCxx_CR0[3:1] */
#define Sample_Hold_2_MODE_SAMPLEANDHOLD     ((uint8)(0x03u << 1u))
#define Sample_Hold_2_MODE_TRACKANDHOLD      ((uint8)(0x07u << 1u))

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_DRIVE_ENUM - SCxx_CR1[1:0] */
#define Sample_Hold_2_DRIVE_MASK             (0x03u)
#define Sample_Hold_2_DRIVE_280UA            (0x00u)
#define Sample_Hold_2_DRIVE_420UA            (0x01u)
#define Sample_Hold_2_DRIVE_530UA            (0x02u)
#define Sample_Hold_2_DRIVE_650UA            (0x03u)

/* Bit Field  SC_COMP_ENUM - SCxx_CR1[3:2] */
#define Sample_Hold_2_COMP_MASK              ((uint8)(0x03u << 2u))
#define Sample_Hold_2_COMP_3P0PF             ((uint8)(0x00u << 2u))
#define Sample_Hold_2_COMP_3P6PF             ((uint8)(0x01u << 2u))
#define Sample_Hold_2_COMP_4P35PF            ((uint8)(0x02u << 2u))
#define Sample_Hold_2_COMP_5P1PF             ((uint8)(0x03u << 2u))

/* Bit Field  SC_DIV2_ENUM - SCxx_CR1[4] */
#define Sample_Hold_2_DIV2                   ((uint8)(0x01u << 4u))
#define Sample_Hold_2_DIV2_DISABLE           ((uint8)(0x00u << 4u))
#define Sample_Hold_2_DIV2_ENABLE            ((uint8)(0x01u << 4u))

/* Bit Field  SC_GAIN_ENUM - SCxx_CR1[5] */
#define Sample_Hold_2_GAIN                   ((uint8)(0x01u << 5u))
#define Sample_Hold_2_GAIN_0DB               ((uint8)(0x00u << 5u))
#define Sample_Hold_2_GAIN_6DB               ((uint8)(0x01u << 5u))

/* CR2 SC Block Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM - SCxx_CR2[0] */
#define Sample_Hold_2_BIAS                   (0x01u)
#define Sample_Hold_2_BIAS_NORMAL            (0x00u)
#define Sample_Hold_2_BIAS_LOW               (0x01u)

/* Bit Field  SC_R20_40B_ENUM - SCxx_CR2[1] */
#define Sample_Hold_2_R20_40B                ((uint8)(0x01u << 1u))
#define Sample_Hold_2_R20_40B_40K            ((uint8)(0x00u << 1u))
#define Sample_Hold_2_R20_40B_20K            ((uint8)(0x01u << 1u))

/* Bit Field  SC_REDC_ENUM  - SCxx_CR2[3:2] */
#define Sample_Hold_2_REDC_MASK              ((uint8)(0x03u << 2u))
#define Sample_Hold_2_REDC_00                ((uint8)(0x00u << 2u))
#define Sample_Hold_2_REDC_01                ((uint8)(0x01u << 2u))
#define Sample_Hold_2_REDC_10                ((uint8)(0x02u << 2u))
#define Sample_Hold_2_REDC_11                ((uint8)(0x03u << 2u))

/* Bit Field  SC_RVAL_ENUM  - SCxx_CR2[6:4] */
#define Sample_Hold_2_RVAL_MASK              ((uint8)(0x07u << 4u))
#define Sample_Hold_2_RVAL_20K               ((uint8)(0x00u << 4u))
#define Sample_Hold_2_RVAL_30K               ((uint8)(0x01u << 4u))
#define Sample_Hold_2_RVAL_40K               ((uint8)(0x02u << 4u))
#define Sample_Hold_2_RVAL_80K               ((uint8)(0x03u << 4u))
#define Sample_Hold_2_RVAL_120K              ((uint8)(0x04u << 4u))
#define Sample_Hold_2_RVAL_250K              ((uint8)(0x05u << 4u))
#define Sample_Hold_2_RVAL_500K              ((uint8)(0x06u << 4u))
#define Sample_Hold_2_RVAL_1000K             ((uint8)(0x07u << 4u))

/* Bit Field  SC_PGA_GNDVREF_ENUM - SCxx_CR2[7] */
#define Sample_Hold_2_GNDVREF                ((uint8)(0x01u << 7u))
#define Sample_Hold_2_GNDVREF_DI             ((uint8)(0x00u << 7u))
#define Sample_Hold_2_GNDVREF_E              ((uint8)(0x01u << 7u)) 

/* SC Block Clock Control SCx.CLk */
#define Sample_Hold_2_DYN_CNTL_EN            ((uint8)(0x01u << 5u))
#define Sample_Hold_2_BYPASS_SYNC            ((uint8)(0x01u << 4u))
#define Sample_Hold_2_CLK_EN                 ((uint8)(0x01u << 3u))

/* SC Block Boost Clock Selection Register - Boost Clock Enable  SCxx_BST[3]  */
#define Sample_Hold_2_BST_CLK_EN             ((uint8)(0x01u << 3u))
#define Sample_Hold_2_BST_CLK_INDEX_MASK     (0x07u)
#define Sample_Hold_2_PM_ACT_CFG_MASK        (0x0Fu)

/* Constant for VDDA Threshold */
#define Sample_Hold_2_CYDEV_VDDA_MV               (CYDEV_VDDA_MV)
#define Sample_Hold_2_MINIMUM_VDDA_THRESHOLD_MV   (2700u)


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from SampleHold 1.40
*******************************************************************************/
/* Component's enable/disable state */
#define Sample_Hold_2_ENABLED             (0x01u)
#define Sample_Hold_2_DISABLED            (0x00u)
#define Sample_Hold_2_VDDA_THRESHOLD_MV   (3500u)
#if (CY_PSOC5A)
    /* For stop API changes mask to make the SC registers CR1 and CR2 null  */
    #define Sample_Hold_2_REG_NULL        (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_SAMPLE_HOLD_Sample_Hold_2_H */


/* [] END OF FILE */
