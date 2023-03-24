#include "USART1_HW.h"

#define USART1_RX_BUFF_LENGTH 128
uint8_t USART1_RX_BUFF[USART1_RX_BUFF_LENGTH];

void USART1_Init(void)
{
HAL_UARTEx_ReceiveToIdle_DMA(&huart1,USART1_RX_BUFF,USART1_RX_BUFF_LENGTH);
}

void USART1_Send(uint8_t* buff,uint8_t length)
{
HAL_UART_Transmit(&huart1,buff,length,10000);

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
if(huart==&huart1)
	{
    USART1_Send(USART1_RX_BUFF,Size); 
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1,USART1_RX_BUFF,USART1_RX_BUFF_LENGTH);
	}
}

int fputc(int ch, FILE *f)
{
 HAL_UART_Transmit(&huart1 ,(uint8_t *)&ch,1,100);    
return (ch); 	
}









