/*******************************************************************************
* File Name: PSOC_PDM_LR_SEL.h  
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

#if !defined(CY_PINS_PSOC_PDM_LR_SEL_H) /* Pins PSOC_PDM_LR_SEL_H */
#define CY_PINS_PSOC_PDM_LR_SEL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PSOC_PDM_LR_SEL_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PSOC_PDM_LR_SEL__PORT == 15 && ((PSOC_PDM_LR_SEL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PSOC_PDM_LR_SEL_Write(uint8 value) ;
void    PSOC_PDM_LR_SEL_SetDriveMode(uint8 mode) ;
uint8   PSOC_PDM_LR_SEL_ReadDataReg(void) ;
uint8   PSOC_PDM_LR_SEL_Read(void) ;
uint8   PSOC_PDM_LR_SEL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PSOC_PDM_LR_SEL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PSOC_PDM_LR_SEL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PSOC_PDM_LR_SEL_DM_RES_UP          PIN_DM_RES_UP
#define PSOC_PDM_LR_SEL_DM_RES_DWN         PIN_DM_RES_DWN
#define PSOC_PDM_LR_SEL_DM_OD_LO           PIN_DM_OD_LO
#define PSOC_PDM_LR_SEL_DM_OD_HI           PIN_DM_OD_HI
#define PSOC_PDM_LR_SEL_DM_STRONG          PIN_DM_STRONG
#define PSOC_PDM_LR_SEL_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PSOC_PDM_LR_SEL_MASK               PSOC_PDM_LR_SEL__MASK
#define PSOC_PDM_LR_SEL_SHIFT              PSOC_PDM_LR_SEL__SHIFT
#define PSOC_PDM_LR_SEL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PSOC_PDM_LR_SEL_PS                     (* (reg8 *) PSOC_PDM_LR_SEL__PS)
/* Data Register */
#define PSOC_PDM_LR_SEL_DR                     (* (reg8 *) PSOC_PDM_LR_SEL__DR)
/* Port Number */
#define PSOC_PDM_LR_SEL_PRT_NUM                (* (reg8 *) PSOC_PDM_LR_SEL__PRT) 
/* Connect to Analog Globals */                                                  
#define PSOC_PDM_LR_SEL_AG                     (* (reg8 *) PSOC_PDM_LR_SEL__AG)                       
/* Analog MUX bux enable */
#define PSOC_PDM_LR_SEL_AMUX                   (* (reg8 *) PSOC_PDM_LR_SEL__AMUX) 
/* Bidirectional Enable */                                                        
#define PSOC_PDM_LR_SEL_BIE                    (* (reg8 *) PSOC_PDM_LR_SEL__BIE)
/* Bit-mask for Aliased Register Access */
#define PSOC_PDM_LR_SEL_BIT_MASK               (* (reg8 *) PSOC_PDM_LR_SEL__BIT_MASK)
/* Bypass Enable */
#define PSOC_PDM_LR_SEL_BYP                    (* (reg8 *) PSOC_PDM_LR_SEL__BYP)
/* Port wide control signals */                                                   
#define PSOC_PDM_LR_SEL_CTL                    (* (reg8 *) PSOC_PDM_LR_SEL__CTL)
/* Drive Modes */
#define PSOC_PDM_LR_SEL_DM0                    (* (reg8 *) PSOC_PDM_LR_SEL__DM0) 
#define PSOC_PDM_LR_SEL_DM1                    (* (reg8 *) PSOC_PDM_LR_SEL__DM1)
#define PSOC_PDM_LR_SEL_DM2                    (* (reg8 *) PSOC_PDM_LR_SEL__DM2) 
/* Input Buffer Disable Override */
#define PSOC_PDM_LR_SEL_INP_DIS                (* (reg8 *) PSOC_PDM_LR_SEL__INP_DIS)
/* LCD Common or Segment Drive */
#define PSOC_PDM_LR_SEL_LCD_COM_SEG            (* (reg8 *) PSOC_PDM_LR_SEL__LCD_COM_SEG)
/* Enable Segment LCD */
#define PSOC_PDM_LR_SEL_LCD_EN                 (* (reg8 *) PSOC_PDM_LR_SEL__LCD_EN)
/* Slew Rate Control */
#define PSOC_PDM_LR_SEL_SLW                    (* (reg8 *) PSOC_PDM_LR_SEL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PSOC_PDM_LR_SEL_PRTDSI__CAPS_SEL       (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PSOC_PDM_LR_SEL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PSOC_PDM_LR_SEL_PRTDSI__OE_SEL0        (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__OE_SEL0) 
#define PSOC_PDM_LR_SEL_PRTDSI__OE_SEL1        (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PSOC_PDM_LR_SEL_PRTDSI__OUT_SEL0       (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__OUT_SEL0) 
#define PSOC_PDM_LR_SEL_PRTDSI__OUT_SEL1       (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PSOC_PDM_LR_SEL_PRTDSI__SYNC_OUT       (* (reg8 *) PSOC_PDM_LR_SEL__PRTDSI__SYNC_OUT) 


#if defined(PSOC_PDM_LR_SEL__INTSTAT)  /* Interrupt Registers */

    #define PSOC_PDM_LR_SEL_INTSTAT                (* (reg8 *) PSOC_PDM_LR_SEL__INTSTAT)
    #define PSOC_PDM_LR_SEL_SNAP                   (* (reg8 *) PSOC_PDM_LR_SEL__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PSOC_PDM_LR_SEL_H */


/* [] END OF FILE */
