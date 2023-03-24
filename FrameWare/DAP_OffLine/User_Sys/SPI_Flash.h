#ifndef __SPI_Flash_h
#define __SPI_Flash_h 
#include "All_Header.h"
#define COM_READ_DEVICE_ID     0XAB
#define COM_READ_COMPANY_ID    0X9F
#define COM_READ_SFDP_REG      0X5A
#define COM_READ_STATU_REG     0X05
#define COM_WRITE_ENABLE       0X06
#define COM_ERASE_SECTOR       0X20
#define COM_WRITE_PAGE         0X02
#define COM_READ_DATA          0X03

#define SPI_NorFlash_CS_LOW()     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define SPI_NorFlash_CS_HIGH()    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET) 


u8 NorFlash_Read_SFDP_Register(u8 add);
void SPI_Flash_Init(void);
u8 NorFlash_Read_DeviceID(void);
u32 NorFlash_Read_CompanyID(void);
u8 NorFlash_Read_SFDP_Register(u8 add);

void MSC_Read_Data(uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
void MSC_Write_Data(uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
#endif
