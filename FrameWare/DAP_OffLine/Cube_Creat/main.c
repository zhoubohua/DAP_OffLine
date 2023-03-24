
#include "main.h"


#include "All_Header.h"
////////////////////////////////////////////////////////////////////////////////////////////////
//#define PROGRAMMER_LOG 1
//FATFS fs;
//FIL fnew;
//FRESULT Res;
//DIR work_dp;	
//FILINFO fil_message;

////UINT fnum;
//BYTE FATReadBuffer[1024]= {0};
//void FatFS_Init(void)
//{
//	Res = f_mount(&fs,"0:",1);
//		if ( Res == FR_OK )
//		{
//	#if(PROGRAMMER_LOG)		
//			printf ("MOUNT TF OK\r\n");
//	#endif		
//		}
//		else 
//		{
//	#if(PROGRAMMER_LOG)		
//			printf ("MOUNT TF ERR %d\r\n",Res);
//	#endif		
//		}
//}
//char BIN_Directory[64]="0:/";
//uint8_t BIN_File_Get(void)
//{
// 	fil_message.lfsize = _MAX_LFN * 2 + 1;
//	fil_message.lfname = &BIN_Directory[3];	
//	fil_message.lfname[3]=0x00;
//	
//Res= f_opendir(&work_dp,"0:/");
//		if ( Res == FR_OK )
//		{
//	#if(PROGRAMMER_LOG)		
//			printf ("OPEN DIR OK\r\n");
//	#endif		   
//		}
//		else 
//		{
//	   return 0;
//		}
//Res = f_findfirst(&work_dp, &fil_message, "", "F*.bin");
//		if (( Res == FR_OK )&&fil_message.lfname[3])
//		{
//		f_closedir(&work_dp);	
//	#if(PROGRAMMER_LOG)		
//			printf ("FIND BIN OK\r\n");
//			printf (BIN_Directory);
//			printf ("\r\n");
//	#endif		   
//		}
//		else 
//		{
//		 f_closedir(&work_dp);	
//	   return 0;
//		}		
//}
//uint32_t flash_address=0x8000000;
//uint16_t flash_write_size=1024;

//extern const program_target_t* flash_algo;
//extern const program_target_t flash_algo_STM32_F1_128;
//extern const program_target_t flash_algo_STM32_F4_1024;
//extern const program_target_t flash_algo_F0_16;

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
//flash_algo=&flash_algo_STM32_F4_1024;
////flash_algo=&flash_algo_STM32_F1_128;
////			flash_algo=&flash_algo_F0_16;
////set MCU into debug mode
//statu=swd_init_debug();
//      if(statu)
//			{
//				#if(PROGRAMMER_LOG)		
//				printf ("SEND INIT OK\r\n");
//				#endif			
//			}
//      else 
//			{
//			return 0;
//			}
//			
//			
////		if (target_opt_init() == ERROR_SUCCESS)
////		{
////		#if(PROGRAMMER_LOG)		
////		printf ("target_opt_init OK\r\n");
////		#endif
////		}
////		else 
////			{
////		#if(PROGRAMMER_LOG)		
////		printf ("target_opt_init err\r\n");
////		#endif				
////			return 0;
////			}
////			
//			
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
//			#if(PROGRAMMER_LOG)		
//			printf ("FLASH CHIP EREASE START\r\n");
//			#endif	
//if (target_flash_erase_chip() == ERROR_SUCCESS)
//		{
//			#if(PROGRAMMER_LOG)		
//			printf ("FLASH CHIP EREASE OK\r\n");
//			#endif			
//		}
//		else 
//		{
//			#if(PROGRAMMER_LOG)		
//			printf ("FLASH CHIP EREASE ERR\r\n");
//			#endif				
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

////////////////////////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void);
int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
	MX_I2C2_Init();
  USART1_Init();
  SPI_Flash_Init();
	MX_SDIO_SD_Init();
	MX_USB_DEVICE_Init();
	
	MX_TIM2_Init();
	
	MX_I2C2_Init();

OLED_init();
OLED_Show_String(0,0,"Init,waiting...");
FatFS_Init();
File_Init();
	
//FatFS_Init();
//	BIN_File_Get();
//	Burn_BIN();
//OLED_Test();
//	OLED_Test();
//OLED_Show_String(0,0,"000000000000000000000000",24);	
//OLED_Show_String(0,1,"111111111111111111111111",24);
//OLED_Show_String(0,2,"222222222222222222222222",24);
//OLED_Show_String(0,3,"333333333333333333333333",24);	

	while(1)
	{
  Logic_Serve();
	Time_Cycle_Serve();
//		Key_Test();;
//		delay_ms(100);
	}
}





void SystemClock_Config(void)
{
 RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
