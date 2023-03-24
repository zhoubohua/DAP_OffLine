/********************************************************************************
  * @file    USB_User.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.25
  * @brief   define of USB,extern function 
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __USB_HW_H
#define __USB_HW_H
/*Includes ------------------------------------------------------------------*/
#include"All_Header.h"
/*define of USB------------------------------------------------------------------*/
#define USB_BUFF_DEEP 5
#define USB_EN_PORT           GPIOB
#define USB_EN_PORT_CLK       RCC_APB2Periph_GPIOB
#define USB_EN_PIN            GPIO_Pin_3
#define USB_ON                PBout(3)=0                                                                                    
#define USB_OFF               PBout(3)=1  	
#define USB_CON_PORT          GPIOB
#define USB_CON_PORT_CLK      RCC_APB2Periph_GPIOB
#define USB_CON_PIN           GPIO_Pin_3
#define USB_INSERT            PBin(13)  

#define REPORT_LENGHT 64
#define CUSTOMHID_SIZ_DEVICE_DESC               18
#define CUSTOMHID_SIZ_CONFIG_DESC               41
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define CUSTOMHID_SIZ_REPORT_DESC               33 // 162 33
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04//
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05//
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02//
#define HID_DESCRIPTOR_TYPE                     0x21//
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define CUSTOMHID_SIZ_HID_DESC                  0x09
#define CUSTOMHID_OFF_HID_DESC                  0x12
#define CUSTOMHID_SIZ_STRING_LANGID             4
#define CUSTOMHID_SIZ_STRING_VENDOR             16
#define CUSTOMHID_SIZ_STRING_PRODUCT            24
#define CUSTOMHID_SIZ_STRING_SERIAL             26
#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/*function for other files------------------------------------------------------------------*/
extern const u8 CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC];
extern const u8 CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC];
extern const u8 CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC];
extern const u8 CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID];
extern const u8 CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR];
extern const u8 CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT];
extern u8 CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL];
extern enum Product ProductModel;
void Usb_Init(void);
void USB_SendData(u8 *str);
u8 *CustomHID_GetDeviceDescriptor(u16 Length);
u8 *CustomHID_GetConfigDescriptor(u16 Length);
u8 *CustomHID_GetReportDescriptor(u16 Length);
void SetEPRXCount(void);
void SetEPTXCount(void);
#endif




