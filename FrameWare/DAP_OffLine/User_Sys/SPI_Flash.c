#include "SPI_Flash.h"
typedef struct
{
  u32  Sector_Size;
	u32  Sector_Number;
}SPI_FLASH;
SPI_FLASH SPI_Flash;

void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  MX_SPI1_Init();
}
void SPI_Flash_Init(void)
{
	u8 temp=0;
	u32 message=0;
  SPI1_Init();
	temp =NorFlash_Read_CompanyID();
  message=(1<<temp);
	SPI_Flash.Sector_Size=4096;
	SPI_Flash.Sector_Number=message/SPI_Flash.Sector_Size;
}
	

u8 SPI_NorFlash_SendByte(u8 byte)
{
	u8 data[1]={0};
	HAL_SPI_TransmitReceive(&hspi1,&byte,data,1, 1000);
	return data[0];
}

u8 NorFlash_Read_DeviceID(void)
{
u8 id=0;
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_READ_DEVICE_ID);
SPI_NorFlash_SendByte(0xff);	
SPI_NorFlash_SendByte(0xff);	
SPI_NorFlash_SendByte(0xff);	
id=SPI_NorFlash_SendByte(0xff);		
SPI_NorFlash_CS_HIGH();
return id;
}

u32 NorFlash_Read_CompanyID(void)
{
u32 id=0;
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_READ_COMPANY_ID);
id=SPI_NorFlash_SendByte(0xff);
id=id<<8;	
id|=SPI_NorFlash_SendByte(0xff);	
id=id<<8;		
id|=SPI_NorFlash_SendByte(0xff);	
SPI_NorFlash_CS_HIGH();
return id;
}
u8 NorFlash_Read_SFDP_Register(u8 add)
{
u8 dat=0;
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_READ_SFDP_REG);
SPI_NorFlash_SendByte(0x00);	
SPI_NorFlash_SendByte(0x00);	
SPI_NorFlash_SendByte(add);	
SPI_NorFlash_SendByte(0xff);	
dat=SPI_NorFlash_SendByte(0xff);	
SPI_NorFlash_CS_HIGH();
return dat;
}
void NorFlash_Write_Enable(void)
{
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_WRITE_ENABLE);	
SPI_NorFlash_CS_HIGH();
}
u8 NorFlash_Read_Statu(void)
{
u8 statu=0;
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_READ_STATU_REG);
statu=SPI_NorFlash_SendByte(0xff);	
SPI_NorFlash_CS_HIGH();
return statu;
}

void  NorFlash_Erase_Sector(u32 SectorAddress)
{
u8 add_h=0;
u8 add_m=0;
u8 add_l=0;	
add_l=SectorAddress;
add_m=SectorAddress>>8;	
add_h=SectorAddress>>16;
NorFlash_Write_Enable();
while(NorFlash_Read_Statu()&0x01);//BUSY
	
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_ERASE_SECTOR);
SPI_NorFlash_SendByte(add_h);
SPI_NorFlash_SendByte(add_m);
SPI_NorFlash_SendByte(add_l);
SPI_NorFlash_CS_HIGH();	
while(NorFlash_Read_Statu()&0x01);//BUSY	
}

void  NorFlash_Page_Write(u32 SectorAddress,u8* data,u16 length)
{
u16 count=0;
u8 add_h=0;
u8 add_m=0;
u8 add_l=0;	
add_l=SectorAddress;
add_m=SectorAddress>>8;	
add_h=SectorAddress>>16;
NorFlash_Write_Enable();
while(NorFlash_Read_Statu()&0x01);//BUSY
	
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_WRITE_PAGE);
SPI_NorFlash_SendByte(add_h);
SPI_NorFlash_SendByte(add_m);
SPI_NorFlash_SendByte(add_l);
for(count=0;count<length;count++)	
	{
	SPI_NorFlash_SendByte(data[count]);
	}
SPI_NorFlash_CS_HIGH();	
while(NorFlash_Read_Statu()&0x01);//BUSY	
}
void  NorFlash_Sector_Write(u32 SectorAddress,u8* data,u32 length)
{
u8 page_count=0;
	NorFlash_Erase_Sector(SectorAddress);
	for(page_count=0;page_count<16;page_count++)
	{
	NorFlash_Page_Write(page_count*256+SectorAddress,&data[page_count*256],256);	
	}
}
void  NorFlash_Read_Data(u32 SectorAddress,u8* data,u32 length)
{
u32 count=0;
u8 add_h=0;
u8 add_m=0;
u8 add_l=0;	
add_l=SectorAddress;
add_m=SectorAddress>>8;	
add_h=SectorAddress>>16;
//NorFlash_Write_Enable();
//while(NorFlash_Read_Statu()&0x01);//BUSY
	
SPI_NorFlash_CS_LOW() ;	
SPI_NorFlash_SendByte(COM_READ_DATA);
SPI_NorFlash_SendByte(add_h);
SPI_NorFlash_SendByte(add_m);
SPI_NorFlash_SendByte(add_l);
for(count=0;count<length;count++)	
	{
	data[count]=SPI_NorFlash_SendByte(0XFF);
	}
SPI_NorFlash_CS_HIGH();	
//while(NorFlash_Read_Statu()&0x01);//BUSY	
}

void  FAT_NorFlash_Read_Data(u8* buff,u32 address,u32 count)
{
u32 i=0;
for(i=0;i<count;i++)
	{
	NorFlash_Read_Data ((address+i)*4096,&buff[4096*i],4096);
	}	
}
void FAT_NorFlash_Sector_Write(u8* buff,u32 address,u32 count)
{
u32 i=0;
for(i=0;i<count;i++)
	{
		NorFlash_Sector_Write ((address+i)*4096,&buff[4096*i],4096);
	}	
}




void MSC_Read_Data(uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
u32 i=0;
for(i=0;i<blk_len;i++)
	{
	NorFlash_Read_Data ((blk_addr+i)*SPI_Flash.Sector_Size,&buf[SPI_Flash.Sector_Size*i],SPI_Flash.Sector_Size);
	}	
}
void MSC_Write_Data(uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
u32 i=0;
for(i=0;i<blk_len;i++)
	{
		NorFlash_Sector_Write ((blk_addr+i)*SPI_Flash.Sector_Size,&buf[SPI_Flash.Sector_Size*i],SPI_Flash.Sector_Size);
	}	
}



