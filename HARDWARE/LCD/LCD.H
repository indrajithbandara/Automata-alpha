#ifndef __LCD_H
#define __LCD_H	

#include "SYS.H"

/////////////////////////////////////
//FSMC_D0->PD14=>LCD_D0
//FSMC_D1->PD15=>LCD_D1
//FSMC_D2->PD0=>LCD_D2
//FSMC_D3->PD1=>LCD_D3
//FSMC_D4->PE7=>LCD_D4
//FSMC_D5->PE8=>LCD_D5
//FSMC_D6->PE9=>LCD_D6
//FSMC_D7->PE10=>LCD_D7
//FSMC_D8->PE11=>LCD_D8
//FSMC_D9->PE12=>LCD_D9
//FSMC_D10->PE13=>LCD_D10
//FSMC_D11->PE14=>LCD_D11
//FSMC_D12->PE15=>LCD_D12
//FSMC_D13->PD8=>LCD_D13
//FSMC_D14->PD9=>LCD_D14
//FSMC_D15->PD10=>LCD_D15

//LCD_RS:A18->PD13
//LCD_CS:FSMC_NE1->PD7
//LCD_WR:FSMC_NWE->PD5
//LCD_RD:FSMC_NOE->PD4

//BACKLIGHT->PB1

//RESET->PD3
/////////////////////////////////////

typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

//ʹ��NOR/SRAM�� Bank1.sector1,��ַλHADDR[27,26]=00 A18��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ���� 0111 1111 1111 1111 1110=0X07FFFE	

#define LCD_BASE        ((u32)(0x60000000 | 0x0007FFFE))
#define LCD             ((LCD_TypeDef*)LCD_BASE)

#define LCD_BACKLIGHT PBout(1)//���� PD3

/////FLASH�ֿ�ƫ��������//////////
#define GB2312_16X16  0x00000000
#define GB2312_12X12  0x00045080
#define GB2312_24X24  0x00078CE0
//����ƫ����
#define SONGTI 	 0x00000000//����
#define KAITI  	 0x00114200//����
#define YOUYUAN  0x00228400//��Բ
//////////////////////////////////

typedef struct  
{										    
	u16 LCD_WIDTH;			//LCD ����
	u16 LCD_HEIGHT;			//LCD �߶�
	u16 LCD_ID;				//LCD ID
	u8  DISPLAY_DIR;			//���������������ƣ�0��������1��������	
	u16	WRGRAM_CMD;		//��ʼдgramָ��
	u16  SETX_CMD;		//����x����ָ��
	u16  SETY_CMD;		//����y����ָ�� 
}_LCD_CONFIG;//LCD�����ṹ��

extern _LCD_CONFIG LCD_CONFIG;//LCD�ṹ��
extern u8 DISPLAY_DIR_CTRL;

extern u16 POINT_COLOR;//��ǰ��ɫ
extern u16 BACK_COLOR;//������ɫ

//////////////////////////////��ʼ�������������ӿں������ڲ���
void LCD_FSMC_INIT(void);
//void LCD_RESET(void);
void LCD_WR_REG(u16 data);
void LCD_WR_DATA(u16 data);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
////////////////////////////////////////////////////////////

/////////////////////////////////////////���������������ӿڣ�
void LCD_INIT_ILI9325(void);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
void LCD_DrawPoint(u16 x,u16 y);
void LCD_SetParam(void);
void LCD_Clear(u16 COLOR);
////////////////////////////////////////////////////////////

/********************************/
///////////////GUI////////////////
/********************************/

//////////////////////////////�����װ�ӿ�/////////////////////////////////////////////////
/************************����GUI**********************/
void GUI_DRAW_POINT(u16 x,u16 y,u16 color);//����
void GUI_DRAW_FILL(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);//���
void GUI_SHOW_STR(u8 size,u16 x,u16 y,u32 FONT,u8 *STR);//����ַ��������ִ�С
void GUI_SHOW_NUM(u16 x,u16 y,u32 num,u8 len,u8 size);//��ӡ���֣����ٽӿڣ����ִ�С
void GUI_DRAW_LINE(u16 x1, u16 y1, u16 x2, u16 y2);//����
void GUI_DRAW_RECTANGLE(u16 x1, u16 y1, u16 x2, u16 y2);//������
void GUI_DRAW_CIRCLE(u16 x0,u16 y0,u8 r);//��Բ
///////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////����Ϊ�ڲ��ӿ�///////////////////////////////////////////////
void GUI_SHOW_CHAR_12X6(u16 x,u16 y,u8 ascii);//(˽�к���)
void GUI_SHOW_ASCIISTR_12X6(u16 x,u16 y,u8 *str);//(˽�к���)
void GUI_SHOW_ONE_HANZI_12X12(u16 x,u16 y,u8 *GBCODE);//(˽�к���)
void GUI_SHOW_STR_HANZI_12X12(u16 x,u16 y,u32 FONT,u8 *GBCODE);//(˽�к���)
void GUI_SHOW_STR_12X12(u16 x,u16 y,u32 FONT,u8 *GBCODE);//���12X12�ַ���(GB2312+ASCIIȫ�ַ�֧��)

void GUI_SHOW_CHAR_16X8(u16 x,u16 y,u8 ascii);//(˽�к���)
void GUI_SHOW_ASCIISTR_16X8(u16 x,u16 y,u8 *str);//(˽�к���)
void GUI_SHOW_ONE_HANZI_16X16(u16 x,u16 y,u8 *GBCODE);//(˽�к���)
void GUI_SHOW_STR_HANZI_16X16(u16 x,u16 y,u32 FONT,u8 *GBCODE);//(˽�к���)
void GUI_SHOW_STR_16X16(u16 x,u16 y,u32 FONT,u8 *GBCODE);//���16X16�ַ���(GB2312+ASCIIȫ�ַ�֧��)

void GUI_SHOW_CHAR_24X12(u16 x,u16 y,u8 ascii);//(˽�к���)
void GUI_SHOW_ASCIISTR_24X12(u16 x,u16 y,u8 *str);//(˽�к���)
void GUI_SHOW_ONE_HANZI_24X24(u16 x,u16 y,u8 *GBCODE);//(˽�к���)
void GUI_SHOW_STR_HANZI_24X24(u16 x,u16 y,u32 FONT,u8 *GBCODE);//(˽�к���)
void GUI_SHOW_STR_24X24(u16 x,u16 y,u32 FONT,u8 *GBCODE);//���24X24�ַ���(GB2312+ASCIIȫ�ַ�֧��)

///////////////////////////////////////////////////////////////////////////////////////////////

#endif  