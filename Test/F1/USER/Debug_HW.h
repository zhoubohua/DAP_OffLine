/********************************************************************************
  * @file    Debug_HW.h
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
#ifndef __Debug_HW_H
#define __Debug_HW_H
/*Includes ------------------------------------------------------------------*/
#include "All_Header.h"
#define DEBUG_PORT          GPIOB
#define DEBUG_PORT_CLK      RCC_APB2Periph_GPIOB
#define DEBUG_TX_PIN        GPIO_Pin_10
#define DEBUG_RX_PIN        GPIO_Pin_11
#define DEBUG_USART(N)      USART3##   N
#define DEBUG_USART_CLK     RCC_APB1Periph_USART3
#define DEBUG_USART_IRQ     USART3_IRQn
void Debug_Init(u32 baund);
void Debug_Send_Data(u8* dat,u8 length);
#endif








































































