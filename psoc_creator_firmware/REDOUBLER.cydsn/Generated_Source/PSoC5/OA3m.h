/*******************************************************************************
* File Name: OA3m.h  
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

#if !defined(CY_PINS_OA3m_H) /* Pins OA3m_H */
#define CY_PINS_OA3m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OA3m_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OA3m__PORT == 15 && ((OA3m__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    OA3m_Write(uint8 value) ;
void    OA3m_SetDriveMode(uint8 mode) ;
uint8   OA3m_ReadDataReg(void) ;
uint8   OA3m_Read(void) ;
uint8   OA3m_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OA3m_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define OA3m_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define OA3m_DM_RES_UP          PIN_DM_RES_UP
#define OA3m_DM_RES_DWN         PIN_DM_RES_DWN
#define OA3m_DM_OD_LO           PIN_DM_OD_LO
#define OA3m_DM_OD_HI           PIN_DM_OD_HI
#define OA3m_DM_STRONG          PIN_DM_STRONG
#define OA3m_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define OA3m_MASK               OA3m__MASK
#define OA3m_SHIFT              OA3m__SHIFT
#define OA3m_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OA3m_PS                     (* (reg8 *) OA3m__PS)
/* Data Register */
#define OA3m_DR                     (* (reg8 *) OA3m__DR)
/* Port Number */
#define OA3m_PRT_NUM                (* (reg8 *) OA3m__PRT) 
/* Connect to Analog Globals */                                                  
#define OA3m_AG                     (* (reg8 *) OA3m__AG)                       
/* Analog MUX bux enable */
#define OA3m_AMUX                   (* (reg8 *) OA3m__AMUX) 
/* Bidirectional Enable */                                                        
#define OA3m_BIE                    (* (reg8 *) OA3m__BIE)
/* Bit-mask for Aliased Register Access */
#define OA3m_BIT_MASK               (* (reg8 *) OA3m__BIT_MASK)
/* Bypass Enable */
#define OA3m_BYP                    (* (reg8 *) OA3m__BYP)
/* Port wide control signals */                                                   
#define OA3m_CTL                    (* (reg8 *) OA3m__CTL)
/* Drive Modes */
#define OA3m_DM0                    (* (reg8 *) OA3m__DM0) 
#define OA3m_DM1                    (* (reg8 *) OA3m__DM1)
#define OA3m_DM2                    (* (reg8 *) OA3m__DM2) 
/* Input Buffer Disable Override */
#define OA3m_INP_DIS                (* (reg8 *) OA3m__INP_DIS)
/* LCD Common or Segment Drive */
#define OA3m_LCD_COM_SEG            (* (reg8 *) OA3m__LCD_COM_SEG)
/* Enable Segment LCD */
#define OA3m_LCD_EN                 (* (reg8 *) OA3m__LCD_EN)
/* Slew Rate Control */
#define OA3m_SLW                    (* (reg8 *) OA3m__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OA3m_PRTDSI__CAPS_SEL       (* (reg8 *) OA3m__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OA3m_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OA3m__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OA3m_PRTDSI__OE_SEL0        (* (reg8 *) OA3m__PRTDSI__OE_SEL0) 
#define OA3m_PRTDSI__OE_SEL1        (* (reg8 *) OA3m__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OA3m_PRTDSI__OUT_SEL0       (* (reg8 *) OA3m__PRTDSI__OUT_SEL0) 
#define OA3m_PRTDSI__OUT_SEL1       (* (reg8 *) OA3m__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OA3m_PRTDSI__SYNC_OUT       (* (reg8 *) OA3m__PRTDSI__SYNC_OUT) 


#if defined(OA3m__INTSTAT)  /* Interrupt Registers */

    #define OA3m_INTSTAT                (* (reg8 *) OA3m__INTSTAT)
    #define OA3m_SNAP                   (* (reg8 *) OA3m__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OA3m_H */


/* [] END OF FILE */
