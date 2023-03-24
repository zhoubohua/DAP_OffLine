/********************************************************************************
  * @file   File_User.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.25
  * @brief   
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __File_User_H
#define __File_User_H
/*Includes ----------------------------------------------------------------------------------------------------*/ 
#include "All_Header.h" 
/*function for other files-------------------------------------------------------------------------------------*/ 
uint8_t FatFS_Init(void);
uint8_t File_Creat_List(void);
void File_Test(void);
void File_Init(void);
void Write_Last_File(uint8_t* buff);
uint32_t Get_BIN_Size(uint8_t* file);
#endif
