/********************************************************************************
  * @file    Burn_Serve.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions,bit binding
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __Burn_Serve_H
#define __Burn_Serve_H
/*Includes ------------------------------------------------------------------*/

#include "All_Header.h"
void Check_BIN_File(uint8_t* file);
void Erease_Flash(uint32_t size);
void Burn_Test(void);
#endif
