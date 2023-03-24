/********************************************************************************
  * @file    Flash_HW.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   about flash extern function,define of flash
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __Flash_HW_H
#define __Flash_HW_H
/*Includes ----------------------------------------------------------------------------------------------------*/ 
#include "All_Header.h" 
/*define of flash size-----------------------------------------------------------------------------------------*/ 
#define BaseAdress 0x08000000
#define CodeSize   0xe800
#define FLASH_SIZE 64//
#if FLASH_SIZE<256
  #define SECTOR_SIZE 1024//
#else 
  #define SECTOR_SIZE 2048//
#endif

/*function for other files-------------------------------------------------------------------------------------*/ 
void FlashErase(u32 adress);
u16 FlashWrite_16 (u32 adress,u16 data);
u16 FlashRead_16 (u32 adress);
void Flash_Load_All(void);
void Flash_Save_All(void);
#endif


