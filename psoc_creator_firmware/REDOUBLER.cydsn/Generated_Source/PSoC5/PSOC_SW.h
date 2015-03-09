/*******************************************************************************
* File Name: PSOC_SW.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PSOC_SW_H) /* Pins PSOC_SW_H */
#define CY_PINS_PSOC_SW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PSOC_SW_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PSOC_SW__PORT == 15 && ((PSOC_SW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PSOC_SW_Write(uint8 value) ;
void    PSOC_SW_SetDriveMode(uint8 mode) ;
uint8   PSOC_SW_ReadDataReg(void) ;
uint8   PSOC_SW_Read(void) ;
uint8   PSOC_SW_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PSOC_SW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PSOC_SW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PSOC_SW_DM_RES_UP          PIN_DM_RES_UP
#define PSOC_SW_DM_RES_DWN         PIN_DM_RES_DWN
#define PSOC_SW_DM_OD_LO           PIN_DM_OD_LO
#define PSOC_SW_DM_OD_HI           PIN_DM_OD_HI
#define PSOC_SW_DM_STRONG          PIN_DM_STRONG
#define PSOC_SW_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PSOC_SW_MASK               PSOC_SW__MASK
#define PSOC_SW_SHIFT              PSOC_SW__SHIFT
#define PSOC_SW_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PSOC_SW_PS                     (* (reg8 *) PSOC_SW__PS)
/* Data Register */
#define PSOC_SW_DR                     (* (reg8 *) PSOC_SW__DR)
/* Port Number */
#define PSOC_SW_PRT_NUM                (* (reg8 *) PSOC_SW__PRT) 
/* Connect to Analog Globals */                                                  
#define PSOC_SW_AG                     (* (reg8 *) PSOC_SW__AG)                       
/* Analog MUX bux enable */
#define PSOC_SW_AMUX                   (* (reg8 *) PSOC_SW__AMUX) 
/* Bidirectional Enable */                                                        
#define PSOC_SW_BIE                    (* (reg8 *) PSOC_SW__BIE)
/* Bit-mask for Aliased Register Access */
#define PSOC_SW_BIT_MASK               (* (reg8 *) PSOC_SW__BIT_MASK)
/* Bypass Enable */
#define PSOC_SW_BYP                    (* (reg8 *) PSOC_SW__BYP)
/* Port wide control signals */                                                   
#define PSOC_SW_CTL                    (* (reg8 *) PSOC_SW__CTL)
/* Drive Modes */
#define PSOC_SW_DM0                    (* (reg8 *) PSOC_SW__DM0) 
#define PSOC_SW_DM1                    (* (reg8 *) PSOC_SW__DM1)
#define PSOC_SW_DM2                    (* (reg8 *) PSOC_SW__DM2) 
/* Input Buffer Disable Override */
#define PSOC_SW_INP_DIS                (* (reg8 *) PSOC_SW__INP_DIS)
/* LCD Common or Segment Drive */
#define PSOC_SW_LCD_COM_SEG            (* (reg8 *) PSOC_SW__LCD_COM_SEG)
/* Enable Segment LCD */
#define PSOC_SW_LCD_EN                 (* (reg8 *) PSOC_SW__LCD_EN)
/* Slew Rate Control */
#define PSOC_SW_SLW                    (* (reg8 *) PSOC_SW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PSOC_SW_PRTDSI__CAPS_SEL       (* (reg8 *) PSOC_SW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PSOC_SW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PSOC_SW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PSOC_SW_PRTDSI__OE_SEL0        (* (reg8 *) PSOC_SW__PRTDSI__OE_SEL0) 
#define PSOC_SW_PRTDSI__OE_SEL1        (* (reg8 *) PSOC_SW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PSOC_SW_PRTDSI__OUT_SEL0       (* (reg8 *) PSOC_SW__PRTDSI__OUT_SEL0) 
#define PSOC_SW_PRTDSI__OUT_SEL1       (* (reg8 *) PSOC_SW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PSOC_SW_PRTDSI__SYNC_OUT       (* (reg8 *) PSOC_SW__PRTDSI__SYNC_OUT) 


#if defined(PSOC_SW__INTSTAT)  /* Interrupt Registers */

    #define PSOC_SW_INTSTAT                (* (reg8 *) PSOC_SW__INTSTAT)
    #define PSOC_SW_SNAP                   (* (reg8 *) PSOC_SW__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PSOC_SW_H */


/* [] END OF FILE */
