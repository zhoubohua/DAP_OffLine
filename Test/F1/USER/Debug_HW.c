/*******************************************************************************
  * @file    Debug_HW.c
  * @author  ZBH
  * @version 
  * @date   
  * @brief  
  ******************************************************************************
	//
	//
	//
  ******************************************************************************
  */
/*Includes ------------------------------------------------------------------*/
#include "Debug_HW.h" 
u8 Debug_Receive_Buff[64];
u8 Debug_Receive_Count=0;
u8 Debug_Receive_Flag=0;
/*******************************************************************************
********************************************************************************
**************************All fuction  about USB********************************
********************************************************************************
*******************************************************************************/

/*******************************************************************************
//Function Name  : Debug_GPIO_Init(void) 
//Description    : init debug usart used GPIO
//USE            : this file / Debug_Init()
//Input          : None. 
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Debug_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DEBUG_PORT_CLK,ENABLE);	
	
  GPIO_InitStructure.GPIO_Pin = DEBUG_TX_PIN ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(DEBUG_PORT , &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = DEBUG_RX_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DEBUG_PORT, &GPIO_InitStructure); 
}
/*******************************************************************************
//Function Name  : Debug_USART_Init(u32 baund) 
//Description    : init debug USART
//USE            : this file / Debug_Init()
//Input          : usart baund rate  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Debug_USART_Init(u32 baund)
{
	USART_InitTypeDef USART_InitStructure;              
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	if(DEBUG_USART_CLK==RCC_APB2Periph_USART1)
	{
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK ,ENABLE);
	}
	else 
	{
	RCC_APB1PeriphClockCmd(DEBUG_USART_CLK ,ENABLE);
	}
	
	USART_InitStructure.USART_BaudRate = baund;     
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ ;  	   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(DEBUG_USART(), USART_IT_RXNE, ENABLE);
	USART_ITConfig(DEBUG_USART(),USART_IT_IDLE, ENABLE);
	USART_Init(DEBUG_USART(), &USART_InitStructure);
	USART_Cmd(DEBUG_USART(), ENABLE);
}
/*******************************************************************************
//Function Name  : Debug_Init(u32 baund) 
//Description    : init debug message out
//USE            : main.c / main function
//Input          : usart baund rate  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Debug_Init(u32 baund)
{
Debug_GPIO_Init();
Debug_USART_Init(baund);
}
/*******************************************************************************
//Function Name  : Debug_Send_Data(u8* dat,u8 length)
//Description    : send buff from debug port
//USE            : other .c file which need send data in debug
//Input          : the data buff address,the data buff length 
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Debug_Send_Data(u8* dat,u8 length)
{
u8 i=0;         
	for(i=0;i<length;i++)
	{
	USART_SendData(DEBUG_USART(),dat[i]);
	while( USART_GetFlagStatus(DEBUG_USART(),USART_FLAG_TC)!= SET); 
	}
}
/*******************************************************************************
//Function Name  : fputc(int ch, FILE *f) 
//Description    : Remapping printf function
//USE            : extern call
//Input          :   
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
int fputc(int ch, FILE *f)
{
USART_SendData(DEBUG_USART(),(unsigned char) ch);
while( USART_GetFlagStatus(DEBUG_USART(),USART_FLAG_TC)!= SET);       
return (ch); 	
}
/*******************************************************************************
//Function Name  :                    USART1_IRQHandler(void)
//Description    :                    receive USART1 data,set receive end flag 
//USE            : extern call by sys IRQ
//Input          : None
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void DEBUG_USART(_IRQHandler)(void)
{
u32 CLE=0;
		if(USART_GetITStatus (DEBUG_USART(),USART_IT_RXNE )!=RESET ) 
		{			
		  USART_ClearITPendingBit(DEBUG_USART(),USART_IT_RXNE);
      Debug_Receive_Buff[Debug_Receive_Count]=USART_ReceiveData(DEBUG_USART());
			Debug_Receive_Count++;
		}
		if(USART_GetITStatus (DEBUG_USART(),USART_IT_IDLE)!=RESET ) 
		{			
		  USART_ClearITPendingBit(DEBUG_USART(),USART_IT_IDLE);
		  CLE=DEBUG_USART()->SR;
		  CLE=DEBUG_USART()->DR;
      Debug_Receive_Flag=1;
		}		
}























