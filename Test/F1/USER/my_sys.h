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
#include "stm32f10x.h"
#include "misc.h"
#include "stdio.h"
/*define of bit binding------------------------------------------------------------------*/
#define PA1 GPIOA->BSRR
#define PA0 GPIOA->BRR
#define PB1 GPIOB->BSRR
#define PB0 GPIOB->BRR
#define PC1 GPIOC->BSRR
#define PC0 GPIOC->BRR
#define PD1 GPIOD->BSRR
#define PD0 GPIOD->BRR
#define PE1 GPIOE->BSRR
#define PE0 GPIOE->BRR
#define GPIOA_ODR_A  (GPIOA_BASE+0x0C)
#define GPIOA_IDR_A  (GPIOA_BASE+0x08)
#define GPIOB_ODR_B  (GPIOB_BASE+0x0C)
#define GPIOB_IDR_B  (GPIOB_BASE+0x08)
#define GPIOC_ODR_C  (GPIOC_BASE+0x0C)
#define GPIOC_IDR_C  (GPIOC_BASE+0x08)
#define GPIOD_ODR_D  (GPIOD_BASE+0x0C)
#define GPIOD_IDR_D  (GPIOD_BASE+0x08)
#define GPIOE_ODR_E  (GPIOE_BASE+0x0C)
#define GPIOE_IDR_E  (GPIOE_BASE+0x08)

#define BitBand(Addr,BitNum)    *((volatile unsigned long *)((Addr&0xF0000000)+0x2000000+((Addr&0xfffff)<<5)+(BitNum<<2)))

#define PAout(n)   BitBand(GPIOA_ODR_A,n)
#define PAin(n)    BitBand(GPIOA_IDR_A,n)
#define PBout(n)   BitBand(GPIOB_ODR_B,n)
#define PBin(n)    BitBand(GPIOB_IDR_B,n)
#define PCout(n)   BitBand(GPIOC_ODR_C,n)
#define PCin(n)    BitBand(GPIOC_IDR_C,n)
#define PDout(n)   BitBand(GPIOD_ODR_D,n)
#define PDin(n)    BitBand(GPIOD_IDR_D,n)
#define PEout(n)   BitBand(GPIOE_ODR_E,n)
#define PEin(n)    BitBand(GPIOE_IDR_E,n)

/*function for other files------------------------------------------------------------------*/
void delay_1ms(void);
void delay_1us(void);
void delay_10us(void);
void delay_ms(u16 nms);
void Mem_Copy(u8* scr,u8* aim,u8 length);
signed char array_find(u8* table1,u8* table2,u8 l1,u8 l2);
void Set_NVIC_Adress(void);
void Maopao_Sort(u16 *dat, u8 leng);
#endif
