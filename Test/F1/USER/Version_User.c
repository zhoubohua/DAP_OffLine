/*******************************************************************************
  * @file    Version_User.c
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
#include "Version_User.h" 
u8 HW_Version[HW_LENGTH]="HYG_FramWare_Demo_VX.X";
const u8 FW_Version[FM_LENGTH] __attribute__((at(0X8006400)))="HYG_FramWare_F103-FW_V1.0.0_Build-210910";
/*******************************************************************************
//Function Name  : Load_Version(void)
//Description    : 
//USE            : 
//Input          : None. 
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Load_Version(void)
{
	u8 i=0;
	for(i=0;i<HW_LENGTH;i++)
	{
		if(FlashRead_16(HW_VERSION_ADDRESS+i*2)!=0xffff)
		{
		HW_Version[i]=FlashRead_16(HW_VERSION_ADDRESS+i*2);
		}
	}
}

/*******************************************************************************
//Function Name  : Load_Version(void)
//Description    : 
//USE            : 
//Input          : None. 
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Save_Version(void)
{
	u8 i=0;
	for(i=0;i<HW_LENGTH;i++)
	{
		FlashWrite_16(i*2+HW_VERSION_ADDRESS,HW_Version[i]);
	}
}












