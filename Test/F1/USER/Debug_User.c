/*******************************************************************************
  * @file    Debug_User.c
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
#include "Debug_User.h" 

extern u8 Debug_Receive_Buff[64];
extern u8 Debug_Receive_Count;
extern u8 Debug_Receive_Flag;
/*******************************************************************************
********************************************************************************
**************************All fuction  about USB********************************
********************************************************************************
*******************************************************************************/
extern u8 HW_Version[HW_LENGTH];
extern const u8 FW_Version[FM_LENGTH];
/*******************************************************************************
//Function Name  : Debug_Data_Serve(void)
//Description    : 
//USE            : 
//Input          : None. 
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Debug_Data_Serve(void)
{
 if(Debug_Receive_Flag)
	 {
		 if(Debug_Receive_Buff[0]=='1')
			 Debug_Send_Data (HW_Version,HW_LENGTH);
		 if(Debug_Receive_Buff[0]=='2')
			 Debug_Send_Data ((u8*)FW_Version,FM_LENGTH);	
		 if(Debug_Receive_Buff[0]=='3')
		 {
			 HW_Version[HW_LENGTH-1]='0';
			 HW_Version[HW_LENGTH-3]='1';
			 Debug_Send_Data (HW_Version,HW_LENGTH);
       Flash_Save_All();			 
		 }			 
	  //Debug_Send_Data (Debug_Receive_Buff,Debug_Receive_Count);
		Debug_Receive_Count=0;
		Debug_Receive_Flag=0; 
	 }
}




























