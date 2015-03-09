/*******************************************************************************
* File Name: PSOC_I2S_MCLK.h  
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

#if !defined(CY_PINS_PSOC_I2S_MCLK_H) /* Pins PSOC_I2S_MCLK_H */
#define CY_PINS_PSOC_I2S_MCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PSOC_I2S_MCLK_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PSOC_I2S_MCLK__PORT == 15 && ((PSOC_I2S_MCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PSOC_I2S_MCLK_Write(uint8 value) ;
void    PSOC_I2S_MCLK_SetDriveMode(uint8 mode) ;
uint8   PSOC_I2S_MCLK_ReadDataReg(void) ;
uint8   PSOC_I2S_MCLK_Read(void) ;
uint8   PSOC_I2S_MCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PSOC_I2S_MCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PSOC_I2S_MCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PSOC_I2S_MCLK_DM_RES_UP          PIN_DM_RES_UP
#define PSOC_I2S_MCLK_DM_RES_DWN         PIN_DM_RES_DWN
#define PSOC_I2S_MCLK_DM_OD_LO           PIN_DM_OD_LO
#define PSOC_I2S_MCLK_DM_OD_HI           PIN_DM_OD_HI
#define PSOC_I2S_MCLK_DM_STRONG          PIN_DM_STRONG
#define PSOC_I2S_MCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PSOC_I2S_MCLK_MASK               PSOC_I2S_MCLK__MASK
#define PSOC_I2S_MCLK_SHIFT              PSOC_I2S_MCLK__SHIFT
#define PSOC_I2S_MCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PSOC_I2S_MCLK_PS                     (* (reg8 *) PSOC_I2S_MCLK__PS)
/* Data Register */
#define PSOC_I2S_MCLK_DR                     (* (reg8 *) PSOC_I2S_MCLK__DR)
/* Port Number */
#define PSOC_I2S_MCLK_PRT_NUM                (* (reg8 *) PSOC_I2S_MCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define PSOC_I2S_MCLK_AG                     (* (reg8 *) PSOC_I2S_MCLK__AG)                       
/* Analog MUX bux enable */
#define PSOC_I2S_MCLK_AMUX                   (* (reg8 *) PSOC_I2S_MCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define PSOC_I2S_MCLK_BIE                    (* (reg8 *) PSOC_I2S_MCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define PSOC_I2S_MCLK_BIT_MASK               (* (reg8 *) PSOC_I2S_MCLK__BIT_MASK)
/* Bypass Enable */
#define PSOC_I2S_MCLK_BYP                    (* (reg8 *) PSOC_I2S_MCLK__BYP)
/* Port wide control signals */                                                   
#define PSOC_I2S_MCLK_CTL                    (* (reg8 *) PSOC_I2S_MCLK__CTL)
/* Drive Modes */
#define PSOC_I2S_MCLK_DM0                    (* (reg8 *) PSOC_I2S_MCLK__DM0) 
#define PSOC_I2S_MCLK_DM1                    (* (reg8 *) PSOC_I2S_MCLK__DM1)
#define PSOC_I2S_MCLK_DM2                    (* (reg8 *) PSOC_I2S_MCLK__DM2) 
/* Input Buffer Disable Override */
#define PSOC_I2S_MCLK_INP_DIS                (* (reg8 *) PSOC_I2S_MCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define PSOC_I2S_MCLK_LCD_COM_SEG            (* (reg8 *) PSOC_I2S_MCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define PSOC_I2S_MCLK_LCD_EN                 (* (reg8 *) PSOC_I2S_MCLK__LCD_EN)
/* Slew Rate Control */
#define PSOC_I2S_MCLK_SLW                    (* (reg8 *) PSOC_I2S_MCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PSOC_I2S_MCLK_PRTDSI__CAPS_SEL       (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PSOC_I2S_MCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PSOC_I2S_MCLK_PRTDSI__OE_SEL0        (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__OE_SEL0) 
#define PSOC_I2S_MCLK_PRTDSI__OE_SEL1        (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PSOC_I2S_MCLK_PRTDSI__OUT_SEL0       (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__OUT_SEL0) 
#define PSOC_I2S_MCLK_PRTDSI__OUT_SEL1       (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PSOC_I2S_MCLK_PRTDSI__SYNC_OUT       (* (reg8 *) PSOC_I2S_MCLK__PRTDSI__SYNC_OUT) 


#if defined(PSOC_I2S_MCLK__INTSTAT)  /* Interrupt Registers */

    #define PSOC_I2S_MCLK_INTSTAT                (* (reg8 *) PSOC_I2S_MCLK__INTSTAT)
    #define PSOC_I2S_MCLK_SNAP                   (* (reg8 *) PSOC_I2S_MCLK__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PSOC_I2S_MCLK_H */


/* [] END OF FILE */
