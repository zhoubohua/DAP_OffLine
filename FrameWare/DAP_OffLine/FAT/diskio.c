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


/* 为每个设备定义一个物理编号 */
#define TF			    0     // 预留SD卡使用
//#define SPI_FLASH		1     // 外部SPI Flash
//#define FLASH_INTERNAL		0
/*-----------------------------------------------------------------------*/
/* 获取设备状态                                                          */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE pdrv		/* 物理编号 */
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
/* 设备初始化                                                            */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
	BYTE pdrv				/* 物理编号 */
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
/* 读扇区：读取扇区内容到指定存储区                                              */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* 设备物理编号(0..) */
	BYTE *buff,		/* 数据缓存区 */
	DWORD sector,	/* 扇区首地址 */
	UINT count		/* 扇区个数(1..128) */
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
/* 写扇区：见数据写入指定扇区空间上                                      */
/*-----------------------------------------------------------------------*/
#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			  /* 设备物理编号(0..) */
	const BYTE *buff,	/* 欲写入数据的缓存区 */
	DWORD sector,		  /* 扇区首地址 */
	UINT count			  /* 扇区个数(1..128) */
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
/* 其他控制                                                              */
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
	BYTE pdrv,		/* 物理编号 */
	BYTE cmd,		  /* 控制指令 */
	void *buff		/* 写入或者读取数据地址指针 */
)
{
	DRESULT res;

	switch (pdrv) {
//		case FLASH_INTERNAL :
// 			switch (cmd) {
//        /* 扇区数量：1536*4096/1024/1024=6(MB) */
//        case GET_SECTOR_COUNT:
//          *(DWORD * )buff = 448;		
//        break;
//        /* 扇区大小  */
//        case GET_SECTOR_SIZE :
//          *(WORD * )buff = 2048;
//        break;
//        /* 同时擦除扇区个数 */
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
        /* 扇区数量：1536*4096/1024/1024=6(MB) */
        case GET_SECTOR_COUNT:
          *(DWORD * )buff =info.LogBlockNbr;		
        break;
        /* 扇区大小  */
        case GET_SECTOR_SIZE :
          *(WORD * )buff =info.LogBlockSize;
        break;
        /* 同时擦除扇区个数 */
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
//        /* 扇区数量：1536*4096/1024/1024=6(MB) */
//        case GET_SECTOR_COUNT:
//          *(DWORD * )buff = 1024;		
//        break;
//        /* 扇区大小  */
//        case GET_SECTOR_SIZE :
//          *(WORD * )buff = 4096;
//        break;
//        /* 同时擦除扇区个数 */
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
	/* 返回当前时间戳 */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}

