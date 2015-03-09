/*******************************************************************************
* File Name: C0o.h  
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

#if !defined(CY_PINS_C0o_H) /* Pins C0o_H */
#define CY_PINS_C0o_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "C0o_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 C0o__PORT == 15 && ((C0o__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    C0o_Write(uint8 value) ;
void    C0o_SetDriveMode(uint8 mode) ;
uint8   C0o_ReadDataReg(void) ;
uint8   C0o_Read(void) ;
uint8   C0o_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define C0o_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define C0o_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define C0o_DM_RES_UP          PIN_DM_RES_UP
#define C0o_DM_RES_DWN         PIN_DM_RES_DWN
#define C0o_DM_OD_LO           PIN_DM_OD_LO
#define C0o_DM_OD_HI           PIN_DM_OD_HI
#define C0o_DM_STRONG          PIN_DM_STRONG
#define C0o_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define C0o_MASK               C0o__MASK
#define C0o_SHIFT              C0o__SHIFT
#define C0o_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define C0o_PS                     (* (reg8 *) C0o__PS)
/* Data Register */
#define C0o_DR                     (* (reg8 *) C0o__DR)
/* Port Number */
#define C0o_PRT_NUM                (* (reg8 *) C0o__PRT) 
/* Connect to Analog Globals */                                                  
#define C0o_AG                     (* (reg8 *) C0o__AG)                       
/* Analog MUX bux enable */
#define C0o_AMUX                   (* (reg8 *) C0o__AMUX) 
/* Bidirectional Enable */                                                        
#define C0o_BIE                    (* (reg8 *) C0o__BIE)
/* Bit-mask for Aliased Register Access */
#define C0o_BIT_MASK               (* (reg8 *) C0o__BIT_MASK)
/* Bypass Enable */
#define C0o_BYP                    (* (reg8 *) C0o__BYP)
/* Port wide control signals */                                                   
#define C0o_CTL                    (* (reg8 *) C0o__CTL)
/* Drive Modes */
#define C0o_DM0                    (* (reg8 *) C0o__DM0) 
#define C0o_DM1                    (* (reg8 *) C0o__DM1)
#define C0o_DM2                    (* (reg8 *) C0o__DM2) 
/* Input Buffer Disable Override */
#define C0o_INP_DIS                (* (reg8 *) C0o__INP_DIS)
/* LCD Common or Segment Drive */
#define C0o_LCD_COM_SEG            (* (reg8 *) C0o__LCD_COM_SEG)
/* Enable Segment LCD */
#define C0o_LCD_EN                 (* (reg8 *) C0o__LCD_EN)
/* Slew Rate Control */
#define C0o_SLW                    (* (reg8 *) C0o__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define C0o_PRTDSI__CAPS_SEL       (* (reg8 *) C0o__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define C0o_PRTDSI__DBL_SYNC_IN    (* (reg8 *) C0o__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define C0o_PRTDSI__OE_SEL0        (* (reg8 *) C0o__PRTDSI__OE_SEL0) 
#define C0o_PRTDSI__OE_SEL1        (* (reg8 *) C0o__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define C0o_PRTDSI__OUT_SEL0       (* (reg8 *) C0o__PRTDSI__OUT_SEL0) 
#define C0o_PRTDSI__OUT_SEL1       (* (reg8 *) C0o__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define C0o_PRTDSI__SYNC_OUT       (* (reg8 *) C0o__PRTDSI__SYNC_OUT) 


#if defined(C0o__INTSTAT)  /* Interrupt Registers */

    #define C0o_INTSTAT                (* (reg8 *) C0o__INTSTAT)
    #define C0o_SNAP                   (* (reg8 *) C0o__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_C0o_H */


/* [] END OF FILE */
