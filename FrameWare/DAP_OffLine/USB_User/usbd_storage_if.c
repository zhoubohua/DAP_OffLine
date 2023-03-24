/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @version        : v2.0_Cube
  * @brief          : Memory management layer.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"

/* USER CODE BEGIN INCLUDE */
#include "All_Header.h"
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief Usb mass storage device module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @brief Private defines.
  * @{
  */

//#define STORAGE_LUN_NBR                  2
//#define STORAGE_BLK_NBR                  48
//#define STORAGE_BLK_SIZ                  0x800

///* USER CODE BEGIN PRIVATE_DEFINES */
//						#define     FLASH1_START_ADDR            0x00000000    //
//						#define     FLASH1_PAGE_NBR              2048            // 64k
//						#define     FLASH1_PAGE_SIZE             4096




//						#define     FLASH1_START_ADDR            0x08010000    //
//						#define     FLASH1_PAGE_NBR              32             // 64k
//						#define     FLASH1_PAGE_SIZE             0x800

						#define     FLASH2_START_ADDR            0x08010000    //
						#define     FLASH2_PAGE_NBR              200             // 64k
						#define     FLASH2_PAGE_SIZE             0x800
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN INQUIRY_DATA_FS */
/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1' ,                     /* Version      : 4 Bytes */
//	/* LUN 1 */
//  0x00,
//  0x80,
//  0x02,
//  0x02,
//  (STANDARD_INQUIRY_DATA_LEN - 5),
//  0x00,
//  0x00,
//  0x00,
//  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
//  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
//  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
//  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
};
/* USER CODE END INQUIRY_DATA_FS */

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;
extern SD_HandleTypeDef hsd;
/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t STORAGE_Init_FS(uint8_t lun);
static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_FS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS(void);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
  STORAGE_Init_FS,
  STORAGE_GetCapacity_FS,
  STORAGE_IsReady_FS,
  STORAGE_IsWriteProtected_FS,
  STORAGE_Read_FS,
  STORAGE_Write_FS,
  STORAGE_GetMaxLun_FS,
  (int8_t *)STORAGE_Inquirydata_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes over USB FS IP
  * @param  lun:
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Init_FS(uint8_t lun)
{
  /* USER CODE BEGIN 2 */
  return (USBD_OK);
  /* USER CODE END 2 */
}

/**
  * @brief  .
  * @param  lun: .
  * @param  block_num: .
  * @param  block_size: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 3 */
	if(lun==0)
	{
	HAL_SD_CardInfoTypeDef info;
	if(HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER)
	{
		HAL_SD_GetCardInfo(&hsd, &info);
		*block_num = info.LogBlockNbr;
		*block_size = info.LogBlockSize;
 
		return  USBD_OK;
	}
	return  USBD_FAIL;
//	*block_num  = FLASH1_PAGE_NBR;
//  *block_size = FLASH1_PAGE_SIZE;
	}
//	if(lun==1)
//	{
//	*block_num  = FLASH2_PAGE_NBR;
//  *block_size = FLASH2_PAGE_SIZE;
//	}  
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsReady_FS(uint8_t lun)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 6 */
	    int8_t ret = USBD_FAIL;
										if(lun == 0)
											{
										      if(HAL_SD_ReadBlocks(&hsd, buf, blk_addr,  blk_len, HAL_MAX_DELAY) == HAL_OK)
														{
															ret = USBD_OK;
												 
																while(HAL_SD_GetState(&hsd) == HAL_SD_STATE_BUSY);
																while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
														}
													 return ret;	
//												MSC_Read_Data(buf,blk_addr, blk_len);
//										   return USBD_OK;
										}
//										if(lun == 1)
//											{
//										   memcpy(buf,(uint8_t *)(FLASH2_START_ADDR + blk_addr*FLASH2_PAGE_SIZE),blk_len*FLASH2_PAGE_SIZE);
//										   return USBD_OK;
//										}
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 7 */
if(lun == 0)
{
//uint16_t i;
//    HAL_FLASH_Unlock();

//    FLASH_EraseInitTypeDef f;
//    f.TypeErase = FLASH_TYPEERASE_PAGES;
//    f.PageAddress = FLASH1_START_ADDR + blk_addr*FLASH1_PAGE_SIZE ;
//    f.NbPages = blk_len;
//    uint32_t PageError = 0;
//    HAL_FLASHEx_Erase(&f, &PageError);

//    for(i=0;i<blk_len*FLASH1_PAGE_SIZE;i+=4)
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,FLASH1_START_ADDR + blk_addr*FLASH1_PAGE_SIZE + i , *(uint32_t *)(&buf[i]));

//    HAL_FLASH_Lock();
//	MSC_Write_Data(buf,blk_addr,blk_len);
//    return USBD_OK;
	int8_t ret = USBD_FAIL;
    if(HAL_SD_WriteBlocks(&hsd, buf, blk_addr, blk_len, HAL_MAX_DELAY) == HAL_OK)
    {
    	ret = USBD_OK;
 
        while(HAL_SD_GetState(&hsd) == HAL_SD_STATE_BUSY);
        while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
    }
 
    return ret;
}
//if(lun == 1)
//{
//uint16_t i;
//    HAL_FLASH_Unlock();

//    FLASH_EraseInitTypeDef f;
//    f.TypeErase = FLASH_TYPEERASE_PAGES;
//    f.PageAddress = FLASH2_START_ADDR + blk_addr*FLASH2_PAGE_SIZE ;
//    f.NbPages = blk_len;
//    uint32_t PageError = 0;
//    HAL_FLASHEx_Erase(&f, &PageError);

//    for(i=0;i<blk_len*FLASH2_PAGE_SIZE;i+=4)
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,FLASH2_START_ADDR + blk_addr*FLASH2_PAGE_SIZE + i , *(uint32_t *)(&buf[i]));

//    HAL_FLASH_Lock();
//    return USBD_OK;
//}
//return USBD_FAIL;	
  return (USBD_OK);
  /* USER CODE END 7 */
}

/**
  * @brief  .
  * @param  None
  * @retval .
  */
int8_t STORAGE_GetMaxLun_FS(void)
{
  /* USER CODE BEGIN 8 */
  return (1 - 1);
  /* USER CODE END 8 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */




//	MSC_Write_Data(buf,blk_addr,blk_len); MSC_Read_Data(buf,blk_addr, blk_len);



