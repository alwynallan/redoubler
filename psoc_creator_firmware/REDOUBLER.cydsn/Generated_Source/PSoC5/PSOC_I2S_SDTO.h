/*******************************************************************************
* File Name: PSOC_I2S_SDTO.h  
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

#if !defined(CY_PINS_PSOC_I2S_SDTO_H) /* Pins PSOC_I2S_SDTO_H */
#define CY_PINS_PSOC_I2S_SDTO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PSOC_I2S_SDTO_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PSOC_I2S_SDTO__PORT == 15 && ((PSOC_I2S_SDTO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PSOC_I2S_SDTO_Write(uint8 value) ;
void    PSOC_I2S_SDTO_SetDriveMode(uint8 mode) ;
uint8   PSOC_I2S_SDTO_ReadDataReg(void) ;
uint8   PSOC_I2S_SDTO_Read(void) ;
uint8   PSOC_I2S_SDTO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PSOC_I2S_SDTO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PSOC_I2S_SDTO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PSOC_I2S_SDTO_DM_RES_UP          PIN_DM_RES_UP
#define PSOC_I2S_SDTO_DM_RES_DWN         PIN_DM_RES_DWN
#define PSOC_I2S_SDTO_DM_OD_LO           PIN_DM_OD_LO
#define PSOC_I2S_SDTO_DM_OD_HI           PIN_DM_OD_HI
#define PSOC_I2S_SDTO_DM_STRONG          PIN_DM_STRONG
#define PSOC_I2S_SDTO_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PSOC_I2S_SDTO_MASK               PSOC_I2S_SDTO__MASK
#define PSOC_I2S_SDTO_SHIFT              PSOC_I2S_SDTO__SHIFT
#define PSOC_I2S_SDTO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PSOC_I2S_SDTO_PS                     (* (reg8 *) PSOC_I2S_SDTO__PS)
/* Data Register */
#define PSOC_I2S_SDTO_DR                     (* (reg8 *) PSOC_I2S_SDTO__DR)
/* Port Number */
#define PSOC_I2S_SDTO_PRT_NUM                (* (reg8 *) PSOC_I2S_SDTO__PRT) 
/* Connect to Analog Globals */                                                  
#define PSOC_I2S_SDTO_AG                     (* (reg8 *) PSOC_I2S_SDTO__AG)                       
/* Analog MUX bux enable */
#define PSOC_I2S_SDTO_AMUX                   (* (reg8 *) PSOC_I2S_SDTO__AMUX) 
/* Bidirectional Enable */                                                        
#define PSOC_I2S_SDTO_BIE                    (* (reg8 *) PSOC_I2S_SDTO__BIE)
/* Bit-mask for Aliased Register Access */
#define PSOC_I2S_SDTO_BIT_MASK               (* (reg8 *) PSOC_I2S_SDTO__BIT_MASK)
/* Bypass Enable */
#define PSOC_I2S_SDTO_BYP                    (* (reg8 *) PSOC_I2S_SDTO__BYP)
/* Port wide control signals */                                                   
#define PSOC_I2S_SDTO_CTL                    (* (reg8 *) PSOC_I2S_SDTO__CTL)
/* Drive Modes */
#define PSOC_I2S_SDTO_DM0                    (* (reg8 *) PSOC_I2S_SDTO__DM0) 
#define PSOC_I2S_SDTO_DM1                    (* (reg8 *) PSOC_I2S_SDTO__DM1)
#define PSOC_I2S_SDTO_DM2                    (* (reg8 *) PSOC_I2S_SDTO__DM2) 
/* Input Buffer Disable Override */
#define PSOC_I2S_SDTO_INP_DIS                (* (reg8 *) PSOC_I2S_SDTO__INP_DIS)
/* LCD Common or Segment Drive */
#define PSOC_I2S_SDTO_LCD_COM_SEG            (* (reg8 *) PSOC_I2S_SDTO__LCD_COM_SEG)
/* Enable Segment LCD */
#define PSOC_I2S_SDTO_LCD_EN                 (* (reg8 *) PSOC_I2S_SDTO__LCD_EN)
/* Slew Rate Control */
#define PSOC_I2S_SDTO_SLW                    (* (reg8 *) PSOC_I2S_SDTO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PSOC_I2S_SDTO_PRTDSI__CAPS_SEL       (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PSOC_I2S_SDTO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PSOC_I2S_SDTO_PRTDSI__OE_SEL0        (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__OE_SEL0) 
#define PSOC_I2S_SDTO_PRTDSI__OE_SEL1        (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PSOC_I2S_SDTO_PRTDSI__OUT_SEL0       (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__OUT_SEL0) 
#define PSOC_I2S_SDTO_PRTDSI__OUT_SEL1       (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PSOC_I2S_SDTO_PRTDSI__SYNC_OUT       (* (reg8 *) PSOC_I2S_SDTO__PRTDSI__SYNC_OUT) 


#if defined(PSOC_I2S_SDTO__INTSTAT)  /* Interrupt Registers */

    #define PSOC_I2S_SDTO_INTSTAT                (* (reg8 *) PSOC_I2S_SDTO__INTSTAT)
    #define PSOC_I2S_SDTO_SNAP                   (* (reg8 *) PSOC_I2S_SDTO__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PSOC_I2S_SDTO_H */


/* [] END OF FILE */
