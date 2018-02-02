#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "LCD.H"
#include "W25QXX.H"
#include "24CXX.H"
#include "TOUCH.H"
#include "NRF24L01.H"
#include "DIGI_SERVO.H"

int main(void)
{
	/////////////////////////////////////////////////////////////////////////////系统初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);//延时初始化
	uart_init(115200);//串口1初始化

	/////////////////////////////////////////////////////////////////////////////硬件初始化
	W25QXX_Init();//FLASH初始化
	LCD_INIT_ILI9325();//LCD初始化
	POINT_COLOR=0x07E0;//画笔颜色
	BACK_COLOR=0X0000;//背景颜色
	AT24CXX_Init();
	TP_Init();
	digitalServo_Init();
	/////////////////////////////////////////////////////////////////////////////其他初始化
	GUI_DRAW_FILL(0,0,LCD_CONFIG.LCD_WIDTH-1,LCD_CONFIG.LCD_HEIGHT-1,BACK_COLOR);//液晶显示背景设置为黑色
	
	while(1)
	{
		
	}
}
