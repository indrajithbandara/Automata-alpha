#include "DIGI_SERVO.h"

//舵机180度角度对应值
const u16 Servo_Angle[]={
	0  ,11 ,22 ,33 ,44 ,56 ,67 ,78 ,89 ,100,
	111,122,133,144,156,167,178,189,200,211,
	222,233,244,256,267,278,289,300,311,322,
	333,344,356,367,378,389,400,411,422,433,
	444,456,467,478,489,500,511,522,533,544,
	556,567,578,589,600,611,622,633,644,656,
	667,678,689,700,711,722,733,744,756,767,
	778,789,800,811,822,833,844,856,867,878,
	889,900,911,922,933,944,956,967,978,989,
	1000,1011,1022,1033,1044,1056,1067,1078,
	1089,1100,1111,1122,1133,1144,1156,1167,
	1178,1189,1200,1211,1222,1233,1244,1256,
	1267,1278,1289,1300,1311,1322,1333,1344,
	1356,1367,1378,1389,1400,1411,1422,1433,
	1444,1456,1467,1478,1489,1500,1511,1522,
	1533,1544,1556,1567,1578,1589,1600,1611,
	1622,1633,1644,1656,1667,1678,1689,1700,
	1711,1722,1733,1744,1756,1767,1778,1789,
	1800,1811,1822,1833,1844,1856,1867,1878,
	1889,1900,1911,1922,1933,1944,1956,1967,
	1978,1989,2000,
};

//初始化数字舵机信号线
void digitalServo_Init(){	
	GPIO_InitTypeDef IO_Init;//GPIO初始化结构体
	TIM_TimeBaseInitTypeDef TIM_Init;//定时器初始化结构体
	TIM_OCInitTypeDef TIM_OC_Init;//定时器输出比较初始化结构体
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIO时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //使能TIM1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE); //使能TIM8时钟
	
	//配置GPIO引脚复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
	
	//初始化GPIOA,GPIOC为复用模式输出
	IO_Init.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	IO_Init.GPIO_Mode=GPIO_Mode_AF;
	IO_Init.GPIO_OType=GPIO_OType_PP;
	IO_Init.GPIO_Speed=GPIO_Speed_100MHz;
	IO_Init.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&IO_Init);
	
	IO_Init.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOC,&IO_Init);
	
	//配置TIM1,TIM8定时器参数
	TIM_Init.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_Init.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Init.TIM_Prescaler=168-1;
	TIM_Init.TIM_Period=3000-1;
	TIM_Init.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_Init);
	TIM_TimeBaseInit(TIM8,&TIM_Init);
	
	//配置PWM输出参数
	TIM_OC_Init.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OC_Init.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC_Init.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM1, &TIM_OC_Init);
	TIM_OC2Init(TIM1, &TIM_OC_Init);
	TIM_OC3Init(TIM1, &TIM_OC_Init);
	TIM_OC4Init(TIM1, &TIM_OC_Init);
	TIM_OC1Init(TIM8, &TIM_OC_Init);
	TIM_OC2Init(TIM8, &TIM_OC_Init);
	TIM_OC3Init(TIM8, &TIM_OC_Init);
	TIM_OC4Init(TIM8, &TIM_OC_Init);
	
	//使能预装载寄存器与ARR寄存器
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_ARRPreloadConfig(TIM8,ENABLE);
	
	//使能TIM1/TIM8
	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_Cmd(TIM8,ENABLE);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
}

//使数字舵机旋转到固定的角度
void digitalServo_write(DigiServo servo){
	if(servo.Servo_Pin<=7 && servo.Angle<=180){
		switch(servo.Servo_Pin){
			case 0:TIM_SetCompare1(TIM1,Servo_Angle[servo.Angle]);break;
			case 1:TIM_SetCompare2(TIM1,Servo_Angle[servo.Angle]);break;
			case 2:TIM_SetCompare3(TIM1,Servo_Angle[servo.Angle]);break;
			case 3:TIM_SetCompare4(TIM1,Servo_Angle[servo.Angle]);break;
			case 4:TIM_SetCompare1(TIM8,Servo_Angle[servo.Angle]);break;
			case 5:TIM_SetCompare2(TIM8,Servo_Angle[servo.Angle]);break;
			case 6:TIM_SetCompare3(TIM8,Servo_Angle[servo.Angle]);break;
			case 7:TIM_SetCompare4(TIM8,Servo_Angle[servo.Angle]);break;
			default:break;
		}
	}
}

void digitalServo_toCenterPos(DigiServo servo){
	servo.Angle=90;
	digitalServo_write(servo);
}

void digitalServo_toMaxPos(DigiServo servo){
	servo.Angle=180;
	digitalServo_write(servo);
}

void digitalServo_toMinPos(DigiServo servo){
	servo.Angle=0;
	digitalServo_write(servo);
}
