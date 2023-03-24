/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "ff.h"
#include "All_Header.h"


/* Ϊÿ���豸����һ�������� */
#define TF			    0     // Ԥ��SD��ʹ��
//#define SPI_FLASH		1     // �ⲿSPI Flash
//#define FLASH_INTERNAL		0
/*-----------------------------------------------------------------------*/
/* ��ȡ�豸״̬                                                          */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE pdrv		/* ������ */
)
{

		DSTATUS stat=STA_NOINIT;
	
	switch (pdrv) {
				case TF :
				stat &=~STA_NOINIT;
				return stat;

//				case SPI_FLASH :
//				stat &=~STA_NOINIT;
//				return stat;
		
				default:
				stat = STA_NOINIT;
	}
	return stat;
}

/*-----------------------------------------------------------------------*/
/* �豸��ʼ��                                                            */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
	BYTE pdrv				/* ������ */
)
{
	DSTATUS stat = STA_NOINIT;	
	switch (pdrv) {
			case TF :
			stat =disk_status(TF);
			return stat;		

//			case SPI_FLASH :
//			stat =disk_status(SPI_FLASH);
//			return stat;	      
			
		default:
			stat = STA_NOINIT;
	}
	return stat;
}


/*-----------------------------------------------------------------------*/
/* ����������ȡ�������ݵ�ָ���洢��                                              */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* �豸������(0..) */
	BYTE *buff,		/* ���ݻ����� */
	DWORD sector,	/* �����׵�ַ */
	UINT count		/* ��������(1..128) */
)
{
		DRESULT res;

	switch (pdrv) {
		case TF :
		//FAT_Read_Page(buff,sector,count);
												      if(HAL_SD_ReadBlocks(&hsd, buff, sector,count, HAL_MAX_DELAY) == HAL_OK)
														{
															res =RES_OK;
												 
																while(HAL_SD_GetState(&hsd) == HAL_SD_STATE_BUSY);
																while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
														}
													 return res;	

//		case SPI_FLASH :
//		FAT_NorFlash_Read_Data(buff,sector,count);	
//		res=RES_OK;
//		return res;	
    
		default:
			res = RES_PARERR;
	}
	return res;
}
//void  NorFlash_Erase_Sector(u32 SectorAddress);
//void  NorFlash_Page_Write(u32 SectorAddress,u8* data,u16 length);
//void  NorFlash_Sector_Write(u32 SectorAddress,u8* data,u32 length);
//void  NorFlash_Read_Data(u32 SectorAddress,u8* data,u32 length);
//void  FAT_NorFlash_Read_Data(u8* buff,u32 address,u32 count)
//{
//u32 i=0;
//for(i=0;i<count;i++)
//	{
//	NorFlash_Read_Data (address+(4096*i),&buff[4096*i],4096);
//	}	
//}
//void FAT_NorFlash_Sector_Write(u8* buff,u32 address,u32 count)
/*-----------------------------------------------------------------------*/
/* д������������д��ָ�������ռ���                                      */
/*-----------------------------------------------------------------------*/
#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			  /* �豸������(0..) */
	const BYTE *buff,	/* ��д�����ݵĻ����� */
	DWORD sector,		  /* �����׵�ַ */
	UINT count			  /* ��������(1..128) */
)
{
DRESULT res;
	if (!count) {
		return RES_PARERR;		/* Check parameter */
	}

	switch (pdrv) {
//		case FLASH_INTERNAL :
//		FAT_Write_Page((u8*)buff,sector,count);
//		res=RES_OK;
//		return res;	
		case TF :
	  res = RES_PARERR;
    if(HAL_SD_WriteBlocks(&hsd,(uint8_t *)buff, sector, count, HAL_MAX_DELAY) == HAL_OK)
    {
    	res = RES_OK;
 
        while(HAL_SD_GetState(&hsd) == HAL_SD_STATE_BUSY);
        while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
    }
    return res;
//		case SPI_FLASH :
//		FAT_NorFlash_Sector_Write((u8*)buff,sector,count);
//		res=RES_OK;
//		return res;
    
		default:
			res = RES_PARERR;
	}
	return res;
}
#endif


/*-----------------------------------------------------------------------*/
/* ��������                                                              */
/*-----------------------------------------------------------------------*/
//typedef struct
//{
//  uint32_t CardType;                     /*!< Specifies the card Type                         */
//  
//  uint32_t CardVersion;                  /*!< Specifies the card version                      */

//  uint32_t Class;                        /*!< Specifies the class of the card class           */

//  uint32_t RelCardAdd;                   /*!< Specifies the Relative Card Address             */
//  
//  uint32_t BlockNbr;                     /*!< Specifies the Card Capacity in blocks           */

//  uint32_t BlockSize;                    /*!< Specifies one block size in bytes               */
//  
//  uint32_t LogBlockNbr;                  /*!< Specifies the Card logical Capacity in blocks   */

//  uint32_t LogBlockSize;                 /*!< Specifies logical block size in bytes           */

//}SD_CardInfoTypeDef;
#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* ������ */
	BYTE cmd,		  /* ����ָ�� */
	void *buff		/* д����߶�ȡ���ݵ�ַָ�� */
)
{
	DRESULT res;

	switch (pdrv) {
//		case FLASH_INTERNAL :
// 			switch (cmd) {
//        /* ����������1536*4096/1024/1024=6(MB) */
//        case GET_SECTOR_COUNT:
//          *(DWORD * )buff = 448;		
//        break;
//        /* ������С  */
//        case GET_SECTOR_SIZE :
//          *(WORD * )buff = 2048;
//        break;
//        /* ͬʱ������������ */
//        case GET_BLOCK_SIZE :
//          *(DWORD * )buff = 1;
//        break;  
//        default	:break;			
//      }
		case TF :
	     HAL_SD_CardInfoTypeDef info;
	if(HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER)
	{
		HAL_SD_GetCardInfo(&hsd, &info);
//		*block_num = info.LogBlockNbr;
//		*block_size = info.LogBlockSize;
 			switch (cmd) {
        /* ����������1536*4096/1024/1024=6(MB) */
        case GET_SECTOR_COUNT:
          *(DWORD * )buff =info.LogBlockNbr;		
        break;
        /* ������С  */
        case GET_SECTOR_SIZE :
          *(WORD * )buff =info.LogBlockSize;
        break;
        /* ͬʱ������������ */
        case GET_BLOCK_SIZE :
          *(DWORD * )buff = 8;
        break;  
        default	:break;			
      }
		return  RES_OK;
	}
	return  RES_PARERR;
	
	
	
//		case SPI_FLASH :
// 			switch (cmd) {
//        /* ����������1536*4096/1024/1024=6(MB) */
//        case GET_SECTOR_COUNT:
//          *(DWORD * )buff = 1024;		
//        break;
//        /* ������С  */
//        case GET_SECTOR_SIZE :
//          *(WORD * )buff = 4096;
//        break;
//        /* ͬʱ������������ */
//        case GET_BLOCK_SIZE :
//          *(DWORD * )buff = 1;
//        break;  
//        default	:break;			
//      }			
			
			
			
//		res=RES_OK;
//		return res;	
    
		default:
			res = RES_PARERR;
	}
	return res;
}
#endif

__weak DWORD get_fattime(void) {
	/* ���ص�ǰʱ��� */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}

