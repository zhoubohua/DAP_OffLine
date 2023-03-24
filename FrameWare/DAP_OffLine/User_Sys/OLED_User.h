/********************************************************************************
  * @file   OLED_User.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.25
  * @brief   
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __OLED_User_H
#define __OLED_User_H
/*Includes ----------------------------------------------------------------------------------------------------*/ 
#include "All_Header.h" 
/*function for other files-------------------------------------------------------------------------------------*/ 
#define OLED_I2C_ADDRESS 0x78
#define MAX_COLUMN      128
#define MAX_ROW         64

#define X_WIDTH         MAX_COLUMN
#define Y_WIDTH         MAX_ROW

#define OLED_CMD        0x00
#define OLED_DATA       0x01

#define CHAR_SIZE_WIDTH 6
#define CHAR_SIZE_HIGHT 12

typedef enum
{
    PEN_CLEAR = 0x00,
    PEN_WRITE = 0x01,
    PEN_INVERSION= 0x02,
}pen_typedef;

void OLED_Test(void);
void OLED_init(void);
void OLED_refresh_gram(void);
void OLED_Roll(void);
//void OLED_Roll_Set(uint8_t line,uint8_t statu);
void OLED_Roll_Set(uint8_t line,uint8_t statu,uint8_t length);
void OLED_Invert_Set(uint8_t line,uint8_t statu);
uint8_t  OLED_Show_String(uint8_t x,uint8_t y,char* data);
void  OLED_Show_Buff(uint8_t x,uint8_t y,char* data,uint8_t length);
void OLED_operate_gram(uint8_t statu);
#endif
