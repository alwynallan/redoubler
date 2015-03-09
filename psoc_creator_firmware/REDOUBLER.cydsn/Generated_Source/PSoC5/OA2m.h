/*******************************************************************************
* File Name: OA2m.h  
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

#if !defined(CY_PINS_OA2m_H) /* Pins OA2m_H */
#define CY_PINS_OA2m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OA2m_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OA2m__PORT == 15 && ((OA2m__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    OA2m_Write(uint8 value) ;
void    OA2m_SetDriveMode(uint8 mode) ;
uint8   OA2m_ReadDataReg(void) ;
uint8   OA2m_Read(void) ;
uint8   OA2m_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OA2m_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define OA2m_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define OA2m_DM_RES_UP          PIN_DM_RES_UP
#define OA2m_DM_RES_DWN         PIN_DM_RES_DWN
#define OA2m_DM_OD_LO           PIN_DM_OD_LO
#define OA2m_DM_OD_HI           PIN_DM_OD_HI
#define OA2m_DM_STRONG          PIN_DM_STRONG
#define OA2m_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define OA2m_MASK               OA2m__MASK
#define OA2m_SHIFT              OA2m__SHIFT
#define OA2m_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OA2m_PS                     (* (reg8 *) OA2m__PS)
/* Data Register */
#define OA2m_DR                     (* (reg8 *) OA2m__DR)
/* Port Number */
#define OA2m_PRT_NUM                (* (reg8 *) OA2m__PRT) 
/* Connect to Analog Globals */                                                  
#define OA2m_AG                     (* (reg8 *) OA2m__AG)                       
/* Analog MUX bux enable */
#define OA2m_AMUX                   (* (reg8 *) OA2m__AMUX) 
/* Bidirectional Enable */                                                        
#define OA2m_BIE                    (* (reg8 *) OA2m__BIE)
/* Bit-mask for Aliased Register Access */
#define OA2m_BIT_MASK               (* (reg8 *) OA2m__BIT_MASK)
/* Bypass Enable */
#define OA2m_BYP                    (* (reg8 *) OA2m__BYP)
/* Port wide control signals */                                                   
#define OA2m_CTL                    (* (reg8 *) OA2m__CTL)
/* Drive Modes */
#define OA2m_DM0                    (* (reg8 *) OA2m__DM0) 
#define OA2m_DM1                    (* (reg8 *) OA2m__DM1)
#define OA2m_DM2                    (* (reg8 *) OA2m__DM2) 
/* Input Buffer Disable Override */
#define OA2m_INP_DIS                (* (reg8 *) OA2m__INP_DIS)
/* LCD Common or Segment Drive */
#define OA2m_LCD_COM_SEG            (* (reg8 *) OA2m__LCD_COM_SEG)
/* Enable Segment LCD */
#define OA2m_LCD_EN                 (* (reg8 *) OA2m__LCD_EN)
/* Slew Rate Control */
#define OA2m_SLW                    (* (reg8 *) OA2m__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OA2m_PRTDSI__CAPS_SEL       (* (reg8 *) OA2m__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OA2m_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OA2m__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OA2m_PRTDSI__OE_SEL0        (* (reg8 *) OA2m__PRTDSI__OE_SEL0) 
#define OA2m_PRTDSI__OE_SEL1        (* (reg8 *) OA2m__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OA2m_PRTDSI__OUT_SEL0       (* (reg8 *) OA2m__PRTDSI__OUT_SEL0) 
#define OA2m_PRTDSI__OUT_SEL1       (* (reg8 *) OA2m__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OA2m_PRTDSI__SYNC_OUT       (* (reg8 *) OA2m__PRTDSI__SYNC_OUT) 


#if defined(OA2m__INTSTAT)  /* Interrupt Registers */

    #define OA2m_INTSTAT                (* (reg8 *) OA2m__INTSTAT)
    #define OA2m_SNAP                   (* (reg8 *) OA2m__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OA2m_H */


/* [] END OF FILE */
