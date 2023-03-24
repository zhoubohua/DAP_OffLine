/********************************************************************************
  * @file    OLED_User.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions
  ******************************************************************************
  ******************************************************************************
  */
#include "OLED_User.h"
extern const uint8_t CODE_8_16[][16];
/*******************************************************************************
//Function Name  :  
//Description    : delay 1 ms
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
//void OLED_Init(void)
//{

//}


uint8_t OLED_Init_CMD[ ] =
{
	0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8,
	0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1,
	0xDA, 0x12, 0xDB, 0x30, 0x8D, 0x14, 0xAF, 0x20, 0x00
};

void OLED_init(void)
{
	HAL_I2C_Mem_Write_DMA(&hi2c2, OLED_I2C_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, OLED_Init_CMD, 29);
}

uint8_t OLED_GRAMbuf[8][512];

uint8_t OLED_CMDbuf[8][4] = {0};
uint8_t I2C1_MemTxFinshFlag = 1;
uint8_t CountFlag = 0; 
uint8_t BufFinshFlag = 0;
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(BufFinshFlag)
	{
		HAL_I2C_Mem_Write_DMA(&hi2c2,0x78,0x40,I2C_MEMADD_SIZE_8BIT,OLED_GRAMbuf[CountFlag],128);
	}
}
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(CountFlag == 7)
	{
		BufFinshFlag = 0;
		CountFlag = 0;
	}
	if(BufFinshFlag)
	{
		CountFlag ++;
		HAL_I2C_Master_Transmit_DMA(&hi2c2,0x78,OLED_CMDbuf[CountFlag],4);
	}
}
void OLED_set_pos(uint16_t x, uint8_t y)
{
	OLED_CMDbuf[y][0] = 0x00;
	OLED_CMDbuf[y][1] = 0xb0 + y;
	OLED_CMDbuf[y][2] = 0x10;
	OLED_CMDbuf[y][3] = 0x00;
	
}

void OLED_refresh_gram(void)
{	
	uint16_t i;
		
	if(BufFinshFlag == 0)
	{
		for(i = 0; i < 8; i ++ )
		{
			OLED_set_pos(0, i);
		}
		BufFinshFlag = 1;
		HAL_I2C_Master_Transmit_DMA(&hi2c2,0x78,OLED_CMDbuf[0],4);
	}
}
void OLED_operate_gram(uint8_t statu)
{
	if (statu == 1)
	{
			memset(OLED_GRAMbuf,0xff,sizeof(OLED_GRAMbuf));
	}
	else if(statu == 0)
	{
			memset(OLED_GRAMbuf,0x00,sizeof(OLED_GRAMbuf));
	}	
}

void OLED_Show_Char(uint16_t x,uint8_t y,char data)
{
	uint16_t i=0;
	for(i=0;i<8;i++)
	{
		OLED_GRAMbuf[y<<1][i+x] =CODE_8_16[(uint8_t)data-32][2*i];//0xff;//
		OLED_GRAMbuf[(y<<1)+1][i+x] =CODE_8_16[(uint8_t)data-32][2*i+1];//0xff;//
	}
}
uint8_t  OLED_Show_String(uint8_t x,uint8_t y,char* data)
{
	uint16_t i=0;
//	for(i=0;i<length;i++)
//	{
//   OLED_Show_Char(x+i*8,y,data[i]);
//	}
	while(data[i]!='\0')
	{
	OLED_Show_Char(x+i*8,y,data[i]);
		i++;
	}
	return i;
}
void  OLED_Show_Buff(uint8_t x,uint8_t y,char* data,uint8_t length)
{
	uint16_t i=0;
	for(i=0;i<length;i++)
	{
   OLED_Show_Char(x+i*8,y,data[i]);
	}
}

uint8_t OLED_Roll_Flag=0x00;
uint16_t Roll_Wide=383;
void OLED_Roll(void)
{
uint16_t i=0;
uint8_t buff0=0;
uint8_t buff1=0;
	
if(OLED_Roll_Flag&0x01)
		{
      buff0=OLED_GRAMbuf[0][0];
			buff1=OLED_GRAMbuf[1][0];
			for(i=0;i<Roll_Wide;i++)
			{
			OLED_GRAMbuf[0][i]=OLED_GRAMbuf[0][i+1];
			OLED_GRAMbuf[1][i]=OLED_GRAMbuf[1][i+1];
			}	
      OLED_GRAMbuf[0][Roll_Wide]=buff0;
			OLED_GRAMbuf[1][Roll_Wide]=buff1;			
		}	
if(OLED_Roll_Flag&0x02)
		{
      buff0=OLED_GRAMbuf[2][0];
			buff1=OLED_GRAMbuf[3][0];
			for(i=0;i<Roll_Wide;i++)
			{
			OLED_GRAMbuf[2][i]=OLED_GRAMbuf[2][i+1];
			OLED_GRAMbuf[3][i]=OLED_GRAMbuf[3][i+1];
			}	
      OLED_GRAMbuf[2][Roll_Wide]=buff0;
			OLED_GRAMbuf[3][Roll_Wide]=buff1;			
		}		
if(OLED_Roll_Flag&0x04)
		{
      buff0=OLED_GRAMbuf[4][0];
			buff1=OLED_GRAMbuf[5][0];
			for(i=0;i<Roll_Wide;i++)
			{
			OLED_GRAMbuf[4][i]=OLED_GRAMbuf[4][i+1];
			OLED_GRAMbuf[5][i]=OLED_GRAMbuf[5][i+1];
			}	
      OLED_GRAMbuf[4][Roll_Wide]=buff0;
			OLED_GRAMbuf[5][Roll_Wide]=buff1;			
		}	
if(OLED_Roll_Flag&0x08)
		{
      buff0=OLED_GRAMbuf[6][0];
			buff1=OLED_GRAMbuf[7][0];
			for(i=0;i<Roll_Wide;i++)
			{
			OLED_GRAMbuf[6][i]=OLED_GRAMbuf[6][i+1];
			OLED_GRAMbuf[7][i]=OLED_GRAMbuf[7][i+1];
			}	
      OLED_GRAMbuf[6][Roll_Wide]=buff0;
			OLED_GRAMbuf[7][Roll_Wide]=buff1;			
		}		
}

void OLED_Roll_Set(uint8_t line,uint8_t statu,uint8_t length)
{

if(statu)
	{
   OLED_Roll_Flag|=(0x01<<line);
	}
	else 
	{
	OLED_Roll_Flag&=(~(0x01<<line));
	}
	Roll_Wide=(length+1)*8;
}
void OLED_Invert_Set(uint8_t line,uint8_t statu)
{
static 	uint8_t OLED_Invert_Flag=0x00;
uint16_t i=0;
if(statu)
	{
   if(OLED_Invert_Flag&(0x01<<line))
		 {
		 return;
		 }
		 else
		 {
		  for(i=0;i<256;i++)
			 {
			 OLED_GRAMbuf[line*2][i]=~OLED_GRAMbuf[line*2][i];
			 OLED_GRAMbuf[line*2+1][i]=~OLED_GRAMbuf[line*2+1][i]; 
			 }
		 OLED_Invert_Flag|=(0x01<<line);
		 }
	}
else	
	{
   if(OLED_Invert_Flag&(0x01<<line))
		 {
		  for(i=0;i<256;i++)
			 {
			 OLED_GRAMbuf[line*2][i]=~OLED_GRAMbuf[line*2][i];
			 OLED_GRAMbuf[line*2+1][i]=~OLED_GRAMbuf[line*2+1][i]; 
			 }	
      OLED_Invert_Flag&=(~(0x01<<line));			 
		 }
		 else
		 {
		 return;
		 }
	}
}


///////////////////////////////////

void OLED_Test(void)
{
//static uint8_t count=0;
//	if(count%2==0)
//	{
//		OLED_Roll_Set(2,1);
//	OLED_Invert_Set(2,1);
//	}
//	else
//	{
//	OLED_Roll_Set(2,0);
//	OLED_Invert_Set(2,0);	
//	}
//count++;
	
	
//uint8_t i=0;	
	OLED_Show_String(0,1,"123456789012345678901234567890123456");
//	OLED_Roll_Set(0,1);
//	OLED_Invert_Set(0,1);
	OLED_Show_String(0,0,"123456789012345678901234567890123456");
//	OLED_Roll_Set(1,1);
//	OLED_Invert_Set(1,1);
//	OLED_Show_Char(0,0,'W');
//OLED_Show_Char(1,1,'Q');
//	OLED_Show_Char(2,2,'S');
//	OLED_Show_Char(3,3,'T');
//	OLED_operate_gram(1);
//OLED_operate_gram(0);	
//OLED_refresh_gram();	
//			for(i=0;i<8;i++)
//		{
//		OLED_GRAMbuf[0][i] =tablle[2*i];
//		OLED_GRAMbuf[1][i] =tablle[2*i+1];
//		}
//		OLED_refresh_gram();
}

