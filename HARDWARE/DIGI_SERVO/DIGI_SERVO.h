#ifndef DIGI_SERVO_H
#define DIGI_SERVO_H
/***************************************************/
//本库使用STM32F4高级定时器TIM1/TIM8驱动数字舵机
//可以驱动多达8个数字舵机
//
//适配数字舵机型号：
//KS-3518,MG995
//
//对应端口：
//  channel  |  pin   |   id
// ----------|--------|-------
// TIM1_CH1  |  PA8   |   0
// TIM1_CH2  |  PA9   |   1
// TIM1_CH3  |  PA10  |   2
// TIM1_CH4  |  PA11  |   3
// TIM8_CH1  |  PC6   |   4
// TIM8_CH2  |  PC7   |   5
// TIM8_CH3  |  PC8   |   6
// TIM8_CH4  |  PC9   |   7
/***************************************************/

#include "sys.h"

typedef struct DigiServo{
	u8 Servo_Pin;
	u8 Angle;
}DigiServo;

void digitalServo_Init(void);//初始化舵机驱动，必须首先调用该函数才能开始使用
void digitalServo_write(DigiServo servo);
void digitalServo_toCenterPos(DigiServo servo);
void digitalServo_toMaxPos(DigiServo servo);
void digitalServo_toMinPos(DigiServo servo);

 
#endif
