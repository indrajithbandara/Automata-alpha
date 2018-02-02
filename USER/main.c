#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "LCD.H"
#include "W25QXX.H"
#include "TOUCH.H"
#include "NRF24L01.H"

_LCD_CONFIG LCD_CONFIG;//LCD参数
u8 DISPLAY_DIR_CTRL;//屏幕方向控制

u8 tmp_buf[33];//NRF24L01 接受/发送缓存

u16 POINT_COLOR;//当前颜色
u16 BACK_COLOR;//背景颜色

int main(void)
{
	DISPLAY_DIR_CTRL=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
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
