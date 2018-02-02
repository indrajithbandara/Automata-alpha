#include "LCD.H"
#include "ASCIICODE.H"
#include "W25QXX.H"

void LCD_FSMC_INIT(void)
{
	GPIO_InitTypeDef LCD_FSMC_INIT;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//使能PD,PE时钟  
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟 
	
//////////初始化PD口为复用输出////////////////	
	LCD_FSMC_INIT.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	LCD_FSMC_INIT.GPIO_OType=GPIO_OType_PP;
	LCD_FSMC_INIT.GPIO_Mode=GPIO_Mode_AF;	
	LCD_FSMC_INIT.GPIO_PuPd=GPIO_PuPd_UP;
	LCD_FSMC_INIT.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&LCD_FSMC_INIT);
//////////////////////////////////////////////
	
//////////初始化PD2为背光输出/////////////////
	LCD_FSMC_INIT.GPIO_Pin=GPIO_Pin_1;
	LCD_FSMC_INIT.GPIO_OType=GPIO_OType_PP;
	LCD_FSMC_INIT.GPIO_Mode=GPIO_Mode_OUT;	
	LCD_FSMC_INIT.GPIO_PuPd=GPIO_PuPd_UP;
	LCD_FSMC_INIT.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&LCD_FSMC_INIT);
//////////////////////////////////////////////

//////////初始化PE口为复用输出////////////////	
	LCD_FSMC_INIT.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	LCD_FSMC_INIT.GPIO_OType=GPIO_OType_PP;
	LCD_FSMC_INIT.GPIO_Mode=GPIO_Mode_AF;	
	LCD_FSMC_INIT.GPIO_PuPd=GPIO_PuPd_UP;
	LCD_FSMC_INIT.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&LCD_FSMC_INIT);
//////////////////////////////////////////////

///////////////FSMC复用配置///////////////////
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC); 	
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);
 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);
//////////////////////////////////////////////

///////////////FSMC时序配置///////////////////
  readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
  readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
	
	writeTiming.FSMC_AddressSetupTime =9;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
  writeTiming.FSMC_DataSetupTime = 8;		 //数据保存时间为6ns*9个HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x00;
  writeTiming.FSMC_DataLatency = 0x00;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
//////////////////////////////////////////////

///////////////FSMC总线配置///////////////////
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//使用NE1
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; //不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;//FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;//FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; //读写使用不同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // 使能BANK1,PART1
}
//////////////////////////////////////////////
/*void LCD_RESET(void)
{
	LCD_RST_CLR;
	delay_ms(100);	
	LCD_RST_SET;
	delay_ms(50);
}*/
//////////////////////////////////////////////
void LCD_WR_REG(u16 data)
{ 
	LCD->LCD_REG=data;//写入要写的寄存器序号	 	
}
//////////////////////////////////////////////
void LCD_WR_DATA(u16 data)
{
	LCD->LCD_RAM=data;
}
//////////////////////////////////////////////
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//写入要写的寄存器序号	 
	LCD->LCD_RAM = LCD_RegValue;//写入数据	     		 
}	
//////////////////////////////////////////////
void LCD_SetParam(void)
{ 	
	LCD_CONFIG.WRGRAM_CMD=0x22;
	if(DISPLAY_DIR_CTRL==1)
	{	  
		LCD_CONFIG.DISPLAY_DIR=1;//横屏
		LCD_CONFIG.LCD_WIDTH=320;
		LCD_CONFIG.LCD_HEIGHT=240;
		LCD_CONFIG.SETX_CMD=0x21;
		LCD_CONFIG.SETY_CMD=0x20;			
		LCD_WriteReg(0x03,0x1038);
		LCD_WriteReg(0x0060,0x2700);
	}
	else
	{
		LCD_CONFIG.DISPLAY_DIR=0;//竖屏				 	 		
		LCD_CONFIG.LCD_WIDTH=240;
		LCD_CONFIG.LCD_HEIGHT=320;
		LCD_CONFIG.SETX_CMD=0x20;
		LCD_CONFIG.SETY_CMD=0x21;	
		LCD_WriteReg(0x03,0x1030);
		LCD_WriteReg(0x0060,0xA700);
	}
}	
//////////////////////////////////////////////
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(LCD_CONFIG.WRGRAM_CMD);
}
//////////////////////////////////////////////
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_WR_REG(LCD_CONFIG.SETX_CMD);	
	LCD_WR_DATA(Xpos);

	LCD_WR_REG(LCD_CONFIG.SETY_CMD);	
	LCD_WR_DATA(Ypos);

	LCD_WriteRAM_Prepare();	//开始写入GRAM	
} 
//////////////////////////////////////////////
void LCD_SetWindows(u16 xStart, u16 yStart,u16 xEnd,u16 yEnd)
{	
	if(DISPLAY_DIR_CTRL==1)//横屏
	{	
	LCD_WR_REG(0x52);	
	LCD_WR_DATA(xStart);
	LCD_WR_REG(0x53);		
	LCD_WR_DATA(xEnd);
	LCD_WR_REG(0x50);	
	LCD_WR_DATA(yStart);
	LCD_WR_REG(0x51);		
	LCD_WR_DATA(yEnd);
	}
	else 
	{
	LCD_WR_REG(0x50);	
	LCD_WR_DATA(xStart);
	LCD_WR_REG(0x51);		
	LCD_WR_DATA(xEnd);
	LCD_WR_REG(0x52);	
	LCD_WR_DATA(yStart);
	LCD_WR_REG(0x53);		
	LCD_WR_DATA(yEnd);
	}
	LCD_WR_REG(LCD_CONFIG.SETX_CMD);	
	LCD_WR_DATA(xStart);	
	LCD_WR_REG(LCD_CONFIG.SETY_CMD);	
	LCD_WR_DATA(yStart);

	LCD_WriteRAM_Prepare();	//开始写入GRAM				
}   
//////////////////////////////////////////////
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);
	LCD_WR_DATA(POINT_COLOR);
}
//////////////////////////////////////////////
void LCD_INIT_ILI9325(void)
{
	LCD_FSMC_INIT();
	//LCD_RESET();
	
	//************* Start Initial Sequence **********//		
	LCD_WriteReg(0x00E5,0x78F0); 
	LCD_WriteReg(0x0001,0x0100); 
	LCD_WriteReg(0x0002,0x0700); 
	LCD_WriteReg(0x0003,0x1030); 
	LCD_WriteReg(0x0004,0x0000); 
	LCD_WriteReg(0x0008,0x0202);  
	LCD_WriteReg(0x0009,0x0000);
	LCD_WriteReg(0x000A,0x0000); 
	LCD_WriteReg(0x000C,0x0000); 
	LCD_WriteReg(0x000D,0x0000);
	LCD_WriteReg(0x000F,0x0000);
	//power on sequence VGHVGL
	LCD_WriteReg(0x0010,0x0000);   
	LCD_WriteReg(0x0011,0x0007);  
	LCD_WriteReg(0x0012,0x0000);  
	LCD_WriteReg(0x0013,0x0000); 
	LCD_WriteReg(0x0007,0x0000); 
	//vgh 
	LCD_WriteReg(0x0010,0x1690);   
	LCD_WriteReg(0x0011,0x0227);
	//delay_ms(100);
	//vregiout 
	LCD_WriteReg(0x0012,0x009D); //0x001b
	//delay_ms(100); 
	//vom amplitude
	LCD_WriteReg(0x0013,0x1900);
	//delay_ms(100); 
	//vom H
	LCD_WriteReg(0x0029,0x0025); 
	LCD_WriteReg(0x002B,0x000D); 
	//gamma
	LCD_WriteReg(0x0030,0x0007);
	LCD_WriteReg(0x0031,0x0303);
	LCD_WriteReg(0x0032,0x0003);// 0006
	LCD_WriteReg(0x0035,0x0206);
	LCD_WriteReg(0x0036,0x0008);
	LCD_WriteReg(0x0037,0x0406); 
	LCD_WriteReg(0x0038,0x0304);//0200
	LCD_WriteReg(0x0039,0x0007); 
	LCD_WriteReg(0x003C,0x0602);// 0504
	LCD_WriteReg(0x003D,0x0008); 
	//ram
	LCD_WriteReg(0x0050,0x0000); 
	LCD_WriteReg(0x0051,0x00EF);
	LCD_WriteReg(0x0052,0x0000); 
	LCD_WriteReg(0x0053,0x013F);  
	LCD_WriteReg(0x0060,0xA700); 
	LCD_WriteReg(0x0061,0x0001); 
	LCD_WriteReg(0x006A,0x0000); 
	//
	LCD_WriteReg(0x0080,0x0000); 
	LCD_WriteReg(0x0081,0x0000); 
	LCD_WriteReg(0x0082,0x0000); 
	LCD_WriteReg(0x0083,0x0000); 
	LCD_WriteReg(0x0084,0x0000); 
	LCD_WriteReg(0x0085,0x0000); 
	//
	LCD_WriteReg(0x0090,0x0010); 
	LCD_WriteReg(0x0092,0x0600); 
	
	LCD_WriteReg(0x0007,0x0133);
	LCD_WriteReg(0x00,0x0022);//	

	
	LCD_SetParam();
	LCD_BACKLIGHT=1;
}

void LCD_Clear(u16 COLOR)
{
	GUI_DRAW_FILL(0,0,LCD_CONFIG.LCD_WIDTH-1,LCD_CONFIG.LCD_HEIGHT-1,COLOR);
}

//////////////////////////////////////////////
/******************GUI函数*******************/
//////////////////////////////////////////////
//画点
void GUI_DRAW_POINT(u16 x,u16 y,u16 color)
{
	LCD_SetCursor(x,y);
	LCD->LCD_RAM=color;
}
//////////////////////////////////////////////
//ASCII基本字符单字12X6
void GUI_SHOW_CHAR_12X6(u16 x,u16 y,u8 ascii)
{
	u8 i,j;
	u8 line;
	u16 x0=x;
	ascii=ascii-' ';
	
		for(i=0;i<12;i++)
		{
			if(y>=LCD_CONFIG.LCD_HEIGHT)return;
			line=ASCII_1206[ascii][i];
			for(j=0;j<6;j++)
			{
				if((line&0x01)==1){LCD_DrawPoint(x,y);}else{GUI_DRAW_POINT(x,y,BACK_COLOR);}
				line>>=1;
				x++;
			}
			x=x0;
			y++;
		}
}
//////////////////////////////////////////////
//ASCII字符串12X6
void GUI_SHOW_ASCIISTR_12X6(u16 x,u16 y,u8 *str)
{
	while(*str!='\0')
	{
		GUI_SHOW_CHAR_12X6(x,y,*str);
		x+=6;
		str++;
	}
}
//////////////////////////////////////////////
//GB2312单个字符12X12
void GUI_SHOW_ONE_HANZI_12X12(u16 x,u16 y,u8 *GBCODE)
{
	u16 x0;
	u8 i,j;
	u16 CodeTemp;
	
	x0=x;
	for(i=0;i<12;i++)
	{
			CodeTemp=*GBCODE<<8;
			GBCODE++;
			CodeTemp+=*GBCODE;
			GBCODE++;
			if(y>=LCD_CONFIG.LCD_HEIGHT)return;
			for(j=0;j<12;j++)
			{
				if(((CodeTemp&0X8000)>>15)==1){LCD_DrawPoint(x,y);}else{GUI_DRAW_POINT(x,y,BACK_COLOR);}
				CodeTemp<<=1;
				x++;
			}
			x=x0;
			y++;
	}
}
//////////////////////////////////////////////
//GB2312字符串12X12
void GUI_SHOW_STR_HANZI_12X12(u16 x,u16 y,u32 FONT,u8 *GBCODE)
{
		//u8 i,j;
	u8 CodeBuff[24];
	u8 HGB,LGB;
	u32 offset;
	
	while(*GBCODE!='\0')
	{
		HGB=*GBCODE;
		GBCODE++;
		LGB=*GBCODE;
		GBCODE++;
		HGB-=0xA0;
		LGB-=0XA0;
		offset=(94*(HGB-1)+(LGB-1))*24;
		W25QXX_Read(CodeBuff,offset+GB2312_12X12+FONT,24);
		GUI_SHOW_ONE_HANZI_12X12(x,y,CodeBuff);
		x+=12;
	}
}
//////////////////////////////////////////////
//全字符显示（内置ASCII+外置GB2312）12X12
void GUI_SHOW_STR_12X12(u16 x,u16 y,u32 FONT,u8 *GBCODE)
{
	u16 x0;
	u8 CodeBuff[24];
	u8 HGB,LGB;
	u32 offset;
	
	x0=x;
	
	while(*GBCODE!='\0')
	{
		HGB=*GBCODE;
		GBCODE++;
		LGB=*GBCODE;
		GBCODE++;
		if((HGB&0x80)>>7==0)
		{
			if((LGB&0x80)>>7==0)//两个都是ascii
			{
				if(LGB=='\0')//下一个是结束符
				{
					if(x+6>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
					GUI_SHOW_CHAR_12X6(x,y,HGB);
					x+=6;
					GBCODE--;
				}
				else
				{
					if(x+6>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
					GUI_SHOW_CHAR_12X6(x,y,HGB);
					x+=6;
					if(x+6>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
					GUI_SHOW_CHAR_12X6(x,y,LGB);
					x+=6;
				}
			}
			else//第一个是ASCII,第二个是下一个gb2312的第一个字节
			{
				if(x+6>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
				GUI_SHOW_CHAR_12X6(x,y,HGB);
				x+=8;
				GBCODE--;
			}
		}
		else
		{
			if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
			HGB-=0xA0;
			LGB-=0XA0;
			offset=(94*(HGB-1)+(LGB-1))*24;
			W25QXX_Read(CodeBuff,offset+GB2312_12X12+FONT,24);
			GUI_SHOW_ONE_HANZI_12X12(x,y,CodeBuff);
			x+=12;
		}
	}
}
//////////////////////////////////////////////
//ASCII基本字符单字16X8
void GUI_SHOW_CHAR_16X8(u16 x,u16 y,u8 ascii)
{
	u8 i,j;
	u8 line;
	u16 x0=x;
	ascii=ascii-' ';
	
		for(i=0;i<16;i++)
		{
			line=ASCII_1608[ascii][i];
			if(y>=LCD_CONFIG.LCD_HEIGHT)return;
			for(j=0;j<8;j++)
			{
				if((line&0x01)==1){LCD_DrawPoint(x,y);}else{GUI_DRAW_POINT(x,y,BACK_COLOR);}
				line>>=1;
				x++;
			}
			x=x0;
			y++;
		}
}
//////////////////////////////////////////////
//ASCII字符串16X8
void GUI_SHOW_ASCIISTR_16X8(u16 x,u16 y,u8 *str)
{
	while(*str!='\0')
	{
		GUI_SHOW_CHAR_16X8(x,y,*str);
		x+=8;
		str++;
	}
}
//////////////////////////////////////////////
//GB2312单个字符16X16
void GUI_SHOW_ONE_HANZI_16X16(u16 x,u16 y,u8 *GBCODE)
{
	u16 x0;
	u8 i,j;
	u16 CodeTemp;
	
	x0=x;
	for(i=0;i<16;i++)
	{
		CodeTemp=*GBCODE<<8;
		GBCODE++;
		CodeTemp+=*GBCODE;
		GBCODE++;
		if(y>=LCD_CONFIG.LCD_HEIGHT)return;
		for(j=0;j<16;j++)
		{
			if(((CodeTemp&0X8000)>>15)==1){LCD_DrawPoint(x,y);}else{GUI_DRAW_POINT(x,y,BACK_COLOR);}
			CodeTemp<<=1;
			x++;
		}
		x=x0;
		y++;
	}
}
//////////////////////////////////////////////
//GB2312字符串16X16
void GUI_SHOW_STR_HANZI_16X16(u16 x,u16 y,u32 FONT,u8 *GBCODE)
{
	//u8 i,j;
	u8 CodeBuff[32];
	u8 HGB,LGB;
	u32 offset;
	
	while(*GBCODE!='\0')
	{
		HGB=*GBCODE;
		GBCODE++;
		LGB=*GBCODE;
		GBCODE++;
		HGB-=0xA0;
		LGB-=0XA0;
		offset=(94*(HGB-1)+(LGB-1))*32;
		W25QXX_Read(CodeBuff,offset+GB2312_16X16+FONT,32);
		GUI_SHOW_ONE_HANZI_16X16(x,y,CodeBuff);
		x+=16;
	}

}
//////////////////////////////////////////////
//全字符显示（内置ASCII+外置GB2312）16X16
void GUI_SHOW_STR_16X16(u16 x,u16 y,u32 FONT,u8 *GBCODE)
{
	u16 x0;
	u8 CodeBuff[32];
	u8 HGB,LGB;
	u32 offset;
	
	x0=x;
	
	while(*GBCODE!='\0')
	{
		HGB=*GBCODE;
		GBCODE++;
		LGB=*GBCODE;
		GBCODE++;
		if((HGB&0x80)>>7==0)
		{
			if((LGB&0x80)>>7==0)//两个都是ascii
			{
				if(LGB=='\0')//下一个是结束符
				{
					if(x+8>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
					GUI_SHOW_CHAR_16X8(x,y,HGB);
					x+=8;
					GBCODE--;
				}
				else
				{
					if(x+8>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
					GUI_SHOW_CHAR_16X8(x,y,HGB);
					x+=8;
					if(x+8>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
					GUI_SHOW_CHAR_16X8(x,y,LGB);
					x+=8;
				}
			}
			else//第一个是ASCII,第二个是下一个gb2312的第一个字节
			{
				if(x+8>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
				GUI_SHOW_CHAR_16X8(x,y,HGB);
				x+=8;
				GBCODE--;
			}
		}
		else
		{
			if(x+16>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
			HGB-=0xA0;
			LGB-=0XA0;
			offset=(94*(HGB-1)+(LGB-1))*32;
			W25QXX_Read(CodeBuff,offset+GB2312_16X16+FONT,32);
			GUI_SHOW_ONE_HANZI_16X16(x,y,CodeBuff);
			x+=16;
		}
	}
}
//////////////////////////////////////////////
//ASCII基本字符单字24X12
void GUI_SHOW_CHAR_24X12(u16 x,u16 y,u8 ascii)
{
	u8 i,j;
	u16 line;
	u16 x0=x;
	ascii=ascii-' ';
	
		for(i=0;i<24;i++)
		{
			if(y>=LCD_CONFIG.LCD_HEIGHT)return;
			line=(ASCII_2412[ascii][i*2])+((ASCII_2412[ascii][i*2+1])<<8);
			for(j=0;j<12;j++)
			{
				if((line&0x0001)==1){LCD_DrawPoint(x,y);}else{GUI_DRAW_POINT(x,y,BACK_COLOR);}
				line>>=1;
				x++;
			}
			x=x0;
			y++;
		}
}
//////////////////////////////////////////////
//ASCII字符串24X12
void GUI_SHOW_ASCIISTR_24X12(u16 x,u16 y,u8 *str)
{
	while(*str!='\0')
	{
		GUI_SHOW_CHAR_24X12(x,y,*str);
		x+=12;
		str++;
	}
}
//////////////////////////////////////////////
//GB2312单个字符24X24
void GUI_SHOW_ONE_HANZI_24X24(u16 x,u16 y,u8 *GBCODE)
{
	u16 x0;
	u8 i,j;
	u32 CodeTemp;
	
	x0=x;
	for(i=0;i<24;i++)
	{
		CodeTemp=*GBCODE<<24;
		GBCODE++;
		CodeTemp+=*GBCODE<<16;
		GBCODE++;
		CodeTemp+=*GBCODE<<8;
		GBCODE++;
		if(y>=LCD_CONFIG.LCD_HEIGHT)return;
		for(j=0;j<24;j++)
		{
			if(((CodeTemp&0X80000000)>>31)==1){LCD_DrawPoint(x,y);}else{GUI_DRAW_POINT(x,y,BACK_COLOR);}
			CodeTemp<<=1;
			x++;
		}
		x=x0;
		y++;
	}
}
//////////////////////////////////////////////
//GB2312字符串24X24
void GUI_SHOW_STR_HANZI_24X24(u16 x,u16 y,u32 FONT,u8 *GBCODE)
{
	//u8 i,j;
	u8 CodeBuff[72];
	u8 HGB,LGB;
	u32 offset;
	
	while(*GBCODE!='\0')
	{
		HGB=*GBCODE;
		GBCODE++;
		LGB=*GBCODE;
		GBCODE++;
		HGB-=0xA0;
		LGB-=0XA0;
		offset=(94*(HGB-1)+(LGB-1))*72;
		W25QXX_Read(CodeBuff,offset+GB2312_24X24+FONT,72);
		GUI_SHOW_ONE_HANZI_24X24(x,y,CodeBuff);
		x+=24;
	}

}
//////////////////////////////////////////////
//全字符显示（内置ASCII+外置GB2312）24X24
void GUI_SHOW_STR_24X24(u16 x,u16 y,u32 FONT,u8 *GBCODE)
{
	u16 x0;
	u8 CodeBuff[72];
	u8 HGB,LGB;
	u32 offset;
	
	x0=x;
	
	while(*GBCODE!='\0')
	{
		HGB=*GBCODE;
		GBCODE++;
		LGB=*GBCODE;
		GBCODE++;
		if((HGB&0x80)>>7==0)
		{
			if((LGB&0x80)>>7==0)//两个都是ascii
			{
				if(LGB=='\0')//下一个是结束符
				{
					if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
					GUI_SHOW_CHAR_24X12(x,y,HGB);
					x+=12;
					GBCODE--;
				}
				else
				{
					if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
					GUI_SHOW_CHAR_24X12(x,y,HGB);
					x+=12;
					if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
					GUI_SHOW_CHAR_24X12(x,y,LGB);
					x+=12;
				}
			}
			else//第一个是ASCII,第二个是下一个gb2312的第一个字节
			{
				if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
				GUI_SHOW_CHAR_24X12(x,y,HGB);
				x+=12;
				GBCODE--;
			}
		}
		else
		{
			if(x+24>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
			HGB-=0xA0;
			LGB-=0XA0;
			offset=(94*(HGB-1)+(LGB-1))*72;
			W25QXX_Read(CodeBuff,offset+GB2312_24X24+FONT,72);
			GUI_SHOW_ONE_HANZI_24X24(x,y,CodeBuff);
			x+=24;
		}
	}
}
//////////////////////////////////////////////
void GUI_SHOW_STR(u8 size,u16 x,u16 y,u32 FONT,u8 *STR)
{
	switch(size)
	{
		case 12:GUI_SHOW_STR_12X12(x,y,FONT,STR);break;
		case 16:GUI_SHOW_STR_16X16(x,y,FONT,STR);break;
		case 24:GUI_SHOW_STR_24X24(x,y,FONT,STR);break;
		default:return;
	}
}
//////////////////////////////////////////////
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
void GUI_SHOW_NUM(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;		
	u16 x0=x;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
					switch(size)
					{
						case 12:if(x+6>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
										GUI_SHOW_CHAR_12X6(x,y,'0');
										x+=6;break;
						case 16:if(x+8>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
										GUI_SHOW_CHAR_16X8(x,y,'0');
										x+=8;break;
						case 24:if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
										GUI_SHOW_CHAR_24X12(x,y,'0');
										x+=12;break;
						default:return;
					}
				continue;
			}else enshow=1; 
		 	 
		}
	 					switch(size)
					{
						case 12:if(x+6>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=18;}
										GUI_SHOW_CHAR_12X6(x,y,temp+'0');
										x+=6;break;
						case 16:if(x+8>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=22;}
										GUI_SHOW_CHAR_16X8(x,y,temp+'0');
										x+=8;break;
						case 24:if(x+12>=LCD_CONFIG.LCD_WIDTH){x=x0;y+=30;}
										GUI_SHOW_CHAR_24X12(x,y,temp+'0');
										x+=12;break;
						default:return;
					}
	}
} 
//////////////////////////////////////////////
//填充
void GUI_DRAW_FILL(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		LCD_SetCursor(sx,i);      				//设置光标位置 
		LCD_WriteRAM_Prepare();     			//开始写入GRAM	  
		for(j=0;j<xlen;j++){LCD->LCD_RAM=color;}	//显示颜色 	
	}
}

//////////////////////////////////////////////
//画线
void GUI_DRAW_LINE(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1;
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1;
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++)
	{  
		LCD_DrawPoint(uRow,uCol);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//////////////////////////////////////////////
//画矩形
void GUI_DRAW_RECTANGLE(u16 x1, u16 y1, u16 x2, u16 y2)
{
	GUI_DRAW_LINE(x1,y1,x2,y1);
	GUI_DRAW_LINE(x1,y1,x1,y2);
	GUI_DRAW_LINE(x1,y2,x2,y2);
	GUI_DRAW_LINE(x2,y1,x2,y2);
}
//////////////////////////////////////////////
//画圆
void GUI_DRAW_CIRCLE(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);
 		LCD_DrawPoint(x0+b,y0-a);
		LCD_DrawPoint(x0+b,y0+a);
		LCD_DrawPoint(x0+a,y0+b);
		LCD_DrawPoint(x0-a,y0+b);
 		LCD_DrawPoint(x0-b,y0+a);
		LCD_DrawPoint(x0-a,y0-b);
  	LCD_DrawPoint(x0-b,y0-a);
		a++;    
		if(di<0)di+=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}         
} 		
//////////////////////////////////////////////
/**************基本GUI结束*******************/
//////////////////////////////////////////////
//////////////////////////////////////////////
