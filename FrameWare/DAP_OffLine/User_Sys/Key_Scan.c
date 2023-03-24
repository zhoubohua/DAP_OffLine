/********************************************************************************
  * @file    Key_Scan.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions
  ******************************************************************************
  ******************************************************************************
  */
#include "Key_Scan.h"
u8 KEY1_STATU=0;          //global variable,use for recorder  KEY1 statu
u8 KEY2_STATU=0;          //global variable,use for recorder  KEY2 statu
u8 KEY3_STATU=0;          //global variable,use for recorder  KEY3 statu
u8 KEY4_STATU=0;          //global variable,use for recorder  KEY4 statu  
u8 KEY_DATA=0; 
/*******************************************************************************
//Function Name  : delay_1ms(void) 
//Description    : delay 1 ms
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
u16 KEY_TIM_STATU=0;
void Key_Scan(void)
{
switch(KEY1_STATU)
				{
				case KEY_FREE :
						 {if(KEY1)KEY1_STATU=KEY_CLICK;}
						 break;
				case KEY_CLICK :
						{
						if(KEY1)KEY1_STATU=KEY_CLICK_TRUE;
							else  KEY1_STATU=KEY_FREE;
						}
						 break;
				case KEY_CLICK_TRUE : 
						{
							if(KEY1)
							{
								KEY_TIM_STATU++;
							}		
								else  
								{
									KEY1_STATU=KEY_FREE;
										if(KEY_TIM_STATU>80)
										{
										KEY_DATA=0x13;
										}
											else 
											{
												KEY_DATA=0x11;	
											}
									KEY_TIM_STATU=0;
								}
						}
						 break;
				case KEY_CLICK1:
						{
						if(KEY1)KEY1_STATU=KEY_CLICK1_TRUE;
							else  {
										 KEY1_STATU=KEY_FREE;
										 KEY_DATA=0x11;
										}
						}
						 break;	
				case KEY_CLICK1_TRUE:
						{
						if(KEY1);
							else  {
										 KEY1_STATU=KEY_FREE;
										 KEY_DATA=0x12;
										}
						}
						 break;					
				default :{KEY1_STATU++;}		
				}
switch(KEY2_STATU)
					{
					case KEY_FREE :
							 {if(KEY2)KEY2_STATU=KEY_CLICK;}
							 break;
					case KEY_CLICK :
							{
							if(KEY2)KEY2_STATU=KEY_CLICK_TRUE;
								else  KEY2_STATU=KEY_FREE;
							}
							 break;
					case KEY_CLICK_TRUE :
							{
								if(KEY2)
									{
										KEY_TIM_STATU++;
									}		
										else  
										{
											KEY2_STATU=KEY_FREE;
												if(KEY_TIM_STATU>80)
												{
												KEY_DATA=0x23;
												}
													else 
													{
														KEY_DATA=0x21;	
													}
											KEY_TIM_STATU=0;
										}
							}
							 break;
					case KEY_CLICK1:
							{
							if(KEY2)KEY2_STATU=KEY_CLICK1_TRUE;
								else  {
											 KEY2_STATU=KEY_FREE;
											 KEY_DATA=0x21;
											}
							}
							 break;	
					case KEY_CLICK1_TRUE:
							{
							if(KEY2);
								else  {
											 KEY2_STATU=KEY_FREE;
											 KEY_DATA=0x22;
									      
											}
							}
							 break;					
					default :{KEY2_STATU++;}		
					}
switch(KEY4_STATU)
					{
					case KEY_FREE :
							 {if(KEY4)KEY4_STATU=KEY_CLICK;}
							 break;
					case KEY_CLICK :
							{
							if(KEY4)KEY4_STATU=KEY_CLICK_TRUE;
								else  KEY4_STATU=KEY_FREE;
							}
							 break;
					case KEY_CLICK_TRUE :
							{
							if(KEY4)
								{
									KEY_TIM_STATU++;
								}		
									else  
									{
										KEY4_STATU=KEY_FREE;
											if(KEY_TIM_STATU>80)
											{
											KEY_DATA=0x43;
											}
												else 
												{
													KEY_DATA=0x41;	
												}
										KEY_TIM_STATU=0;
									}
							}
							 break;
					case KEY_CLICK1:
							{
							if(KEY4)KEY4_STATU=KEY_CLICK1_TRUE;
								else  {
											 KEY4_STATU=KEY_FREE;
											 KEY_DATA=0x41;
											}
							}
							 break;	
					case KEY_CLICK1_TRUE:
							{
							if(KEY4);
								else  {
											 KEY4_STATU=KEY_FREE;
											 KEY_DATA=0x42;
								
											}
							}
							 break;					
					default :{KEY4_STATU++;}		
					}
switch(KEY3_STATU)
					{
					case KEY_FREE :
							 {if(KEY3)KEY3_STATU=KEY_CLICK;}
							 break;
					case KEY_CLICK :
							{
							if(KEY3)KEY3_STATU=KEY_CLICK_TRUE;
								else  KEY3_STATU=KEY_FREE;
							}
							 break;
					case KEY_CLICK_TRUE :
							{
								if(KEY3)
								{
									KEY_TIM_STATU++;
                      if(KEY_TIM_STATU==80)
											{
											KEY_DATA=0x33;
											}
								}		
									else  
									{
										KEY3_STATU=KEY_FREE;
											if(KEY_TIM_STATU>80)
											{
										//	KEY_DATA=0x33;
											}
												else 
												{
													KEY_DATA=0x31;	
												}
										KEY_TIM_STATU=0;
									}
							}
							 break;
					case KEY_CLICK1:
							{
							if(KEY3)KEY3_STATU=KEY_CLICK1_TRUE;
								else  {
											 KEY3_STATU=KEY_FREE;
											 KEY_DATA=0x31;
											}
							}
							 break;	
					case KEY_CLICK1_TRUE:
							{
							if(KEY3);
								else  {
											 KEY3_STATU=KEY_FREE;
											 KEY_DATA=0x32;
											}
							}
							 break;					
					default :{KEY3_STATU++;}		
					}																	
}


void Key_Test(void)
{
if(KEY_DATA !=0x00)
{
printf ("key=0x%x\r\n",KEY_DATA);
KEY_DATA=0;
}
}

