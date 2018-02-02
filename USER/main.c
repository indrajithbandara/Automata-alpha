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
	/////////////////////////////////////////////////////////////////////////////ϵͳ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);//��ʱ��ʼ��
	uart_init(115200);//����1��ʼ��

	/////////////////////////////////////////////////////////////////////////////Ӳ����ʼ��
	W25QXX_Init();//FLASH��ʼ��
	LCD_INIT_ILI9325();//LCD��ʼ��
	POINT_COLOR=0x07E0;//������ɫ
	BACK_COLOR=0X0000;//������ɫ
	AT24CXX_Init();
	TP_Init();
	digitalServo_Init();
	/////////////////////////////////////////////////////////////////////////////������ʼ��
	GUI_DRAW_FILL(0,0,LCD_CONFIG.LCD_WIDTH-1,LCD_CONFIG.LCD_HEIGHT-1,BACK_COLOR);//Һ����ʾ��������Ϊ��ɫ
	
	while(1)
	{
		
	}
}
