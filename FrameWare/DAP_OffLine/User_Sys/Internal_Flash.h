#ifndef __Internal_Flash_h
#define __Internal_Flash_h 
#include "All_Header.h"
void Internal_Flash_Read(uint8_t* buff,uint32_t add,uint16_t length);
void Internal_Flash_Erase(uint32_t page_start_add,uint16_t page_num);
void Internal_Flash_Write(uint8_t* buff,uint32_t add,uint16_t length);
#endif
