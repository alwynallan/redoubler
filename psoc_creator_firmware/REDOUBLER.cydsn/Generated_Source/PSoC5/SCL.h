/*******************************************************************************
* File Name: SCL.h  
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

#if !defined(CY_PINS_SCL_H) /* Pins SCL_H */
#define CY_PINS_SCL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SCL_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SCL__PORT == 15 && ((SCL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SCL_Write(uint8 value) ;
void    SCL_SetDriveMode(uint8 mode) ;
uint8   SCL_ReadDataReg(void) ;
uint8   SCL_Read(void) ;
uint8   SCL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SCL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SCL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SCL_DM_RES_UP          PIN_DM_RES_UP
#define SCL_DM_RES_DWN         PIN_DM_RES_DWN
#define SCL_DM_OD_LO           PIN_DM_OD_LO
#define SCL_DM_OD_HI           PIN_DM_OD_HI
#define SCL_DM_STRONG          PIN_DM_STRONG
#define SCL_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SCL_MASK               SCL__MASK
#define SCL_SHIFT              SCL__SHIFT
#define SCL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SCL_PS                     (* (reg8 *) SCL__PS)
/* Data Register */
#define SCL_DR                     (* (reg8 *) SCL__DR)
/* Port Number */
#define SCL_PRT_NUM                (* (reg8 *) SCL__PRT) 
/* Connect to Analog Globals */                                                  
#define SCL_AG                     (* (reg8 *) SCL__AG)                       
/* Analog MUX bux enable */
#define SCL_AMUX                   (* (reg8 *) SCL__AMUX) 
/* Bidirectional Enable */                                                        
#define SCL_BIE                    (* (reg8 *) SCL__BIE)
/* Bit-mask for Aliased Register Access */
#define SCL_BIT_MASK               (* (reg8 *) SCL__BIT_MASK)
/* Bypass Enable */
#define SCL_BYP                    (* (reg8 *) SCL__BYP)
/* Port wide control signals */                                                   
#define SCL_CTL                    (* (reg8 *) SCL__CTL)
/* Drive Modes */
#define SCL_DM0                    (* (reg8 *) SCL__DM0) 
#define SCL_DM1                    (* (reg8 *) SCL__DM1)
#define SCL_DM2                    (* (reg8 *) SCL__DM2) 
/* Input Buffer Disable Override */
#define SCL_INP_DIS                (* (reg8 *) SCL__INP_DIS)
/* LCD Common or Segment Drive */
#define SCL_LCD_COM_SEG            (* (reg8 *) SCL__LCD_COM_SEG)
/* Enable Segment LCD */
#define SCL_LCD_EN                 (* (reg8 *) SCL__LCD_EN)
/* Slew Rate Control */
#define SCL_SLW                    (* (reg8 *) SCL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SCL_PRTDSI__CAPS_SEL       (* (reg8 *) SCL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SCL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SCL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SCL_PRTDSI__OE_SEL0        (* (reg8 *) SCL__PRTDSI__OE_SEL0) 
#define SCL_PRTDSI__OE_SEL1        (* (reg8 *) SCL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SCL_PRTDSI__OUT_SEL0       (* (reg8 *) SCL__PRTDSI__OUT_SEL0) 
#define SCL_PRTDSI__OUT_SEL1       (* (reg8 *) SCL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SCL_PRTDSI__SYNC_OUT       (* (reg8 *) SCL__PRTDSI__SYNC_OUT) 


#if defined(SCL__INTSTAT)  /* Interrupt Registers */

    #define SCL_INTSTAT                (* (reg8 *) SCL__INTSTAT)
    #define SCL_SNAP                   (* (reg8 *) SCL__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SCL_H */


/* [] END OF FILE */
