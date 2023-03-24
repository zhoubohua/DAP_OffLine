/********************************************************************************
  * @file    Logic_Control.c
  * @author  ZBH
  * @version v1.0.0
  * @date    2021.08.24
  * @brief   Common functions
  ******************************************************************************
  ******************************************************************************
  */
#include "Logic_Control.h"
#define STATU_FILE_CHOOSE_INIT 0
#define STATU_FILE_CHOOSE_SER  1
#define STATU_FILE_BROW_INIT   2
#define STATU_FILE_BROW_SER    3
#define STATU_FILE_BURN_INIT   4
#define STATU_FILE_BURN_SER    5

uint8_t Logic_Statu=0;
extern uint8_t Last_File[64];
extern u8 KEY_DATA;
extern uint8_t BIN_LIST_TABLE[100][64];
extern uint8_t BIN_LIST_TOTLE;
extern uint32_t Bin_Size;
/*******************************************************************************
//Function Name  :  
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void File_Choosed_Init(void)
{
uint8_t length=0;
uint8_t i=0;
OLED_operate_gram(0);	
OLED_Roll_Set(0,0,32);
OLED_Roll_Set(1,0,32);
OLED_Roll_Set(2,0,32);
OLED_Roll_Set(3,0,32);

OLED_Invert_Set(0,0);
OLED_Invert_Set(1,0);
OLED_Invert_Set(2,0);
OLED_Invert_Set(3,0);	
	length=OLED_Show_String(0,0,(char *)"Current File:");	
length=OLED_Show_String(0,1,(char *)Last_File);//printf("%s\r\n",(char *)&Current_Page_Buff[3][0]);
//OLED_Invert_Set(Point_Flag,1);	
if(length>16)OLED_Roll_Set(1,1,length);
//	for(i=0;i<64;i++)
//	{
//	if((Last_File[i]==' ')|(Last_File[i]=='\0')|(Last_File[i]==0))
//		{
//		Last_File[i]=' ';
//		}
//	
//	}
//		for(i=0;i<64;i++)
//	{
//	if(Last_File[i]==' ')
//	break;
//	}
//	length =i;
//	i=0;
//for(i=0;i<4;i++)
//	{
//	 OLED_Show_Buff(0,i,(char *)&Last_File[i*16],16);
//	}
Logic_Statu=STATU_FILE_CHOOSE_SER;
}
/*******************************************************************************
//Function Name  :  
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void File_Choosed_Serve(void)
{
switch (KEY_DATA )
	{
	case KEY_BACK_SINGLE:{Logic_Statu=STATU_FILE_BROW_INIT;};break;
  case KEY_OK_SINGLE:{Logic_Statu=STATU_FILE_BURN_INIT;};break;	
  default :break;		
	}
KEY_DATA=0x00;	
}
/*******************************************************************************
//Function Name  :  
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
int8_t Point_Flag=0;
uint8_t Current_Page_Buff[4][64];
int8_t Current_BIN_Flag=0;
void File_Brow_Fresh_OLED(void)
{
uint8_t line_length[4];
OLED_operate_gram(0);	
OLED_Roll_Set(0,0,32);
OLED_Roll_Set(1,0,32);
OLED_Roll_Set(2,0,32);
OLED_Roll_Set(3,0,32);

OLED_Invert_Set(0,0);
OLED_Invert_Set(1,0);
OLED_Invert_Set(2,0);
OLED_Invert_Set(3,0);	
line_length[0]=OLED_Show_String(0,0,(char *)&Current_Page_Buff[0][0]);//printf("%s\r\n",(char *)&Current_Page_Buff[0][0]);
line_length[1]=OLED_Show_String(0,1,(char *)&Current_Page_Buff[1][0]);//printf("%s\r\n",(char *)&Current_Page_Buff[1][0]);
line_length[2]=OLED_Show_String(0,2,(char *)&Current_Page_Buff[2][0]);//printf("%s\r\n",(char *)&Current_Page_Buff[2][0]);
line_length[3]=OLED_Show_String(0,3,(char *)&Current_Page_Buff[3][0]);//printf("%s\r\n",(char *)&Current_Page_Buff[3][0]);
OLED_Invert_Set(Point_Flag,1);	
if(line_length[Point_Flag]>16)OLED_Roll_Set(Point_Flag,1,line_length[Point_Flag]);
}


void File_Brow_Init(void)
{
	uint8_t i=0;
for(i=0;i<4;i++)
	{
	Mem_Copy(&BIN_LIST_TABLE[i][0],&Current_Page_Buff[i][0],64);
	}
File_Brow_Fresh_OLED();
Logic_Statu=STATU_FILE_BROW_SER;
}
/*******************************************************************************
//Function Name  :  
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Brow_Down_Serve(void)
{
	uint8_t i=0;
Current_BIN_Flag++;
if(Current_BIN_Flag>BIN_LIST_TOTLE-1)
{
Current_BIN_Flag=BIN_LIST_TOTLE-1;
}
Point_Flag++;
if(Point_Flag>3)
	{
	Point_Flag=3;
	for(i=0;i<4;i++)
		{
		Mem_Copy(&BIN_LIST_TABLE[Current_BIN_Flag-3+i][0],&Current_Page_Buff[i][0],64);
		}		
	}
File_Brow_Fresh_OLED();
}


void Brow_Up_Serve(void)
{
	uint8_t i=0;
Current_BIN_Flag--;
if(Current_BIN_Flag<=0)
{
Current_BIN_Flag=0;
}

	
Point_Flag--;
if(Point_Flag<=0)
	{
	Point_Flag=0;
	for(i=0;i<4;i++)
		{
		Mem_Copy(&BIN_LIST_TABLE[Current_BIN_Flag+i][0],&Current_Page_Buff[i][0],64);
		}		
	}
File_Brow_Fresh_OLED();
}
void Brow_OK_Serve(void)
{

Mem_Copy(&BIN_LIST_TABLE[Current_BIN_Flag][0],Last_File,64);

Logic_Statu=STATU_FILE_CHOOSE_INIT;	
}


void File_Brow_Serve(void)
{

switch (KEY_DATA )
	{
	case KEY_DOWN_SINGLE:{Brow_Down_Serve();};break;
	case KEY_UP_SINGLE:{Brow_Up_Serve();};break;
  case KEY_OK_SINGLE:{Brow_OK_Serve();};break;	
  default :break;		
	}
KEY_DATA=0x00;	
}
/*******************************************************************************
//Function Name  :  
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void File_Burn_Init(void)
{
uint8_t  buff[64];
Write_Last_File(Last_File);
OLED_operate_gram(0);	
OLED_Show_String(0,0,(char *)"File");	
Check_BIN_File(Last_File);
sprintf ((char*)buff,"%.2fkb",Bin_Size/1024.0);	
OLED_Show_String(48,0,(char *)buff);	
Logic_Statu=STATU_FILE_BURN_SER;
}
/*******************************************************************************
//Function Name  :  
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void File_Burn_Serve(void)
{
//Erease_Flash();
Burn_Test();	
//switch (KEY_DATA )
//	{
//	case KEY_BACK_SINGLE:{Logic_Statu=STATU_FILE_BROW_INIT;};break;
//  case KEY_OK_SINGLE:{Logic_Statu=STATU_FILE_BURN_INIT;};break;	
//  default :break;		
//	}
	Logic_Statu=STATU_FILE_CHOOSE_INIT;
}
/*******************************************************************************
//Function Name  : Logic_Serve(void) 
//Description    : 
//USE            : 
//Input          : None.  
//Output         : None.
//Return         : None.
//EDITER         : ZBH
*******************************************************************************/
void Logic_Serve(void)
{
switch(Logic_Statu)
{
	case STATU_FILE_CHOOSE_INIT:{File_Choosed_Init();};break; 
	case STATU_FILE_CHOOSE_SER:{File_Choosed_Serve();};break;
	case STATU_FILE_BROW_INIT:{File_Brow_Init();};break; 
	case STATU_FILE_BROW_SER:{File_Brow_Serve();};break;
	case STATU_FILE_BURN_INIT:{File_Burn_Init();};break; 
	case STATU_FILE_BURN_SER:{File_Burn_Serve();};break;
	default:break;
}
}