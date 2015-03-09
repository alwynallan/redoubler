/*******************************************************************************
* File Name: Clock_CIC_Running.h  
* Version 1.70
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

#if !defined(CY_CONTROL_REG_Clock_CIC_Running_H) /* CY_CONTROL_REG_Clock_CIC_Running_H */
#define CY_CONTROL_REG_Clock_CIC_Running_H

#include "cytypes.h"


/***************************************
*         Function Prototypes 
***************************************/

void    Clock_CIC_Running_Write(uint8 control) ;
uint8   Clock_CIC_Running_Read(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Clock_CIC_Running_Control        (* (reg8 *) Clock_CIC_Running_Sync_ctrl_reg__CONTROL_REG )
#define Clock_CIC_Running_Control_PTR    (  (reg8 *) Clock_CIC_Running_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Clock_CIC_Running_H */


/* [] END OF FILE */
