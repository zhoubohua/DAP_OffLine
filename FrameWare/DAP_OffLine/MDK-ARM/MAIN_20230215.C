
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#include "All_Header.h"

void SystemClock_Config(void);
FATFS fs;
FIL fnew;
FRESULT res_sd;
FRESULT Res;
UINT fnum;
BYTE ReadBuffer[1024]= {0};
BYTE WriteBuffer[] ="STM32 fat write test \r\n";




//#define u8 uint8_t;
u8 readflag = 1;
u32 addr = 0;
uint16_t bytesread;
char rData[1024] = "";
uint8_t FLASH_SWD(uint8_t *File){
	Res = f_open(&fnew, (const TCHAR*)File,FA_READ );
	if ( Res == FR_OK )
	{
		readflag = 1;
	  addr = 0;
		if(swd_init_debug())
		{
//printf("swd_init_debug ok \r\n");
//				if (target_opt_init() == ERROR_SUCCESS)
//				{
////printf("target_opt_init ok \r\n");
//					if (target_opt_erase_chip() != ERROR_SUCCESS)
//						{
////printf("target_opt_erase_chip err \r\n");
//					  return 0;
//					}
//				}else return 0;
//				target_opt_uninit();
//printf("target_opt_uninit ok \r\n");
			  if (swd_init_debug())
			{
//printf("swd_init_debug ok \r\n");
				if (target_flash_init(0x08000000) == ERROR_SUCCESS)
				{
//printf("target_flash_init ok \r\n");
					if (target_flash_erase_chip() == ERROR_SUCCESS)
					{
//printf("target_flash_erase_chip \r\n");
						while(readflag){
			         f_read(&fnew, rData,1024, (void *)&bytesread);
			         if(bytesread<1024){
				         readflag = 0;
			         }
								if (target_flash_program_page(0x08000000 + addr, (u8*)&rData[0], 1024) == ERROR_SUCCESS)
							{
								u32 progess = (((double)addr/f_size(&fnew))*100);
printf("target_flash_program_page %d \r\n",progess);
							}else 
                  {
//printf("target_flash_program_page err \r\n");
	                 return 0;
                   }
							addr += 1024;
		        }
						if (swd_init_debug())
		        {
							printf("Dlowload ok \r\n");
			        swd_set_target_reset(0);//¸´Î»ÔËÐÐ
							return 1;
		        }
						else return 0;
					}else return 0;
				}
				target_flash_uninit();
			}else return 0;
		}else return 0;
	}else return 0;
	return 0;
}
















int main(void)
{
//D:\SoftWareInstall\KEIL5_3\Keil\STM32F1xx_DFP\1.1.0\Device\Include\stm32f10x.h(306): error:  #101: "CAN1_RX1_IRQn" has already been declared in the current scope
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();

  USART1_Init();
  SPI_Flash_Init();
	MX_SDIO_SD_Init();
	MX_USB_DEVICE_Init();
	
res_sd = f_mount(&fs,"0:",1);
//	printf ("MOUNT RES=%d \r\n",res_sd);
	if ( res_sd == FR_OK )
	{
		printf ("MOUNT TF OK\r\n");
	//res_sd=f_open(&fnew,"0:FatFs test.txt",FA_CREATE_ALWAYS|FA_WRITE);
	}
DIR work_dp;	
res_sd = f_opendir(&work_dp,"0:/");
	if ( res_sd == FR_OK )
	{
		printf ("open dir OK\r\n");
	}	
FILINFO fil;

while(1)
{
	char buf[256];
  char* fn;
#if _USE_LFN
 	fil.lfsize = _MAX_LFN * 2 + 1;
	fil.lfname = buf;
#endif		
	
	
res_sd= f_readdir(&work_dp,&fil);

	
//	if ( res_sd == FR_OK )
//	{
//		printf ("read file name OK\r\n");
//	}	

	if(res_sd != FR_OK || fil.fname[0] == 0)
	{
	printf ("no file\r\n");
	break;
	}
	
	if(fil.fname[0] =='.')
	{
	printf ("doit file\r\n");	
	 continue;
	}
	
	 if(fil.fattrib & AM_DIR)
	 {
	 printf("(0x%02d)DIR\r\n",fil.fattrib);
	 }
	 else 
	 {	 
	 printf("(0x%02d)FIL\r\n",fil.fattrib);
		
	 fn=fil.lfname?fil.lfname:fil.fname;
	printf("NAME:%s\r\n",fn);
	if((fn[0]=='T')&& (fn[1]=='E')&&(fn[2]=='S')&&(fn[3]=='T'))
	{
	   printf("SWO READY\r\n");
		          while(!FLASH_SWD((u8*)fn))
							{
								Delayms(100);
								printf("SWO RUN\r\n");
							}
		
	}
		 
	 }

	 
	
	
}
res_sd= f_readdir(&work_dp,&fil);
	if ( res_sd == FR_OK )
	{
		printf ("read file name OK\r\n");
	}		




//YP_LAB9xx_CH_V4.5.0.bin	
//res_sd= f_open(&fnew,"0:/YP_LAB9xx_CH_V4.5.0.bin",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);	
//if ( res_sd == FR_OK ) 	
//	{
//	 printf ("open YP_LAB9xx_CH_V4.5.0.bin OK\r\n"); 
//	}
////	f_lseek(&fnew,0);
////	f_gets((char*)ReadBuffer,1024,&fnew);	
//	res_sd = f_read(&fnew, ReadBuffer,sizeof(ReadBuffer), &fnum);
//	if ( res_sd == FR_OK )
//	{
//	printf("read data ok ,data length :%d\n",fnum);
//    uint16_t l=0;
//		for(l=0;l<fnum;l++)
//		{
//		 if(l%16==0)
//		 {
//		 printf ("\r\n");
//		 }			
//			printf("0x%02x ",ReadBuffer[l]);

//		}
//	}
//	else 
//	{
//	printf("read data err %d\r\n",res_sd);
//	}

	
	
//		          while(!FLASH_SWD((u8*)FileInfo.lfname))
//							{
//		            u8 WaitTips[] = "...";
//			          OLED_ShowString(45,1,(u8*)"          ",1,0);
//			          OLED_ShowString(45,2,(u8*)"WAIT",1,1);
//			          for(i=0;i<3;i++){
//                  OLED_ShowChar(69+i*6,2,WaitTips[i],1);
//	                delay_ms(200);
//	              }
//			          OLED_ShowString(45,2,(u8*)"       ",1,1);
//		          }	
	
	
	
	
	
//if ( res_sd == FR_OK ) 
//{
//	printf("create file ok,ready to write data\r\n");
//	res_sd=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
//	if (res_sd==FR_OK)
//	{
//	printf("write data ok ,data length :%d\n",fnum);
//	}
//	else 
//	{
//	printf("write data err,err :%d\n",fnum);
//	}
//	f_close(&fnew);
//}
//else 
//{
//	printf("create file err,err:%d\r\n",res_sd);
//}
  while (1)
  {	
		HAL_Delay(100);//huart1
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
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
