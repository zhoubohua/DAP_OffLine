/********************************************************************************
  * @file    Cycle_User.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.26
  * @brief   This file is core logic control,it control RES,press,battray left num
	*          Calculation,and RES Calculation,creat cycle time frame
  ******************************************************************************
  *******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Cycle_User.h" 

/* global variable ------------------------------------------------------------------*/                                  
//below global variable use for creat cycle time interface
extern TIM_HandleTypeDef htim2;
static  u16 SYS_Count=0;                                   //global variable,use for recorder  sys count ,plus one per 2ms  
static u8  Count_2ms=0;                                   //global variable,use for creat cycle 2ms
static u8  Count_10ms=0;                                  //global variable,use for creat cycle 10ms
static u8  Count_20ms=0;                                  //global variable,use for creat cycle 20ms
static u8  Count_100ms=0;                                 //global variable,use for creat cycle 100ms
static u8  Count_500ms=0;                                 //global variable,use for creat cycle 500ms
static u8  Time_Flag_2ms=0;                               //global variable,use as 2ms flag
static u8  Time_Flag_10ms=0;                              //global variable,use as 10ms flag
static u8  Time_Flag_20ms=0;                              //global variable,use as 20ms flag
static u8  Time_Flag_100ms=0;                             //global variable,use as 100ms flag
static u8  Time_Flag_500ms=0;                             //global variable,use as 500ms flag
/*******************************************************************************
********************************************************************************
**************************All fuction  about Logic_Control**********************
********************************************************************************
*******************************************************************************/


/*******************************************************************************
//Function Name  : Time_Serve_2ms(void)
//Description    : the entrance of 2ms cycle need to do function  
//USE            : internal call 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Serve_2ms(void)
{

}
/*******************************************************************************
//Function Name  : Time_Serve_10ms(void)
//Description    : the entrance of 10ms cycle need to do function  
//USE            : internal call 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Serve_10ms(void)
{

}
/*******************************************************************************
//Function Name  : Time_Serve_20ms(void)
//Description    : the entrance of 20ms cycle need to do function  
//USE            : internal call 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Serve_20ms(void)
{

OLED_Roll();
Key_Scan();	
}
/*******************************************************************************
//Function Name  : Time_Serve_100ms(void)
//Description    : the entrance of 100ms cycle need to do function  
//USE            : internal call 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Serve_100ms(void)
{

}
/*******************************************************************************
//Function Name  : Time_Serve_500ms(void)
//Description    : the entrance of 500ms cycle need to do function  
//USE            : internal call 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Serve_500ms(void)
{
//OLED_Test();
}
/*******************************************************************************
//Function Name  : Time_Basic_Creat(void) 
//Description    : creat cycle time,set flag of 2ms,10ms,20ms,100ms,500ms
//USE            : external call by main while(1)
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Basic_Creat(void)
{
if(SYS_Count!=Count_2ms)
	{
		Count_2ms=SYS_Count;
    Time_Flag_2ms=1;	
    Count_10ms++;
    if((Count_10ms==5)&&(Time_Flag_10ms==0))	
		  {	
      Count_10ms=0;				
			Time_Flag_10ms=1;
       Count_20ms++;
        if((Count_20ms==2)&&(Time_Flag_20ms==0))
				{
				  Count_20ms=0;				
			    Time_Flag_20ms=1;
					Count_100ms++;
					if((Count_100ms==5)&&(Time_Flag_100ms==0))
					{
					Count_100ms=0;
					Time_Flag_100ms=1;
          Count_500ms++;	
             if((Count_500ms>=5)&&(Time_Flag_500ms==0))	
						 { 
						  Count_500ms=0;
							SYS_Count=0;
					    Time_Flag_500ms=1;
						 }							 
					}
				}					
			}			
		}		
}
/*******************************************************************************
//Function Name  : Time_Cycle_Serve(void)
//Description    : drive all cycle time entrance  
//USE            : external call by main while(1)
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Time_Cycle_Serve(void)
{
Time_Basic_Creat();	
if(Time_Flag_2ms)
	{
	Time_Serve_2ms();	
	Time_Flag_2ms=0;
	}
if(Time_Flag_10ms)
	{
	Time_Serve_10ms();	
	Time_Flag_10ms=0;
	}
if(Time_Flag_20ms)
	{
	Time_Serve_20ms();	
	Time_Flag_20ms=0;
	}
if(Time_Flag_100ms)
	{
	Time_Serve_100ms();	
	Time_Flag_100ms=0;
	}
if(Time_Flag_500ms)
	{
	Time_Serve_500ms();	
	Time_Flag_500ms=0;
	}
}
///*******************************************************************************
////Function Name  : SysTick_Handler(void) 
////Description    : plus SYS_Count 1 per 2ms 
////USE            : extern call by sys IRQ
////Input          : None.  
////Output         : None.
////Return         : None.
////EDITER         : ZBH
//*******************************************************************************/
//void SysTick_Handler(void)
//{
//	SYS_Count++;
//}
uint8_t  RT_Count=0;
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	
SYS_Count++;
	RT_Count++;
	if(RT_Count==10)
	{
	RT_Count=0;
	OLED_refresh_gram();	
	}
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}


