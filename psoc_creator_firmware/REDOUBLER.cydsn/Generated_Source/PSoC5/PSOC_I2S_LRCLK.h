/*******************************************************************************
* File Name: PSOC_I2S_LRCLK.h  
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

#if !defined(CY_PINS_PSOC_I2S_LRCLK_H) /* Pins PSOC_I2S_LRCLK_H */
#define CY_PINS_PSOC_I2S_LRCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PSOC_I2S_LRCLK_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PSOC_I2S_LRCLK__PORT == 15 && ((PSOC_I2S_LRCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PSOC_I2S_LRCLK_Write(uint8 value) ;
void    PSOC_I2S_LRCLK_SetDriveMode(uint8 mode) ;
uint8   PSOC_I2S_LRCLK_ReadDataReg(void) ;
uint8   PSOC_I2S_LRCLK_Read(void) ;
uint8   PSOC_I2S_LRCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PSOC_I2S_LRCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PSOC_I2S_LRCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PSOC_I2S_LRCLK_DM_RES_UP          PIN_DM_RES_UP
#define PSOC_I2S_LRCLK_DM_RES_DWN         PIN_DM_RES_DWN
#define PSOC_I2S_LRCLK_DM_OD_LO           PIN_DM_OD_LO
#define PSOC_I2S_LRCLK_DM_OD_HI           PIN_DM_OD_HI
#define PSOC_I2S_LRCLK_DM_STRONG          PIN_DM_STRONG
#define PSOC_I2S_LRCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PSOC_I2S_LRCLK_MASK               PSOC_I2S_LRCLK__MASK
#define PSOC_I2S_LRCLK_SHIFT              PSOC_I2S_LRCLK__SHIFT
#define PSOC_I2S_LRCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PSOC_I2S_LRCLK_PS                     (* (reg8 *) PSOC_I2S_LRCLK__PS)
/* Data Register */
#define PSOC_I2S_LRCLK_DR                     (* (reg8 *) PSOC_I2S_LRCLK__DR)
/* Port Number */
#define PSOC_I2S_LRCLK_PRT_NUM                (* (reg8 *) PSOC_I2S_LRCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define PSOC_I2S_LRCLK_AG                     (* (reg8 *) PSOC_I2S_LRCLK__AG)                       
/* Analog MUX bux enable */
#define PSOC_I2S_LRCLK_AMUX                   (* (reg8 *) PSOC_I2S_LRCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define PSOC_I2S_LRCLK_BIE                    (* (reg8 *) PSOC_I2S_LRCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define PSOC_I2S_LRCLK_BIT_MASK               (* (reg8 *) PSOC_I2S_LRCLK__BIT_MASK)
/* Bypass Enable */
#define PSOC_I2S_LRCLK_BYP                    (* (reg8 *) PSOC_I2S_LRCLK__BYP)
/* Port wide control signals */                                                   
#define PSOC_I2S_LRCLK_CTL                    (* (reg8 *) PSOC_I2S_LRCLK__CTL)
/* Drive Modes */
#define PSOC_I2S_LRCLK_DM0                    (* (reg8 *) PSOC_I2S_LRCLK__DM0) 
#define PSOC_I2S_LRCLK_DM1                    (* (reg8 *) PSOC_I2S_LRCLK__DM1)
#define PSOC_I2S_LRCLK_DM2                    (* (reg8 *) PSOC_I2S_LRCLK__DM2) 
/* Input Buffer Disable Override */
#define PSOC_I2S_LRCLK_INP_DIS                (* (reg8 *) PSOC_I2S_LRCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define PSOC_I2S_LRCLK_LCD_COM_SEG            (* (reg8 *) PSOC_I2S_LRCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define PSOC_I2S_LRCLK_LCD_EN                 (* (reg8 *) PSOC_I2S_LRCLK__LCD_EN)
/* Slew Rate Control */
#define PSOC_I2S_LRCLK_SLW                    (* (reg8 *) PSOC_I2S_LRCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PSOC_I2S_LRCLK_PRTDSI__CAPS_SEL       (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PSOC_I2S_LRCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PSOC_I2S_LRCLK_PRTDSI__OE_SEL0        (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__OE_SEL0) 
#define PSOC_I2S_LRCLK_PRTDSI__OE_SEL1        (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PSOC_I2S_LRCLK_PRTDSI__OUT_SEL0       (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__OUT_SEL0) 
#define PSOC_I2S_LRCLK_PRTDSI__OUT_SEL1       (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PSOC_I2S_LRCLK_PRTDSI__SYNC_OUT       (* (reg8 *) PSOC_I2S_LRCLK__PRTDSI__SYNC_OUT) 


#if defined(PSOC_I2S_LRCLK__INTSTAT)  /* Interrupt Registers */

    #define PSOC_I2S_LRCLK_INTSTAT                (* (reg8 *) PSOC_I2S_LRCLK__INTSTAT)
    #define PSOC_I2S_LRCLK_SNAP                   (* (reg8 *) PSOC_I2S_LRCLK__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PSOC_I2S_LRCLK_H */


/* [] END OF FILE */
