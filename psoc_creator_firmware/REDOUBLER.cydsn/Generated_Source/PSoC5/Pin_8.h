/*******************************************************************************
* File Name: Pin_8.h  
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

#if !defined(CY_PINS_Pin_8_H) /* Pins Pin_8_H */
#define CY_PINS_Pin_8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_8_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_8__PORT == 15 && ((Pin_8__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_8_Write(uint8 value) ;
void    Pin_8_SetDriveMode(uint8 mode) ;
uint8   Pin_8_ReadDataReg(void) ;
uint8   Pin_8_Read(void) ;
uint8   Pin_8_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_8_DM_RES_UP          PIN_DM_RES_UP
#define Pin_8_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_8_DM_OD_LO           PIN_DM_OD_LO
#define Pin_8_DM_OD_HI           PIN_DM_OD_HI
#define Pin_8_DM_STRONG          PIN_DM_STRONG
#define Pin_8_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_8_MASK               Pin_8__MASK
#define Pin_8_SHIFT              Pin_8__SHIFT
#define Pin_8_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_8_PS                     (* (reg8 *) Pin_8__PS)
/* Data Register */
#define Pin_8_DR                     (* (reg8 *) Pin_8__DR)
/* Port Number */
#define Pin_8_PRT_NUM                (* (reg8 *) Pin_8__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_8_AG                     (* (reg8 *) Pin_8__AG)                       
/* Analog MUX bux enable */
#define Pin_8_AMUX                   (* (reg8 *) Pin_8__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_8_BIE                    (* (reg8 *) Pin_8__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_8_BIT_MASK               (* (reg8 *) Pin_8__BIT_MASK)
/* Bypass Enable */
#define Pin_8_BYP                    (* (reg8 *) Pin_8__BYP)
/* Port wide control signals */                                                   
#define Pin_8_CTL                    (* (reg8 *) Pin_8__CTL)
/* Drive Modes */
#define Pin_8_DM0                    (* (reg8 *) Pin_8__DM0) 
#define Pin_8_DM1                    (* (reg8 *) Pin_8__DM1)
#define Pin_8_DM2                    (* (reg8 *) Pin_8__DM2) 
/* Input Buffer Disable Override */
#define Pin_8_INP_DIS                (* (reg8 *) Pin_8__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_8_LCD_COM_SEG            (* (reg8 *) Pin_8__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_8_LCD_EN                 (* (reg8 *) Pin_8__LCD_EN)
/* Slew Rate Control */
#define Pin_8_SLW                    (* (reg8 *) Pin_8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_8_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_8_PRTDSI__OE_SEL0        (* (reg8 *) Pin_8__PRTDSI__OE_SEL0) 
#define Pin_8_PRTDSI__OE_SEL1        (* (reg8 *) Pin_8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_8_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_8__PRTDSI__OUT_SEL0) 
#define Pin_8_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_8_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_8__PRTDSI__SYNC_OUT) 


#if defined(Pin_8__INTSTAT)  /* Interrupt Registers */

    #define Pin_8_INTSTAT                (* (reg8 *) Pin_8__INTSTAT)
    #define Pin_8_SNAP                   (* (reg8 *) Pin_8__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_8_H */


/* [] END OF FILE */
