#include "Internal_Flash.h"

void Internal_Flash_Read(uint8_t* buff,uint32_t add,uint16_t length)
{
 memcpy(buff,(uint8_t *)add,length);
}

void Internal_Flash_Erase(uint32_t page_start_add,uint16_t page_num)
{
HAL_FLASH_Unlock();
    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = page_start_add ;
    f.NbPages =page_num;
    uint32_t PageError = 0;
    HAL_FLASHEx_Erase(&f, &PageError);
HAL_FLASH_Lock();
}

void Internal_Flash_Write(uint8_t* buff,uint32_t add,uint16_t length)
{
	uint16_t i=0;
HAL_FLASH_Unlock();	
	for(i=0;i<length;i+=4)
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,add + i , *(uint32_t *)(&buff[i]));
HAL_FLASH_Lock();	
}


