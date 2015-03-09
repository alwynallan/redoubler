/*******************************************************************************
* File Name: C1o.h  
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

#if !defined(CY_PINS_C1o_H) /* Pins C1o_H */
#define CY_PINS_C1o_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "C1o_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 C1o__PORT == 15 && ((C1o__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    C1o_Write(uint8 value) ;
void    C1o_SetDriveMode(uint8 mode) ;
uint8   C1o_ReadDataReg(void) ;
uint8   C1o_Read(void) ;
uint8   C1o_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define C1o_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define C1o_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define C1o_DM_RES_UP          PIN_DM_RES_UP
#define C1o_DM_RES_DWN         PIN_DM_RES_DWN
#define C1o_DM_OD_LO           PIN_DM_OD_LO
#define C1o_DM_OD_HI           PIN_DM_OD_HI
#define C1o_DM_STRONG          PIN_DM_STRONG
#define C1o_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define C1o_MASK               C1o__MASK
#define C1o_SHIFT              C1o__SHIFT
#define C1o_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define C1o_PS                     (* (reg8 *) C1o__PS)
/* Data Register */
#define C1o_DR                     (* (reg8 *) C1o__DR)
/* Port Number */
#define C1o_PRT_NUM                (* (reg8 *) C1o__PRT) 
/* Connect to Analog Globals */                                                  
#define C1o_AG                     (* (reg8 *) C1o__AG)                       
/* Analog MUX bux enable */
#define C1o_AMUX                   (* (reg8 *) C1o__AMUX) 
/* Bidirectional Enable */                                                        
#define C1o_BIE                    (* (reg8 *) C1o__BIE)
/* Bit-mask for Aliased Register Access */
#define C1o_BIT_MASK               (* (reg8 *) C1o__BIT_MASK)
/* Bypass Enable */
#define C1o_BYP                    (* (reg8 *) C1o__BYP)
/* Port wide control signals */                                                   
#define C1o_CTL                    (* (reg8 *) C1o__CTL)
/* Drive Modes */
#define C1o_DM0                    (* (reg8 *) C1o__DM0) 
#define C1o_DM1                    (* (reg8 *) C1o__DM1)
#define C1o_DM2                    (* (reg8 *) C1o__DM2) 
/* Input Buffer Disable Override */
#define C1o_INP_DIS                (* (reg8 *) C1o__INP_DIS)
/* LCD Common or Segment Drive */
#define C1o_LCD_COM_SEG            (* (reg8 *) C1o__LCD_COM_SEG)
/* Enable Segment LCD */
#define C1o_LCD_EN                 (* (reg8 *) C1o__LCD_EN)
/* Slew Rate Control */
#define C1o_SLW                    (* (reg8 *) C1o__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define C1o_PRTDSI__CAPS_SEL       (* (reg8 *) C1o__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define C1o_PRTDSI__DBL_SYNC_IN    (* (reg8 *) C1o__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define C1o_PRTDSI__OE_SEL0        (* (reg8 *) C1o__PRTDSI__OE_SEL0) 
#define C1o_PRTDSI__OE_SEL1        (* (reg8 *) C1o__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define C1o_PRTDSI__OUT_SEL0       (* (reg8 *) C1o__PRTDSI__OUT_SEL0) 
#define C1o_PRTDSI__OUT_SEL1       (* (reg8 *) C1o__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define C1o_PRTDSI__SYNC_OUT       (* (reg8 *) C1o__PRTDSI__SYNC_OUT) 


#if defined(C1o__INTSTAT)  /* Interrupt Registers */

    #define C1o_INTSTAT                (* (reg8 *) C1o__INTSTAT)
    #define C1o_SNAP                   (* (reg8 *) C1o__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_C1o_H */


/* [] END OF FILE */
