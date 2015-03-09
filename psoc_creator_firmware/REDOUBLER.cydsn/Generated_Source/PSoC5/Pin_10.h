/*******************************************************************************
* File Name: Pin_10.h  
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

#if !defined(CY_PINS_Pin_10_H) /* Pins Pin_10_H */
#define CY_PINS_Pin_10_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_10_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_10__PORT == 15 && ((Pin_10__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_10_Write(uint8 value) ;
void    Pin_10_SetDriveMode(uint8 mode) ;
uint8   Pin_10_ReadDataReg(void) ;
uint8   Pin_10_Read(void) ;
uint8   Pin_10_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_10_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_10_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_10_DM_RES_UP          PIN_DM_RES_UP
#define Pin_10_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_10_DM_OD_LO           PIN_DM_OD_LO
#define Pin_10_DM_OD_HI           PIN_DM_OD_HI
#define Pin_10_DM_STRONG          PIN_DM_STRONG
#define Pin_10_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_10_MASK               Pin_10__MASK
#define Pin_10_SHIFT              Pin_10__SHIFT
#define Pin_10_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_10_PS                     (* (reg8 *) Pin_10__PS)
/* Data Register */
#define Pin_10_DR                     (* (reg8 *) Pin_10__DR)
/* Port Number */
#define Pin_10_PRT_NUM                (* (reg8 *) Pin_10__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_10_AG                     (* (reg8 *) Pin_10__AG)                       
/* Analog MUX bux enable */
#define Pin_10_AMUX                   (* (reg8 *) Pin_10__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_10_BIE                    (* (reg8 *) Pin_10__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_10_BIT_MASK               (* (reg8 *) Pin_10__BIT_MASK)
/* Bypass Enable */
#define Pin_10_BYP                    (* (reg8 *) Pin_10__BYP)
/* Port wide control signals */                                                   
#define Pin_10_CTL                    (* (reg8 *) Pin_10__CTL)
/* Drive Modes */
#define Pin_10_DM0                    (* (reg8 *) Pin_10__DM0) 
#define Pin_10_DM1                    (* (reg8 *) Pin_10__DM1)
#define Pin_10_DM2                    (* (reg8 *) Pin_10__DM2) 
/* Input Buffer Disable Override */
#define Pin_10_INP_DIS                (* (reg8 *) Pin_10__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_10_LCD_COM_SEG            (* (reg8 *) Pin_10__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_10_LCD_EN                 (* (reg8 *) Pin_10__LCD_EN)
/* Slew Rate Control */
#define Pin_10_SLW                    (* (reg8 *) Pin_10__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_10_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_10__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_10_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_10__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_10_PRTDSI__OE_SEL0        (* (reg8 *) Pin_10__PRTDSI__OE_SEL0) 
#define Pin_10_PRTDSI__OE_SEL1        (* (reg8 *) Pin_10__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_10_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_10__PRTDSI__OUT_SEL0) 
#define Pin_10_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_10__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_10_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_10__PRTDSI__SYNC_OUT) 


#if defined(Pin_10__INTSTAT)  /* Interrupt Registers */

    #define Pin_10_INTSTAT                (* (reg8 *) Pin_10__INTSTAT)
    #define Pin_10_SNAP                   (* (reg8 *) Pin_10__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_10_H */


/* [] END OF FILE */
