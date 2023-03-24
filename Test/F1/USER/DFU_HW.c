/**
  ******************************************************************************
  * @file    DFU_HW.c
  * @author  ZBH
  * @version V1.0.0
  * @date    2017.05.31
  * @brief   This file is about DFU update 
  ******************************************************************************
  * only EnterDFUMode() may be extern by other file,it will make the procedure
	* jump to UPDATE MODE
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "DFU_HW.h" 
/*******************************************************************************
//Function Name  : BKP_Configration(void) 
//Description    : Config backup register
//USE            : intern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void BKP_Configration(void)
{
   /* Enable PWR and BKP clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); 
  /* Enable write access to Backup domain */
  PWR_BackupAccessCmd(ENABLE);
  /* Clear Tamper pin Event(TE) pending flag */
  BKP_ClearFlag();
}
/*******************************************************************************
//Function Name  : SystemReset(void) 
//Description    : reset system by soft ware
//USE            : intern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void SystemReset(void)
{
__set_PRIMASK(1);
NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);	
NVIC_SystemReset(); 
}
/*******************************************************************************
//Function Name  : EnterDFUMode(void) 
//Description    : jump code into DFU mode
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void EnterDFUMode(void)
{  
  BKP_Configration();
  BKP_WriteBackupRegister(BKP_DR10, DFU_MODE_FLAG); 	
  SystemReset();
  return;
} 





