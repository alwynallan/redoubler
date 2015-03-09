/*******************************************************************************
* File Name: USBFS_descr.c
* Version 2.60
*
* Description:
*  USB descriptors and storage.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBFS.h"
#include "USBFS_pvt.h"


/*****************************************************************************
*  User supplied descriptors.  If you want to specify your own descriptors,
*  remove the comments around the define USER_SUPPLIED_DESCRIPTORS below and
*  add your descriptors.
*****************************************************************************/
/* `#START USER_DESCRIPTORS_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
*  USB Customizer Generated Descriptors
***************************************/

#if !defined(USER_SUPPLIED_DESCRIPTORS)
/*********************************************************************
* Device Descriptors
*********************************************************************/
const uint8 CYCODE USBFS_DEVICE0_DESCR[18u] = {
/* Descriptor Length                       */ 0x12u,
/* DescriptorType: DEVICE                  */ 0x01u,
/* bcdUSB (ver 2.0)                        */ 0x00u, 0x02u,
/* bDeviceClass                            */ 0x00u,
/* bDeviceSubClass                         */ 0x00u,
/* bDeviceProtocol                         */ 0x00u,
/* bMaxPacketSize0                         */ 0x08u,
/* idVendor                                */ 0xB4u, 0x04u,
/* idProduct                               */ 0x00u, 0xC5u,
/* bcdDevice                               */ 0x00u, 0x10u,
/* iManufacturer                           */ 0x01u,
/* iProduct                                */ 0x0Cu,
/* iSerialNumber                           */ 0x80u,
/* bNumConfigurations                      */ 0x01u
};
/*********************************************************************
* Config Descriptor  
*********************************************************************/
const uint8 CYCODE USBFS_DEVICE0_CONFIGURATION0_DESCR[112u] = {
/*  Config Descriptor Length               */ 0x09u,
/*  DescriptorType: CONFIG                 */ 0x02u,
/*  wTotalLength                           */ 0x70u, 0x00u,
/*  bNumInterfaces                         */ 0x02u,
/*  bConfigurationValue                    */ 0x01u,
/*  iConfiguration                         */ 0x0Au,
/*  bmAttributes                           */ 0x80u,
/*  bMaxPower                              */ 0x32u,
/*********************************************************************
* AudioControl Interface Descriptor
*********************************************************************/
/*  Interface Descriptor Length            */ 0x09u,
/*  DescriptorType: INTERFACE              */ 0x04u,
/*  bInterfaceNumber                       */ 0x00u,
/*  bAlternateSetting                      */ 0x00u,
/*  bNumEndpoints                          */ 0x01u,
/*  bInterfaceClass                        */ 0x01u,
/*  bInterfaceSubClass                     */ 0x01u,
/*  bInterfaceProtocol                     */ 0x00u,
/*  iInterface                             */ 0x0Cu,
/*********************************************************************
* AC Header Descriptor
*********************************************************************/
/*  AC Header Descriptor Length            */ 0x09u,
/*  DescriptorType: AUDIO                  */ 0x24u,
/*  bDescriptorSubtype                     */ 0x01u,
/*  bcdADC                                 */ 0x00u, 0x01u,
/*  wTotalLength                           */ 0x1Eu, 0x00u,
/*  bInCollection                          */ 0x01u,
/*  baInterfaceNr                          */ 0x01u,
/*********************************************************************
* AC Input Terminal Descriptor
*********************************************************************/
/*  AC Input Terminal Descriptor Length    */ 0x0Cu,
/*  DescriptorType: AUDIO                  */ 0x24u,
/*  bDescriptorSubtype                     */ 0x02u,
/*  bTerminalID                            */ 0x04u,
/*  wTerminalType                          */ 0x01u, 0x02u,
/*  bAssocTerminal                         */ 0x00u,
/*  bNrChannels                            */ 0x02u,
/*  wChannelConfig                         */ 0x03u, 0x00u,
/*  iChannelNames                          */ 0x00u,
/*  iTerminal                              */ 0x04u,
/*********************************************************************
* AC Output Terminal Descriptor
*********************************************************************/
/*  AC Output Terminal Descriptor Length   */ 0x09u,
/*  DescriptorType: AUDIO                  */ 0x24u,
/*  bDescriptorSubtype                     */ 0x03u,
/*  bTerminalID                            */ 0x05u,
/*  wTerminalType                          */ 0x01u, 0x01u,
/*  bAssocTerminal                         */ 0x00u,
/*  bSourceID                              */ 0x04u,
/*  iTerminal                              */ 0x06u,
/*********************************************************************
* Endpoint Descriptor
*********************************************************************/
/*  Endpoint Descriptor Length             */ 0x09u,
/*  DescriptorType: ENDPOINT               */ 0x05u,
/*  bEndpointAddress                       */ 0x86u,
/*  bmAttributes                           */ 0x03u,
/*  wMaxPacketSize                         */ 0x02u, 0x00u,
/*  bInterval                              */ 0x1Eu,
/*  bRefresh                               */ 0x00u,
/*  bSynchAddress                          */ 0x00u,
/*********************************************************************
* AudioStreaming Interface Descriptor
*********************************************************************/
/*  Interface Descriptor Length            */ 0x09u,
/*  DescriptorType: INTERFACE              */ 0x04u,
/*  bInterfaceNumber                       */ 0x01u,
/*  bAlternateSetting                      */ 0x00u,
/*  bNumEndpoints                          */ 0x00u,
/*  bInterfaceClass                        */ 0x01u,
/*  bInterfaceSubClass                     */ 0x02u,
/*  bInterfaceProtocol                     */ 0x00u,
/*  iInterface                             */ 0x0Cu,
/*********************************************************************
* AudioStreaming Interface Descriptor
*********************************************************************/
/*  Interface Descriptor Length            */ 0x09u,
/*  DescriptorType: INTERFACE              */ 0x04u,
/*  bInterfaceNumber                       */ 0x01u,
/*  bAlternateSetting                      */ 0x01u,
/*  bNumEndpoints                          */ 0x01u,
/*  bInterfaceClass                        */ 0x01u,
/*  bInterfaceSubClass                     */ 0x02u,
/*  bInterfaceProtocol                     */ 0x00u,
/*  iInterface                             */ 0x08u,
/*********************************************************************
* AS General Descriptor
*********************************************************************/
/*  AS General Descriptor Length           */ 0x07u,
/*  DescriptorType: AUDIO                  */ 0x24u,
/*  bDescriptorSubtype                     */ 0x01u,
/*  bTerminalLink                          */ 0x05u,
/*  bDelay                                 */ 0x01u,
/*  wFormatTag                             */ 0x01u, 0x00u,
/*********************************************************************
* AS Format Type I Descriptor
*********************************************************************/
/*  AS Format Type I Descriptor Length     */ 0x0Eu,
/*  DescriptorType: AUDIO                  */ 0x24u,
/*  bDescriptorSubtype                     */ 0x02u,
/*  bFormatType                            */ 0x01u,
/*  bNrChannels                            */ 0x02u,
/*  bSubframeSize                          */ 0x02u,
/*  bBitResolution                         */ 0x10u,
/*  bSamFreqType                           */ 0x02u,
/*  tSamFreq                               */ 0x44u, 0xACu, 0x00u, 
                                              0x80u, 0xBBu, 0x00u,
/*********************************************************************
* Endpoint Descriptor
*********************************************************************/
/*  Endpoint Descriptor Length             */ 0x09u,
/*  DescriptorType: ENDPOINT               */ 0x05u,
/*  bEndpointAddress                       */ 0x82u,
/*  bmAttributes                           */ 0x0Du,
/*  wMaxPacketSize                         */ 0xC0u, 0x00u,
/*  bInterval                              */ 0x01u,
/*  bRefresh                               */ 0x00u,
/*  bSynchAddress                          */ 0x00u,
/*********************************************************************
* AS Endpoint Descriptor
*********************************************************************/
/*  Endpoint Descriptor Length             */ 0x07u,
/*  DescriptorType: CS_ENDPOINT            */ 0x25u,
/*  bDescriptorSubtype                     */ 0x01u,
/*  bmAttributes                           */ 0x01u,
/*  bLockDelayUnits                        */ 0x01u,
/*  wLockDelay                             */ 0x01u, 0x00u
};

/*********************************************************************
* String Descriptor Table
*********************************************************************/
const uint8 CYCODE USBFS_STRING_DESCRIPTORS[501u] = {
/*********************************************************************
* Language ID Descriptor
*********************************************************************/
/* Descriptor Length                       */ 0x04u,
/* DescriptorType: STRING                  */ 0x03u,
/* Language Id                             */ 0x09u, 0x04u,
/*********************************************************************
* String Descriptor: "Open Source Hardware Copyright (c) 2015 Peter Allan"
*********************************************************************/
/* Descriptor Length                       */ 0x68u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'O', 0u,(uint8)'p', 0u,(uint8)'e', 0u,(uint8)'n', 0u,(uint8)' ', 0u,
 (uint8)'S', 0u,(uint8)'o', 0u,(uint8)'u', 0u,(uint8)'r', 0u,(uint8)'c', 0u,
 (uint8)'e', 0u,(uint8)' ', 0u,(uint8)'H', 0u,(uint8)'a', 0u,(uint8)'r', 0u,
 (uint8)'d', 0u,(uint8)'w', 0u,(uint8)'a', 0u,(uint8)'r', 0u,(uint8)'e', 0u,
 (uint8)' ', 0u,(uint8)'C', 0u,(uint8)'o', 0u,(uint8)'p', 0u,(uint8)'y', 0u,
 (uint8)'r', 0u,(uint8)'i', 0u,(uint8)'g', 0u,(uint8)'h', 0u,(uint8)'t', 0u,
 (uint8)' ', 0u,(uint8)'(', 0u,(uint8)'c', 0u,(uint8)')', 0u,(uint8)' ', 0u,
 (uint8)'2', 0u,(uint8)'0', 0u,(uint8)'1', 0u,(uint8)'5', 0u,(uint8)' ', 0u,
 (uint8)'P', 0u,(uint8)'e', 0u,(uint8)'t', 0u,(uint8)'e', 0u,(uint8)'r', 0u,
 (uint8)' ', 0u,(uint8)'A', 0u,(uint8)'l', 0u,(uint8)'l', 0u,(uint8)'a', 0u,
 (uint8)'n', 0u,
/*********************************************************************
* String Descriptor: "AudioControl"
*********************************************************************/
/* Descriptor Length                       */ 0x1Au,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'A', 0u,(uint8)'u', 0u,(uint8)'d', 0u,(uint8)'i', 0u,(uint8)'o', 0u,
 (uint8)'C', 0u,(uint8)'o', 0u,(uint8)'n', 0u,(uint8)'t', 0u,(uint8)'r', 0u,
 (uint8)'o', 0u,(uint8)'l', 0u,
/*********************************************************************
* String Descriptor: "ZeroBandwidth"
*********************************************************************/
/* Descriptor Length                       */ 0x1Cu,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'Z', 0u,(uint8)'e', 0u,(uint8)'r', 0u,(uint8)'o', 0u,(uint8)'B', 0u,
 (uint8)'a', 0u,(uint8)'n', 0u,(uint8)'d', 0u,(uint8)'w', 0u,(uint8)'i', 0u,
 (uint8)'d', 0u,(uint8)'t', 0u,(uint8)'h', 0u,
/*********************************************************************
* String Descriptor: "Microphone"
*********************************************************************/
/* Descriptor Length                       */ 0x16u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'M', 0u,(uint8)'i', 0u,(uint8)'c', 0u,(uint8)'r', 0u,(uint8)'o', 0u,
 (uint8)'p', 0u,(uint8)'h', 0u,(uint8)'o', 0u,(uint8)'n', 0u,(uint8)'e', 0u,
/*********************************************************************
* String Descriptor: "Speaker"
*********************************************************************/
/* Descriptor Length                       */ 0x10u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'S', 0u,(uint8)'p', 0u,(uint8)'e', 0u,(uint8)'a', 0u,(uint8)'k', 0u,
 (uint8)'e', 0u,(uint8)'r', 0u,
/*********************************************************************
* String Descriptor: "USB Streaming"
*********************************************************************/
/* Descriptor Length                       */ 0x1Cu,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'U', 0u,(uint8)'S', 0u,(uint8)'B', 0u,(uint8)' ', 0u,(uint8)'S', 0u,
 (uint8)'t', 0u,(uint8)'r', 0u,(uint8)'e', 0u,(uint8)'a', 0u,(uint8)'m', 0u,
 (uint8)'i', 0u,(uint8)'n', 0u,(uint8)'g', 0u,
/*********************************************************************
* String Descriptor: "Active"
*********************************************************************/
/* Descriptor Length                       */ 0x0Eu,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'A', 0u,(uint8)'c', 0u,(uint8)'t', 0u,(uint8)'i', 0u,(uint8)'v', 0u,
 (uint8)'e', 0u,
/*********************************************************************
* String Descriptor: "Active 16 bit"
*********************************************************************/
/* Descriptor Length                       */ 0x1Cu,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'A', 0u,(uint8)'c', 0u,(uint8)'t', 0u,(uint8)'i', 0u,(uint8)'v', 0u,
 (uint8)'e', 0u,(uint8)' ', 0u,(uint8)'1', 0u,(uint8)'6', 0u,(uint8)' ', 0u,
 (uint8)'b', 0u,(uint8)'i', 0u,(uint8)'t', 0u,
/*********************************************************************
* String Descriptor: "Active 24 bit"
*********************************************************************/
/* Descriptor Length                       */ 0x1Cu,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'A', 0u,(uint8)'c', 0u,(uint8)'t', 0u,(uint8)'i', 0u,(uint8)'v', 0u,
 (uint8)'e', 0u,(uint8)' ', 0u,(uint8)'2', 0u,(uint8)'4', 0u,(uint8)' ', 0u,
 (uint8)'b', 0u,(uint8)'i', 0u,(uint8)'t', 0u,
/*********************************************************************
* String Descriptor: "Mac"
*********************************************************************/
/* Descriptor Length                       */ 0x08u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'M', 0u,(uint8)'a', 0u,(uint8)'c', 0u,
/*********************************************************************
* String Descriptor: "PlaylistControl"
*********************************************************************/
/* Descriptor Length                       */ 0x20u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'P', 0u,(uint8)'l', 0u,(uint8)'a', 0u,(uint8)'y', 0u,(uint8)'l', 0u,
 (uint8)'i', 0u,(uint8)'s', 0u,(uint8)'t', 0u,(uint8)'C', 0u,(uint8)'o', 0u,
 (uint8)'n', 0u,(uint8)'t', 0u,(uint8)'r', 0u,(uint8)'o', 0u,(uint8)'l', 0u,
/*********************************************************************
* String Descriptor: "REDOUBLER Random Number Generator"
*********************************************************************/
/* Descriptor Length                       */ 0x44u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'R', 0u,(uint8)'E', 0u,(uint8)'D', 0u,(uint8)'O', 0u,(uint8)'U', 0u,
 (uint8)'B', 0u,(uint8)'L', 0u,(uint8)'E', 0u,(uint8)'R', 0u,(uint8)' ', 0u,
 (uint8)'R', 0u,(uint8)'a', 0u,(uint8)'n', 0u,(uint8)'d', 0u,(uint8)'o', 0u,
 (uint8)'m', 0u,(uint8)' ', 0u,(uint8)'N', 0u,(uint8)'u', 0u,(uint8)'m', 0u,
 (uint8)'b', 0u,(uint8)'e', 0u,(uint8)'r', 0u,(uint8)' ', 0u,(uint8)'G', 0u,
 (uint8)'e', 0u,(uint8)'n', 0u,(uint8)'e', 0u,(uint8)'r', 0u,(uint8)'a', 0u,
 (uint8)'t', 0u,(uint8)'o', 0u,(uint8)'r', 0u,
/*********************************************************************
* String Descriptor: "CDC Communication Interface"
*********************************************************************/
/* Descriptor Length                       */ 0x38u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'C', 0u,(uint8)'D', 0u,(uint8)'C', 0u,(uint8)' ', 0u,(uint8)'C', 0u,
 (uint8)'o', 0u,(uint8)'m', 0u,(uint8)'m', 0u,(uint8)'u', 0u,(uint8)'n', 0u,
 (uint8)'i', 0u,(uint8)'c', 0u,(uint8)'a', 0u,(uint8)'t', 0u,(uint8)'i', 0u,
 (uint8)'o', 0u,(uint8)'n', 0u,(uint8)' ', 0u,(uint8)'I', 0u,(uint8)'n', 0u,
 (uint8)'t', 0u,(uint8)'e', 0u,(uint8)'r', 0u,(uint8)'f', 0u,(uint8)'a', 0u,
 (uint8)'c', 0u,(uint8)'e', 0u,
/*********************************************************************
* String Descriptor: "CDC Data Interface"
*********************************************************************/
/* Descriptor Length                       */ 0x26u,
/* DescriptorType: STRING                  */ 0x03u,
 (uint8)'C', 0u,(uint8)'D', 0u,(uint8)'C', 0u,(uint8)' ', 0u,(uint8)'D', 0u,
 (uint8)'a', 0u,(uint8)'t', 0u,(uint8)'a', 0u,(uint8)' ', 0u,(uint8)'I', 0u,
 (uint8)'n', 0u,(uint8)'t', 0u,(uint8)'e', 0u,(uint8)'r', 0u,(uint8)'f', 0u,
 (uint8)'a', 0u,(uint8)'c', 0u,(uint8)'e', 0u,
/*********************************************************************/
/* Marks the end of the list.              */ 0x00u};
/*********************************************************************/

/*********************************************************************
* Serial Number String Descriptor
*********************************************************************/
const uint8 CYCODE USBFS_SN_STRING_DESCRIPTOR[2] = {
/* Descriptor Length                       */ 0x02u,
/* DescriptorType: STRING                  */ 0x03u
};



/*********************************************************************
* Endpoint Setting Table -- This table contain the endpoint setting
*                           for each endpoint in the configuration. It
*                           contains the necessary information to
*                           configure the endpoint hardware for each
*                           interface and alternate setting.
*********************************************************************/
const T_USBFS_EP_SETTINGS_BLOCK CYCODE USBFS_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[2u] = {
/* IFC  ALT    EPAddr bmAttr MaxPktSize Class ********************/
{0x00u, 0x00u, 0x86u, 0x03u, 0x0002u,   0x01u},
{0x01u, 0x01u, 0x82u, 0x0Du, 0x00C0u,   0x01u}
};
const uint8 CYCODE USBFS_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u] = {
0x01u, 0x01u, 
};
/*********************************************************************
* Config Dispatch Table -- Points to the Config Descriptor and each of
*                          and endpoint setup table and to each
*                          interface table if it specifies a USB Class
*********************************************************************/
const T_USBFS_LUT CYCODE USBFS_DEVICE0_CONFIGURATION0_TABLE[5u] = {
    {0x01u,     &USBFS_DEVICE0_CONFIGURATION0_DESCR},
    {0x02u,     &USBFS_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE},
    {0x00u,    NULL},
    {0x00u,    NULL},
    {0x00u,     &USBFS_DEVICE0_CONFIGURATION0_INTERFACE_CLASS}
};
/*********************************************************************
* Device Dispatch Table -- Points to the Device Descriptor and each of
*                          and Configuration Tables for this Device 
*********************************************************************/
const T_USBFS_LUT CYCODE USBFS_DEVICE0_TABLE[2u] = {
    {0x01u,     &USBFS_DEVICE0_DESCR},
    {0x01u,     &USBFS_DEVICE0_CONFIGURATION0_TABLE}
};
/*********************************************************************
* Device Table -- Indexed by the device number.
*********************************************************************/
const T_USBFS_LUT CYCODE USBFS_TABLE[1u] = {
    {0x01u,     &USBFS_DEVICE0_TABLE}
};

#endif /* USER_SUPPLIED_DESCRIPTORS */

#if defined(USBFS_ENABLE_MSOS_STRING)

    /******************************************************************************
    *  USB Microsoft OS String Descriptor
    *  "MSFT" identifies a Microsoft host
    *  "100" specifies version 1.00
    *  USBFS_GET_EXTENDED_CONFIG_DESCRIPTOR becomes the bRequest value
    *  in a host vendor device/class request
    ******************************************************************************/

    const uint8 CYCODE USBFS_MSOS_DESCRIPTOR[USBFS_MSOS_DESCRIPTOR_LENGTH] = {
    /* Descriptor Length                       */   0x12u,
    /* DescriptorType: STRING                  */   0x03u,
    /* qwSignature - "MSFT100"                 */   (uint8)'M', 0u, (uint8)'S', 0u, (uint8)'F', 0u, (uint8)'T', 0u,
                                                    (uint8)'1', 0u, (uint8)'0', 0u, (uint8)'0', 0u,
    /* bMS_VendorCode:                         */   USBFS_GET_EXTENDED_CONFIG_DESCRIPTOR,
    /* bPad                                    */   0x00u
    };

    /* Extended Configuration Descriptor */

    const uint8 CYCODE USBFS_MSOS_CONFIGURATION_DESCR[USBFS_MSOS_CONF_DESCR_LENGTH] = {
    /*  Length of the descriptor 4 bytes       */   0x28u, 0x00u, 0x00u, 0x00u,
    /*  Version of the descriptor 2 bytes      */   0x00u, 0x01u,
    /*  wIndex - Fixed:INDEX_CONFIG_DESCRIPTOR */   0x04u, 0x00u,
    /*  bCount - Count of device functions.    */   0x01u,
    /*  Reserved : 7 bytes                     */   0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    /*  bFirstInterfaceNumber                  */   0x00u,
    /*  Reserved                               */   0x01u,
    /*  compatibleID    - "CYUSB\0\0"          */   (uint8)'C', (uint8)'Y', (uint8)'U', (uint8)'S', (uint8)'B',
                                                    0x00u, 0x00u, 0x00u,
    /*  subcompatibleID - "00001\0\0"          */   (uint8)'0', (uint8)'0', (uint8)'0', (uint8)'0', (uint8)'1',
                                                    0x00u, 0x00u, 0x00u,
    /*  Reserved : 6 bytes                     */   0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
    };

#endif /* USBFS_ENABLE_MSOS_STRING */

/* DIE ID string descriptor for 8 bytes ID */
#if defined(USBFS_ENABLE_IDSN_STRING)
    uint8 USBFS_idSerialNumberStringDescriptor[USBFS_IDSN_DESCR_LENGTH];
#endif /* USBFS_ENABLE_IDSN_STRING */


/* [] END OF FILE */
