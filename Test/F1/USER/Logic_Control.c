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

//u8 HW_Verion[18]="HYG_EarPen_MB_VX.X";
//const u8 FW_Verion[38]="HYG_EarPen_F103-FW_V2.0.1_Build-210910";
/* global variable ------------------------------------------------------------------*/                                  
//below global variable use for creat cycle time interface
u16 SYS_Count=0;                                   //global variable,use for recorder  sys count ,plus one per 2ms  
u8  Count_2ms=0;                                   //global variable,use for creat cycle 2ms
u8  Count_10ms=0;                                  //global variable,use for creat cycle 10ms
u8  Count_20ms=0;                                  //global variable,use for creat cycle 20ms
u8  Count_100ms=0;                                 //global variable,use for creat cycle 100ms
u8  Count_500ms=0;                                 //global variable,use for creat cycle 500ms
u8  Time_Flag_2ms=0;                               //global variable,use as 2ms flag
u8  Time_Flag_10ms=0;                              //global variable,use as 10ms flag
u8  Time_Flag_20ms=0;                              //global variable,use as 20ms flag
u8  Time_Flag_100ms=0;                             //global variable,use as 100ms flag
u8  Time_Flag_500ms=0;                             //global variable,use as 500ms flag
/*******************************************************************************
********************************************************************************
**************************All fuction  about Logic_Control**********************
********************************************************************************
*******************************************************************************/

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
