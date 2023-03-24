/********************************************************************************
  * @file    my_sys.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions
  ******************************************************************************
  ******************************************************************************
  */
#include "my_sys.h"
/*******************************************************************************
//Function Name  : delay_1ms(void) 
//Description    : delay 1 ms
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void delay_1ms(void)
{
u16 i;
for(i=0;i<18660;i++);
}
/*******************************************************************************
//Function Name  : delay_1us(void) 
//Description    : delay 1 us
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void delay_1us(void)
{
u16 i;
for(i=0;i<7;i++);
}
/*******************************************************************************
//Function Name  : delay_10us(void) 
//Description    : delay 10 us
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void delay_10us(void)
{
u16 i;
for(i=0;i<177;i++);
}
/*******************************************************************************
//Function Name  : delay_ms(u16 nms) 
//Description    : delay x ms
//USE            : extern call
//Input          : the num of ms  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void delay_ms(u16 nms)
{
while(nms--)delay_1ms();
}
/*******************************************************************************
//Function Name  : Mem_Copy(u8* scr,u8* aim,u8 length)
//Description    : copy one buff to another buff
//USE            : extern call
//Input          : the source address,the aim address,the length 
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Mem_Copy(u8* scr,u8* aim,u8 length)
{
u8 i=0;
	for(i=0;i<length;i++)
	{
	aim[i]=scr[i];
	}
}
/*******************************************************************************
//Function Name  : array_find(u8* table1,u8* table2,u8 l1,u8 l2)
//Description    : find one buff from another buff
//USE            : extern call
//Input          : the find buff address,the finded buff address,the length of find, the length of finded
//Output         : None
//Return         : first find position
//EDITER         : ZBH
*******************************************************************************/
signed char array_find(u8* table1,u8* table2,u8 l1,u8 l2)
{
u8 i=0;
u8 j=0;
	for(i=0;i<l2;i++)
	{
		if(table2[i]==table1[0])
		{
		for(j=0;j<l1;j++)
			{
			if(table2[i+j]==table1 [j])
			{
			  if(j==(l1-1))
				{
				return i;
				}
			}
       else  
				 break ;
			}
		}
	}
	return -1;
}
/*******************************************************************************
//Function Name  : Maopao_Sort(u16 *dat, u8 leng)
//Description    : bubble sort
//USE            : extern call
//Input          : the sort buff adress ,the buff length
//Output         : the sort buff
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Maopao_Sort(u16 *dat, u8 leng)
{
	u16 i,j;
	u16 buf;
	for(j=0;j<leng-1;j++)
	for(i=0;i<leng-j-1;i++)
	if(dat[i]>dat[i+1]){
	buf=dat[i];
	dat[i]=dat[i+1];
	dat[i+1]=buf;
	}
}
/*******************************************************************************
//Function Name  : Set_NVIC_Adress(void)
//Description    : set NVIC base adress
//USE            : external call
//Input          : None
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Set_NVIC_Adress(void)
{ 
//#ifdef DFU_DONWLOAD 
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x08003000);
//#else
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
//#endif
}

//int fputc(int ch, FILE *f)
//{
//	unsigned  char bCh=0;
//	bCh=ch;
//	HAL_UART_Transmit(&huart1 ,&bCh,1,100);
// return  (ch);
//}
