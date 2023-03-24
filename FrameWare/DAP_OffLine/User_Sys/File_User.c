/********************************************************************************
  * @file    File_User.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions
  ******************************************************************************
  ******************************************************************************
  */
#include "File_User.h"
#define FILE_LOG 1


FATFS fs;
FIL fBIN;
FIL fLast;
//FRESULT Res;
DIR sys_dir;	
DIR root_dir;
FILINFO BIN_message;
uint8_t Last_File[64]="NO FILE CHOOSED";
FRESULT res;
////UINT fnum;
//BYTE FATReadBuffer[1024]= {0};
uint8_t FatFS_Init(void)
{

	res = f_mount(&fs,"0:",1);
		if ( res == FR_OK )
		{
	#if(FILE_LOG)		
			printf ("MOUNT TF OK\r\n");
	#endif		
		}
		else 
		{
	#if(FILE_LOG)		
			printf ("MOUNT TF ERR %d\r\n",res);
	#endif		
		}
return res;
}

uint8_t File_Creat_List(void)
{

	uint8_t statu=0;

res=f_opendir(&sys_dir,(const TCHAR*)"0:/sys");	
if ( res == FR_OK )
		{
	#if(FILE_LOG)		
			printf ("SYS DIR OK\r\n");
	#endif		
		}
		else 
		{
	#if(FILE_LOG)		
			printf ("SYS DIR ERR %d\r\n",res);
						res=f_mkdir("0:/sys");
						if ( res == FR_OK )
								{
							#if(FILE_LOG)		
									printf ("CREAT SYS DIR OK\r\n");
							#endif		
								}
								else 
								{
							#if(FILE_LOG)		
									printf ("CREAT SYS DIR ERR %d\r\n",res);
							#endif		
								}	
	#endif		
		}		
//////////////////////////////////////////////////////////////////////////////////////////////////
//  res=f_open(&fList, (const TCHAR*)"0:/sys/List.txt",FA_CREATE_ALWAYS|FA_WRITE);	
//	f_sync(&fList);
//		if ( res == FR_OK )
//		{
//	#if(FILE_LOG)		
//			printf ("CREAT LIST OK\r\n");
//	#endif		
//		}
//		else 
//		{
//	#if(FILE_LOG)		
//			printf ("CREAT LIST ERR %d\r\n",res);
//	#endif		
//		}
//	 f_close(&fList);
return res;
}

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
//}List_message

//void Fresh_List(void)
//{
//FRESULT res;
//char BIN_Directory[64]="0:/";
//BIN_message.lfsize = _MAX_LFN * 2 + 1;
//BIN_message.lfname = &BIN_Directory[3];	
//BIN_message.lfname[0]=0x00;
//res= f_opendir(&root_dir,"0:/");
//		if ( res == FR_OK )
//		{
//	#if(FILE_LOG)		
//			printf ("OPEN ROOT DIR OK\r\n");
//	#endif	   
//		}
//		else 
//		{
//	#if(FILE_LOG)		
//			printf ("OPEN ROOT DIR ERR%d\r\n",res);
//	#endif
//		}	
//uint8_t BIN_count=0;
//res = f_findfirst(&root_dir, &BIN_message, "", "F*.bin");
//		if (( res == FR_OK )&&BIN_message.lfname[0])
//		{	
//		res=f_open(&fList, (const TCHAR*)"0:/sys/List.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);		
//	#if(FILE_LOG)			
//			printf ("FIND BIN OK\r\n");
//	#endif
//			f_printf(&fList,"%3d_%s\r\n",BIN_count,(const TCHAR*)BIN_Directory);
//			f_sync(&fList);
//			BIN_message.lfname[0]=0x00;
//     BIN_count++;
//			
//		while((f_findnext(&root_dir, &BIN_message)==FR_OK)&&BIN_message.lfname[0])
//				{
//					#if(FILE_LOG)			
//					printf ("FIND BIN OK\r\n");
//					#endif		 
//					f_printf(&fList,"%3d_%s\r\n",BIN_count,(const TCHAR*)BIN_Directory);
//					f_sync(&fList);
//					BIN_message.lfname[0]=0x00;
//					BIN_count++;							
//				}	
//    f_close(&fList);				
//		}
//		else 
//		{
//	#if(FILE_LOG)			
//			printf ("NO BIN FILE\r\n");
//	#endif				
//		 f_closedir(&root_dir);	
////	   return 0;
//		}				
//}
uint8_t BIN_LIST_TABLE[100][64];
uint8_t BIN_LIST_TOTLE=0;
void Fresh_List(void)
{

char BIN_Directory[64]="0:/";
BIN_message.lfsize = _MAX_LFN * 2 + 1;
BIN_message.lfname = &BIN_Directory[3];	
BIN_message.lfname[0]=0x00;
res= f_opendir(&root_dir,"0:/");
		if ( res == FR_OK )
		{
	#if(FILE_LOG)		
			printf ("OPEN ROOT DIR OK\r\n");
	#endif	   
		}
		else 
		{
	#if(FILE_LOG)		
			printf ("OPEN ROOT DIR ERR%d\r\n",res);
	#endif
		}	
uint8_t BIN_count=0;
res = f_findfirst(&root_dir, &BIN_message, "", "F*.bin");
		if (( res == FR_OK )&&BIN_message.lfname[0])
		{	
		
	#if(FILE_LOG)			
			printf ("FIND BIN-%d OK\r\n",BIN_count);
	#endif
			delay_1ms();
			memset(&BIN_LIST_TABLE[BIN_count][0],'\0',64);
			sprintf ((char*)&BIN_LIST_TABLE[BIN_count][0],"%03d_%s",BIN_count,&BIN_Directory[3]);
			BIN_message.lfname[0]=0x00;
     BIN_count++;
			BIN_LIST_TOTLE=BIN_count;
		while((f_findnext(&root_dir, &BIN_message)==FR_OK)&&BIN_message.lfname[0])
				{
					#if(FILE_LOG)			
					printf ("FIND BIN-%d OK\r\n",BIN_count);
					#endif	
          delay_1ms();					
					memset(&BIN_LIST_TABLE[BIN_count][0],'\0',64);
					sprintf ((char*)&BIN_LIST_TABLE[BIN_count][0],"%03d_%s",BIN_count,&BIN_Directory[3]);
					BIN_message.lfname[0]=0x00;
					BIN_count++;
          BIN_LIST_TOTLE=BIN_count;					
				}					
		}
		else 
		{
	#if(FILE_LOG)			
			printf ("NO BIN FILE\r\n");
	#endif				
		 f_closedir(&root_dir);	
//	   return 0;
		}				
}
void Fresh_Last_File(void)
{

uint32_t read_count=0;	
	uint8_t buff[64];
memset(Last_File,'\0',64);	
res=f_open(&fLast, (const TCHAR*)"0:/sys/Last.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
res=f_read(&fLast,buff,64, (void *)&read_count);
if(read_count!=0)
	{
		Mem_Copy(buff,Last_File,read_count);
	}
	else
		{
	  Mem_Copy("NO FILE CHOOSE",Last_File,14);
	  }
	f_close(&fLast);
}

void Write_Last_File(uint8_t* buff)
{

uint32_t write_count=0;	
	
res=f_open(&fLast, (const TCHAR*)"0:/sys/Last.txt",FA_CREATE_ALWAYS|FA_WRITE|FA_READ);
res =f_write(&fLast,buff,64, (void *)&write_count);	
f_close(&fLast);
}
uint32_t file_size=0;
uint32_t Get_BIN_Size(uint8_t* file)
{

res=f_open(&fBIN, (const TCHAR*)file,FA_OPEN_ALWAYS|FA_READ);	
file_size=f_size(&fBIN);
f_close(&fBIN);
return file_size;	
}
void File_Test(void)
{
File_Creat_List();
Fresh_List();
}
void File_Init(void)
{
File_Creat_List();
Fresh_List();
Fresh_Last_File();
}


