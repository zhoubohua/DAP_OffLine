/********************************************************************************
  * @file    my_sys.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions,bit binding
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __my_sys_H
#define __my_sys_H
/*Includes ------------------------------------------------------------------*/

#include "All_Header.h"

void delay_1ms(void);
void delay_1us(void);
void delay_10us(void);
void delay_ms(u16 nms);
void Mem_Copy(u8* scr,u8* aim,u8 length);
signed char array_find(u8* table1,u8* table2,u8 l1,u8 l2);
void Set_NVIC_Adress(void);
void Maopao_Sort(u16 *dat, u8 leng);
#endif
