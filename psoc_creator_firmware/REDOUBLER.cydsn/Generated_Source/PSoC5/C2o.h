/*******************************************************************************
* File Name: C2o.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_C2o_H) /* Pins C2o_H */
#define CY_PINS_C2o_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "C2o_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 C2o__PORT == 15 && ((C2o__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    C2o_Write(uint8 value) ;
void    C2o_SetDriveMode(uint8 mode) ;
uint8   C2o_ReadDataReg(void) ;
uint8   C2o_Read(void) ;
uint8   C2o_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define C2o_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define C2o_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define C2o_DM_RES_UP          PIN_DM_RES_UP
#define C2o_DM_RES_DWN         PIN_DM_RES_DWN
#define C2o_DM_OD_LO           PIN_DM_OD_LO
#define C2o_DM_OD_HI           PIN_DM_OD_HI
#define C2o_DM_STRONG          PIN_DM_STRONG
#define C2o_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define C2o_MASK               C2o__MASK
#define C2o_SHIFT              C2o__SHIFT
#define C2o_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define C2o_PS                     (* (reg8 *) C2o__PS)
/* Data Register */
#define C2o_DR                     (* (reg8 *) C2o__DR)
/* Port Number */
#define C2o_PRT_NUM                (* (reg8 *) C2o__PRT) 
/* Connect to Analog Globals */                                                  
#define C2o_AG                     (* (reg8 *) C2o__AG)                       
/* Analog MUX bux enable */
#define C2o_AMUX                   (* (reg8 *) C2o__AMUX) 
/* Bidirectional Enable */                                                        
#define C2o_BIE                    (* (reg8 *) C2o__BIE)
/* Bit-mask for Aliased Register Access */
#define C2o_BIT_MASK               (* (reg8 *) C2o__BIT_MASK)
/* Bypass Enable */
#define C2o_BYP                    (* (reg8 *) C2o__BYP)
/* Port wide control signals */                                                   
#define C2o_CTL                    (* (reg8 *) C2o__CTL)
/* Drive Modes */
#define C2o_DM0                    (* (reg8 *) C2o__DM0) 
#define C2o_DM1                    (* (reg8 *) C2o__DM1)
#define C2o_DM2                    (* (reg8 *) C2o__DM2) 
/* Input Buffer Disable Override */
#define C2o_INP_DIS                (* (reg8 *) C2o__INP_DIS)
/* LCD Common or Segment Drive */
#define C2o_LCD_COM_SEG            (* (reg8 *) C2o__LCD_COM_SEG)
/* Enable Segment LCD */
#define C2o_LCD_EN                 (* (reg8 *) C2o__LCD_EN)
/* Slew Rate Control */
#define C2o_SLW                    (* (reg8 *) C2o__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define C2o_PRTDSI__CAPS_SEL       (* (reg8 *) C2o__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define C2o_PRTDSI__DBL_SYNC_IN    (* (reg8 *) C2o__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define C2o_PRTDSI__OE_SEL0        (* (reg8 *) C2o__PRTDSI__OE_SEL0) 
#define C2o_PRTDSI__OE_SEL1        (* (reg8 *) C2o__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define C2o_PRTDSI__OUT_SEL0       (* (reg8 *) C2o__PRTDSI__OUT_SEL0) 
#define C2o_PRTDSI__OUT_SEL1       (* (reg8 *) C2o__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define C2o_PRTDSI__SYNC_OUT       (* (reg8 *) C2o__PRTDSI__SYNC_OUT) 


#if defined(C2o__INTSTAT)  /* Interrupt Registers */

    #define C2o_INTSTAT                (* (reg8 *) C2o__INTSTAT)
    #define C2o_SNAP                   (* (reg8 *) C2o__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_C2o_H */


/* [] END OF FILE */
