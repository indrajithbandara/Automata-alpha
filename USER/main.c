#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "LCD.H"
#include "W25QXX.H"
#include "TOUCH.H"
#include "NRF24L01.H"

_LCD_CONFIG LCD_CONFIG;//LCD����
u8 DISPLAY_DIR_CTRL;//��Ļ�������

u8 tmp_buf[33];//NRF24L01 ����/���ͻ���

u16 POINT_COLOR;//��ǰ��ɫ
u16 BACK_COLOR;//������ɫ

int main(void)
{
	DISPLAY_DIR_CTRL=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);
	uart_init(115200);
	W25QXX_Init();
	LCD_INIT_ILI9325();
	POINT_COLOR=0x07E0;
	BACK_COLOR=0X0000;
	GUI_DRAW_FILL(0,0,LCD_CONFIG.LCD_WIDTH-1,LCD_CONFIG.LCD_HEIGHT-1,BACK_COLOR);
	TP_Init();
	
	while(1)
	{
		
	}
}
