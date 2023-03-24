/********************************************************************************
  * @file    Burn_Serve.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions
  ******************************************************************************
  ******************************************************************************
  */
#include "Burn_Serve.h"
#define  STM32_F0_16 0X00

#define  STM32_F1_128 0X10
#define  STM32_F1_512 0X11

#define  STM32_F4_1024 0X20
uint32_t  STM32F4_Flash_Table[13]=
{	
0x00000000,	
0x00004000,	
0x00008000,	
0x0000C000,	
0x00010000,	
0x00020000,	
0x00040000,	
0x00060000,	
0x00080000,	
0x000A0000,	
0x000C0000,	
0x000E0000,
0x00100000	
}	;
	
	
	
	
	
	
/*******************************************************************************
//Function Name  : delay_1ms(void) 
//Description    : delay 1 ms
//USE            : extern call
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
uint32_t Bin_Size=0;
uint16_t Bin_Flash_Type=0;
uint32_t flash_address=0x8000000; 
extern const program_target_t* flash_algo;
extern const program_target_t flash_algo_F0_16;
extern const program_target_t flash_algo_STM32_F1_128;
extern const program_target_t flash_algo_STM32_F4_1024;

extern uint8_t Last_File[64];


extern uint8_t Logic_Statu;
void Check_BIN_File(uint8_t* file)
{
	uint8_t dir_buff[64]="0:/";
	sprintf ((char *)dir_buff,"0:/%s",&file[4]);
	Bin_Size=0;
	Bin_Size=Get_BIN_Size(dir_buff);
	if(array_find((uint8_t *)"F1_512",file,6,32)!=-1)
	{
	Bin_Flash_Type=STM32_F1_512;
	flash_algo=&flash_algo_STM32_F1_128;
	}else
	if(array_find((uint8_t *)"F1_128",file,6,32)!=-1)
	{
	Bin_Flash_Type=STM32_F1_128;
	flash_algo=&flash_algo_STM32_F1_128;
	}else
	if(array_find((uint8_t *)"F0_16",file,5,32)!=-1)
	{
	Bin_Flash_Type=STM32_F0_16;
	flash_algo=&flash_algo_F0_16;	
	}else
	if(array_find((uint8_t *)"F4_1024",file,7,32)!=-1)
	{
	Bin_Flash_Type=STM32_F4_1024;
	flash_algo=&flash_algo_STM32_F4_1024;
	}
}
#define PROGRAMMER_LOG 1

void Show_Erase_statu(uint32_t data)
{
uint8_t  buff[32];
sprintf ((char*)buff,"Erease  %.2fkb",data/1024.0);	
OLED_Show_String(0,1,(char *)buff);	
}

void STM32F4_Erease_Flash(uint32_t size)
{
uint8_t statu=0;
uint8_t i=0;
	statu=1;
	i=0;
	while(statu)
	{
	if (target_flash_erase_sector(flash_address|STM32F4_Flash_Table[i])== ERROR_SUCCESS)
			{
				if(STM32F4_Flash_Table[i+1]>=size)
				statu=0;	
				#if(PROGRAMMER_LOG)		
				printf ("FLASH EREASE 0x%x to 0x%x OK\r\n",flash_address|STM32F4_Flash_Table[i],flash_address|STM32F4_Flash_Table[i+1]);
				#endif	
				i++;
        Show_Erase_statu(STM32F4_Flash_Table[i]);				
			}
			else 
			{
				#if(PROGRAMMER_LOG)		
				printf ("FLASH CHIP EREASE ERR\r\n");
				#endif				
			}
	}	
}



void STM32F1_Erease_Flash(uint32_t size)
{
uint8_t statu=0;
uint16_t i=0;
statu=1;
i=0;
	while(statu)
	{
	if (target_flash_erase_sector(flash_address|(i*1024))== ERROR_SUCCESS)
			{
				if((i+1)*1024>=size)
				statu=0;	
				#if(PROGRAMMER_LOG)		
				printf ("FLASH EREASE 0x%x to 0x%x OK\r\n",flash_address|(i*1024),flash_address|((i+1)*1024));
				#endif	
				i++;	
				Show_Erase_statu(i*1024);
			}
			else 
			{
				#if(PROGRAMMER_LOG)		
				printf ("FLASH CHIP EREASE ERR\r\n");
				#endif				
			}
	}	
}
void Erease_Flash_Sector(void)
{
uint8_t statu=0;
	uint8_t i=0;
statu=swd_init_debug();
      if(statu)
			{
				#if(PROGRAMMER_LOG)		
				printf ("SEND INIT OK\r\n");
				#endif			
			}
      else 
			{
				#if(PROGRAMMER_LOG)		
				printf ("SEND INIT ERR\r\n");
				#endif
			}	
////////////////////////////////////////////			
if (target_flash_init(flash_address) == ERROR_SUCCESS)
		{
			#if(PROGRAMMER_LOG)		
			printf ("FLASH INIT OK\r\n");
			#endif			
		}
		else 
		{
				#if(PROGRAMMER_LOG)		
				printf ("FLASH INIT ERR\r\n");
				#endif
			  OLED_Show_String(0,1,"Erease err");
			  OLED_Show_String(0,2,"Check file name");
			  delay_ms(1000);
			  return;
			
		} 
////////////////////////////////////////////////
switch (Bin_Flash_Type)
{
	case STM32_F4_1024:{STM32F4_Erease_Flash(Bin_Size);};break;
	case STM32_F0_16:{STM32F1_Erease_Flash(Bin_Size);};break;;
	case STM32_F1_128:{STM32F1_Erease_Flash(Bin_Size);};break;
	case STM32_F1_512:{STM32F1_Erease_Flash(Bin_Size);};break;
	default:{};break;		
}		
}







////////////////////////

void Show_Burn_statu(uint32_t data)
{
uint8_t  buff[32];
sprintf ((char*)buff,"Burn  %.2fkb",data/1024.0);	
OLED_Show_String(0,2,(char *)buff);	
}
void Show_Burn_End(void)
{
OLED_Show_String(0,3,(char *)"Burn OK,return");	
}

extern FIL fBIN;
extern  FRESULT res;
uint16_t read_count=0;
void STM32_Write_Flash(uint8_t* file)
{
uint8_t statu=0;
uint16_t i=0;
uint8_t dir_buff[64]="0:/";


uint32_t current_write_address=0;
uint32_t progess=0;
uint8_t rData[1024] = "";		
	
	
statu=1;
i=0;
sprintf ((char *)dir_buff,"0:/%s",&file[4]);	
				#if(PROGRAMMER_LOG)		
				printf ("OPEN BIN DIR-%s\r\n",dir_buff);
				#endif	
res=f_open(&fBIN, (const TCHAR*)dir_buff,FA_OPEN_ALWAYS|FA_READ);	
	if ( res == FR_OK )
			{
				#if(PROGRAMMER_LOG)		
				printf ("OPEN BIN FILE OK\r\n");
				#endif
			}
		else 
			{
				#if(PROGRAMMER_LOG)		
				printf ("OPEN BIN FILE ERR%d\r\n",res);
				#endif			
			}
////////////////////////////////////////////////////////////
statu=swd_init_debug();
      if(statu)
			{
				#if(PROGRAMMER_LOG)		
				printf ("SEND INIT OK\r\n");
				#endif			
			}
      else 
			{
				#if(PROGRAMMER_LOG)		
				printf ("SEND INIT ERR\r\n");
				#endif
			}	
////////////////////////////////////////////			
if (target_flash_init(flash_address) == ERROR_SUCCESS)
		{
			#if(PROGRAMMER_LOG)		
			printf ("FLASH INIT OK\r\n");
			#endif			
		}
		else 
		{
				#if(PROGRAMMER_LOG)		
				printf ("FLASH INIT ERR\r\n");
				#endif
				OLED_Show_String(0,1,"Burn err");
			  OLED_Show_String(0,2,"Check file name");
			  delay_ms(1000);
			  return;
		} 
///////////////////////////////////////////////////////////
//write bin file to MCU flash	
statu=1;
		while(statu)
		{
			//res=f_open(&fBIN, (const TCHAR*)file,FA_OPEN_ALWAYS|FA_READ);
		//read a pack data(flash_write_size)	,and check the bin read end
		res=f_read(&fBIN, rData,1024, (void *)&read_count);
				if ( res == FR_OK )
						{
					#if(PROGRAMMER_LOG)		
							printf ("READ FILE OK%d\r\n",read_count);
					#endif	   
						}
						else 
						{
					#if(PROGRAMMER_LOG)		
							printf ("READ FILE ERR%d\r\n",res);
					#endif
						}			
		if(read_count<1024)
			{
			 statu=0;
			}
		//write apack bin data to MCU flash
		if (target_flash_program_page(flash_address +current_write_address,&rData[0], 1024) == ERROR_SUCCESS)
			{
			progess = ((current_write_address+read_count)*100)/f_size(&fBIN);
			Show_Burn_statu(current_write_address+read_count);	
					#if(PROGRAMMER_LOG)		
					printf ("BURN %3d/100\r\n",progess);
					#endif				
			}
			else 
			{
					#if(PROGRAMMER_LOG)		
					printf ("BURN %3d/100\r\n",progess);
					#endif	
			}
			current_write_address +=1024;//set next data write sddress		
		}
//set MCU into debug mode
		if (swd_init_debug())
				{
					Show_Burn_End();
					#if(PROGRAMMER_LOG)		
					printf ("SWD INIT OK,WILL RESET MCU\r\n");
					#endif
					delay_ms(2000);
					swd_set_target_reset(0);//reset and run
				}
				else 
				{
				}				
f_close(&fBIN);	
}
//uint8_t Burn_BIN(void)
//{
//uint8_t statu=0;
//uint16_t read_count=0;
//uint32_t current_write_address=0;
//uint32_t progess=0;
//uint8_t rData[1024] = "";	
////open bin file
//Res = f_open(&fnew, (const TCHAR*)BIN_Directory,FA_READ );
//	if ( Res == FR_OK )
//			{
//				#if(PROGRAMMER_LOG)		
//				printf ("OPEN BIN FILE OK\r\n");
//				#endif
//			}
//		else 
//			{
//			return 0;
//			}
//			
//flash_algo=&flash_algo_STM32_F1_128;
////			flash_algo=&flash_algo_STM32_F4_1024;
////set MCU into debug mode
//statu=swd_init_debug();
//      if(statu)
//			{
//				#if(PROGRAMMER_LOG)		
//				printf ("SED INIT OK\r\n");
//				#endif			
//			}
//      else 
//			{
//			return 0;
//			}
////init MCU flash
//if (target_flash_init(flash_address) == ERROR_SUCCESS)
//		{
//			#if(PROGRAMMER_LOG)		
//			printf ("FLASH INIT OK\r\n");
//			#endif			
//		}
//		else 
//		{
//		return 0;
//		} 
////erase MCU flash
//if (target_flash_erase_chip() == ERROR_SUCCESS)
//		{
//			#if(PROGRAMMER_LOG)		
//			printf ("FLASH CHIP EREASE OK\r\n");
//			#endif			
//		}
//		else 
//		{
//		return 0;
//		} 
////write bin file to MCU flash	
//statu=1;
//		while(statu)
//		{
//		//read a pack data(flash_write_size)	,and check the bin read end
//		f_read(&fnew, rData,flash_write_size, (void *)&read_count);
//		if(read_count<flash_write_size)
//			{
//			 statu=0;
//			}
//		//write apack bin data to MCU flash
//		if (target_flash_program_page(flash_address +current_write_address,&rData[0], flash_write_size) == ERROR_SUCCESS)
//			{
//			progess = (current_write_address*100)/f_size(&fnew);
//					#if(PROGRAMMER_LOG)		
//					printf ("BURN %3d/100\r\n",progess);
//					#endif				
//			}
//			else 
//			{
//			 return 0;
//			}
//			current_write_address +=flash_write_size;//set next data write sddress		
//		}
////set MCU into debug mode
//		if (swd_init_debug())
//				{
//					#if(PROGRAMMER_LOG)		
//					printf ("SWD INIT OK,WILL RESET MCU\r\n");
//					#endif
//					swd_set_target_reset(0);//reset and run
//					return 1;
//				}
//				else 
//				{
//				return 0;
//				}						
//}


//void Check_BIN_File(uint8_t* file)
//{
//	uint8_t dir_buff[64]="0:/";
//	sprintf ((char *)dir_buff,"0:/%s",&file[4]);
//	Bin_Size=0;
//	Bin_Size=Get_BIN_Size(dir_buff);

void Burn_Test(void)
{
Erease_Flash_Sector();
STM32_Write_Flash(Last_File);
}
















