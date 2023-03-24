/********************************************************************************
  * @file    Flash_HW.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.25 
  * @brief   This file is about flash write an read,all calibration write and read
  ******************************************************************************
  *******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Flash_HW.h"
/*******************************************************************************
********************************************************************************
**************************All fuction  about STM32Flash*************************
********************************************************************************
*******************************************************************************/

/*******************************************************************************
//Function Name  : FlashWrite_16 (u32 adress,u16 data)
//Description    : write a data to point flash
//USE            : internal call
//Input          : save address,save data  
//Output         : save data
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
u16 FlashWrite_16(u32 adress,u16 data)
{
adress=BaseAdress +CodeSize +adress;
FLASH_Unlock();//解锁
FLASH_ProgramHalfWord(adress,data);
FLASH_Lock();//上锁	
return *(vu16*)adress;
}
/*******************************************************************************
//Function Name  : FlashRead_16 (u32 adress)
//Description    : read a data from point flash
//USE            : internal call
//Input          : read address
//Output         : read data
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
u16 FlashRead_16 (u32 adress)
{
adress=BaseAdress +CodeSize +adress;	
return *(vu16*)adress;
}
/*******************************************************************************
//Function Name  : FlashErase(u32 adress)
//Description    : erase flash (will arase whole page)
//USE            : external call
//Input          : to erase address
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void FlashErase(u32 adress)
{
u32 page_adress;
adress=BaseAdress +CodeSize +adress;	
page_adress =adress/SECTOR_SIZE ;	
page_adress =page_adress*SECTOR_SIZE ;		
FLASH_Unlock();//解锁
FLASH_ErasePage(adress);
FLASH_Lock();//上锁	
}
/*******************************************************************************
//Function Name  : Flash_Load_All(void)
//Description    : read all calibration data ,save to RES_Reference,Press_Reference,BLE_MAC_S
//USE            : external call
//Input          : None.
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Flash_Load_All(void)
{
Load_Version();	
}
/*******************************************************************************
//Function Name  : Flash_Save_All(void)
//Description    : save all calibration data,from RES_Reference,Press_Reference,BLE_MAC_S
//USE            : external call
//Input          : None.
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Flash_Save_All(void)
{
	FlashErase(2);
  Save_Version();	
}


