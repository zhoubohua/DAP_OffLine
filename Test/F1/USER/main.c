/********************************************************************************
  * @file    main.c
  * @author  ZBH
  * @version 
  * @date   
  * @brief  
  ******************************************************************************
  ******************************************************************************
  */
/*Includes ------------------------------------------------------------------*/
#include "All_Header.h" 
/*******************************************************************************
//Function Name  : main(void) 
//Description    : Entry function,init hard device,processing real-time tasks
//USE            : main
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	PAout (1)=1;
}
//#define DEBUG_PORT_CLK      RCC_APB2Periph_GPIOB
//#define DEBUG_TX_PIN        GPIO_Pin_10
//#define DEBUG_RX_PIN        GPIO_Pin_11
int main(void)
{ 
Set_NVIC_Adress();
Flash_Load_All();
Debug_Init(921600);
#ifdef HID_EN
Usb_Init();	
#endif
SysTick_Config(SystemCoreClock /500);//2ms 
	 LED_Init();
while(1)
			{ 
			Debug_Data_Serve();	
			Time_Cycle_Serve();
			} 
} 








 
