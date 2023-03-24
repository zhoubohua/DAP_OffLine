/********************************************************************************
  * @file    Version_User.h
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
#ifndef __Version_User_H
#define __Version_User_H
/*Includes ------------------------------------------------------------------*/
#include "All_Header.h"
#define HW_LENGTH              22 
#define HW_VERSION_ADDRESS     0    //use HW_LENGTH*2 byte to save HW_VERSION
#define FM_LENGTH              40
void Load_Version(void);
void Save_Version(void);
#endif



















