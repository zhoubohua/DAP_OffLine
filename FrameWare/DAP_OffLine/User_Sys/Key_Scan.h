/********************************************************************************
  * @file    Key_Scan.h
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions,bit binding
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __Key_Scan_H
#define __Key_Scan_H
/*Includes ------------------------------------------------------------------*/

#include "All_Header.h"

//#define KEY1_Pin GPIO_PIN_0
//#define KEY1_GPIO_Port GPIOC
//#define KEY2_Pin GPIO_PIN_1
//#define KEY2_GPIO_Port GPIOC
//#define KEY3_Pin GPIO_PIN_2
//#define KEY3_GPIO_Port GPIOC
//#define KEY4_Pin GPIO_PIN_3
//#define KEY4_GPIO_Port GPIOC

#define KEY1    !HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)//(!PCin(0))//HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
#define KEY2    !HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
#define KEY3    !HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define KEY4    !HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)
//#define KEY2 (!PCin(1))
//#define KEY3 (!PCin(2))
//#define KEY4 (!PCin(3))
#define KEY_FREE 0
#define KEY_CLICK 1
#define KEY_CLICK_TRUE 2
#define KEY_FREE1 3
#define KEY_CLICK1 10
#define KEY_CLICK1_TRUE 11

#define KEY_UP_SINGLE    0X11
#define KEY_DOWN_SINGLE  0X21
#define KEY_BACK_SINGLE  0X31
#define KEY_OK_SINGLE    0X41
void Key_Scan(void);
void Key_Test(void);
#endif
