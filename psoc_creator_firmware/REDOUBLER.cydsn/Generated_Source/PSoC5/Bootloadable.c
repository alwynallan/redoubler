/*******************************************************************************
* File Name: Bootloadable.c
* Version 1.10
*
*  Description:
*   Provides an API for the Bootloadable application. The API includes a
*   single function for starting bootloader.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Bootloadable.h"


/*******************************************************************************
* Function Name: Bootloadable_Load
********************************************************************************
* Summary:
*  Begins the bootloading algorithm, downloading a new ACD image from the host.
*
* Parameters:
*  None
*
* Returns:
*  This method will never return. It will load a new application and reset
*  the device.
*
*******************************************************************************/
void Bootloadable_Load(void) 
{
    /* Schedule Bootloader to start after reset */
    Bootloadable_SET_RUN_TYPE(Bootloadable_START_BTLDR);

    /* Reset device */
    Bootloadable_SOFTWARE_RESET;
}


/*******************************************************************************
* Function Name: Bootloadable_SetFlashByte
********************************************************************************
* Summary:
*  Sets byte at specified address in Flash.
*
* Parameters:  
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void Bootloadable_SetFlashByte(uint32 address, uint8 runType) 
{
    uint32 flsAddr = address - CYDEV_FLASH_BASE;
    uint8 rowData[CYDEV_FLS_ROW_SIZE];

    #if !(CY_PSOC4)
        uint8 arrayId = (flsAddr / CYDEV_FLS_SECTOR_SIZE);
    #endif  /* !(CY_PSOC4) */

    uint16 rowNum = ((flsAddr % CYDEV_FLS_SECTOR_SIZE) / CYDEV_FLS_ROW_SIZE);
    uint32 baseAddr = address - (address % CYDEV_FLS_ROW_SIZE);
    uint16 idx;


    for (idx = 0; idx < CYDEV_FLS_ROW_SIZE; idx++)
    {
        rowData[idx] = Bootloadable_GET_CODE_DATA(baseAddr + idx);
    }
    rowData[address % CYDEV_FLS_ROW_SIZE] = runType;

    #if(CY_PSOC4)
        CySysFlashWriteRow(rowNum, rowData);
    #else
        CyWriteRowData(arrayId, rowNum, rowData);
    #endif  /* (CY_PSOC4) */
}


/* [] END OF FILE */
