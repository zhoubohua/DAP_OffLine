/********************************************************************************
  * @file    USB_HW.c
  * @author  ZBH
  * @version V1.0
  * @date    2017.05.31
  * @brief   This file is USB int and receive or send
  ******************************************************************************
  *if change or add USB message must changge this file about USB describe, include 
	*HID ,PID ,report length . the buff for receive data also need change .
  *******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "USB_HW.h"
#ifdef HID_EN
u8 USB_ReceiveFlg=0 ;                 //global variable for USB receive data flag
u8 Receive_Buffer[64];                    //global variable for USB receive data buff
u8 Translate_Buffer[USB_BUFF_DEEP][64];   //global variable for USB send data buff
u8 USB_Buff_In_Count=0;                   //global variable for USB send buff in number
u8 USB_Buff_Out_Count=0;                  //global variable for USB send buff out number
/*******************************************************************************
********************************************************************************
**************************All Description  about USB****************************
********************************************************************************
*******************************************************************************/
/* USB Standard Device Descriptor */
const u8 CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize40*/
    0x81,                       /*idVendor (0x0483)*/
    0x04,
    0x70,                       /*idProduct = 0x5750*/
    0x57,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describingmanufacturer */
    2,                          /*Index of string descriptor describing product*/
    3,                          /*Index of string descriptor describing thedevice serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* CustomHID_DeviceDescriptor */

const u8 CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] = 
{ 
//#ifdef 1 
0x05, 0x8c, /* USAGE_PAGE (ST Page) */ 
0x09, 0x01, /* USAGE (Demo Kit) */ 
0xa1, 0x01, /* COLLECTION (Application) */ 
// The Input report 
0x09,0x03, // USAGE ID - Vendor defined 
0x15,0x00, // LOGICAL_MINIMUM (0) 
0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255) 
0x75,0x08, // REPORT_SIZE (8) ////////////////////////////////////////////////
0x95,0x40, // REPORT_COUNT (20) 
0x81,0x02, // INPUT (Data,Var,Abs) 
// The Output report 
0x09,0x04, // USAGE ID - Vendor defined 
0x15,0x00, // LOGICAL_MINIMUM (0) 
0x26,0x00,0xFF, // LOGICAL_MAXIMUM (255) 
0x75,0x08, // REPORT_SIZE (8) 
0x95,0x40, // REPORT_COUNT (20) 
0x91,0x02, // OUTPUT (Data,Var,Abs) 
0xc0 /* END_COLLECTION */ 
}; /* CustomHID_ReportDescriptor */ 

const u8 CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuation Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    CUSTOMHID_SIZ_CONFIG_DESC,
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0xA0,         /* bmAttributes: Bus powered */
                  /*Bus powered: 7th bit, Self Powered: 6th bit, Remote wakeup: 5th bit, reserved: 4..0 bits */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus */
    /************** Descriptor of Custom HID interface ****************/
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID HID ********************/
    0x09,         /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
    0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    CUSTOMHID_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Custom HID endpoints ******************/
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */
    0x82,          /* bEndpointAddress: Endpoint Address (IN) */               
    0x03,          /* bmAttributes: Interrupt endpoint */
    0x40,//0x02,          /* wMaxPacketSize: 20 Bytes max */
    0x00,
    0x01,          /* bInterval: Polling Interval (21 ms) */
    0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
    0x01,	/* bEndpointAddress: */
    0x03,	/* bmAttributes: Interrupt endpoint */
    0x40,//0x02,	/* wMaxPacketSize: 20 Bytes max  */
    0x00,
    0x01,	/* bInterval: Polling Interval (32 ms) */
  }
  ; /* CustomHID_ConfigDescriptor */
const u8 CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
  {
    CUSTOMHID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */
const u8 CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
  {
    CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    // Manufacturer: "STMicroelectronics" 
    'A', 0, 'A', 0, 'A', 0,'A', 0, 'A', 0, 'A', 0, 'A', 0
  };
const u8 CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
  {
    CUSTOMHID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'B', 0, 'B', 0, 'B', 0,'B', 0,'B', 0, 'B', 0, 'B', 0, 'B', 0, 'B', 0, 'B', 0, 'B', 0
  };
u8 CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
  {
    CUSTOMHID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'C', 0, 'C', 0, 'C', 0,'C', 0,'C', 0, 'C', 0, 'C', 0
  };	
/*******************************************************************************
********************************************************************************
***********************Format description  about USB****************************
********************************************************************************
*******************************************************************************/
ONE_DESCRIPTOR Device_Descriptor =
  {
    (u8*)CustomHID_DeviceDescriptor,
    CUSTOMHID_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (u8*)CustomHID_ConfigDescriptor,
    CUSTOMHID_SIZ_CONFIG_DESC
  };
ONE_DESCRIPTOR CustomHID_Report_Descriptor =
  {
    (u8 *)CustomHID_ReportDescriptor,
    CUSTOMHID_SIZ_REPORT_DESC
  };

/*******************************************************************************
********************************************************************************
**************************All fuction  about USB********************************
********************************************************************************
*******************************************************************************/

/*******************************************************************************
//Function Name  : USB_GPIO_Init(void)
//Description    : USB control gpio init,D+ pull up control,cable insert flag io
//USE            : internal call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
********************************************************************************/
void USB_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(USB_EN_PORT_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(USB_CON_PORT_CLK ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = USB_EN_PIN;//USB_EN
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(USB_EN_PORT, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = USB_CON_PIN;	//USB_CON_FLAG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(USB_CON_PORT, &GPIO_InitStructure);
	USB_ON;
}	
/*******************************************************************************
//Function Name  : Set_USBClock(void)
//Description    : USB syscolck  set to 48 mhz
//USE            : internal call
//Input          : None
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Set_USBClock(void)
{
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);  // 72MHZ sysclk
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}
/*******************************************************************************
//Function Name  : USB_Interrupts_Config(void)
//Description    : config USB interrupt
//USE            : internal call
//Input          : None
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_InitStructure.NVIC_IRQChannel =USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
//Function Name  : Usb_Init(void)
//Description    : config USB device
//USE            : external call
//Input          : None
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Usb_Init(void)
{
	USB_GPIO_Init();
	USB_Interrupts_Config();
	Set_USBClock();//usb systine set  ,48 mhz
	USB_Init();
}

/*******************************************************************************
//Function Name  : USB_Send_Drive(u8 *str)
//Description    : check USB_Buff_Out_Count and USB_Buff_in_Count to decide send data or not
//USE            : only call in this file
//Input          : None.
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void USB_Send_Drive(void)
{
	if(USB_Buff_In_Count!=USB_Buff_Out_Count)
	{
		   UserToPMABufferCopy(&Translate_Buffer[USB_Buff_Out_Count][0], ENDP2_TXADDR, REPORT_LENGHT);
			 SetEPTxValid(ENDP2);
	}
}
/*******************************************************************************
//Function Name  : USB_SendData(u8 *str)
//Description    : move send data to usb send buff and  trig send
//USE            : external call
//Input          : data array first address
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void USB_SendData(u8 *str)
{
Mem_Copy (str,&Translate_Buffer[USB_Buff_In_Count][0],64);
USB_Buff_In_Count++;
if(USB_Buff_In_Count==USB_BUFF_DEEP)USB_Buff_In_Count=0;
USB_Send_Drive();	
}
/*******************************************************************************
//Function Name  : *CustomHID_GetDeviceDescriptor(u16 Length)
//Description    : send Device Descriptor
//USE            : USB auto call
//Input          : Device Descriptor length
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
u8 *CustomHID_GetDeviceDescriptor(u16 Length)
{
 return Standard_GetDescriptorData(Length, &Device_Descriptor);
}
/*******************************************************************************
//Function Name  : *CustomHID_GetConfigDescriptor(u16 Length)
//Description    : send Config Descriptor
//USE            : USB auto call
//Input          : Device Descriptor length
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
u8 *CustomHID_GetConfigDescriptor(u16 Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}
/*******************************************************************************
//Function Name  : EP1_OUT_Callback(void)
//Description    : EP1 receive data call back
//USE            : USB auto call
//Input          : None.
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/

void EP1_OUT_Callback(void)
{
		USB_ReceiveFlg = TRUE;
		PMAToUserBufferCopy(Receive_Buffer, ENDP1_RXADDR, REPORT_LENGHT);
		SetEPRxStatus(ENDP1, EP_RX_VALID);
}		
/*******************************************************************************
//Function Name  : EP2_IN_Callback(void)
//Description    : EP2 send end call back,check has data to send or not
//USE            : USB auto call
//Input          : None
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void EP2_IN_Callback(void)
{
USB_Buff_Out_Count++;
if(USB_Buff_Out_Count==USB_BUFF_DEEP)USB_Buff_Out_Count=0;
USB_Send_Drive();	
}
/*******************************************************************************
//Function Name  : *CustomHID_GetReportDescriptor(u16 Length)
//Description    : send Report Descriptor
//USE            : USB auto call
//Input          : None.
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
u8 *CustomHID_GetReportDescriptor(u16 Length)
{
		return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}
/*******************************************************************************
//Function Name  : SetEPRXCount(void)
//Description    : set USB point1 repoet length
//USE            : USB auto call
//Input          : None.
//Output         : None. 
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void SetEPRXCount(void)
{
		SetEPRxCount(ENDP1, REPORT_LENGHT);//
}
/*******************************************************************************
//Function Name  : SetEPRXCount(void)
//Description    : set USB point2 repoer length
//USE            : USB auto call
//Input          : None.
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void SetEPTXCount(void)
{
		SetEPTxCount(ENDP2, REPORT_LENGHT);//
}
#endif


