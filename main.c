

#include "regX52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include <intrins.h>		//因为要用到左右移函数，所以加入这个头文件
#include "LCD1602.h"
#include "menu.h"
typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

#define led P2_1	   // 低电平点亮
#define microphone P1_0    //默认高电平 低电平有效
#define hcsr501 P1_1  //默认高电平 低电平有效
u16 min_duty =  10;
u16 max_duty = 100;
u16 current_duty = 0;
u8 light_flag =0;
u16 duration = 10000;


void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0Xff;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}
void Timer1Init()
{
	TMOD|=0X10;//选择为定时器1模式，工作方式1，仅用TR1打开启动。

	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;	
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=1;//打开定时器			
}

void main()
{
	Timer0Init();
	Timer1Init();
	LCD_init();
	current_duty=min_duty;
	P2=0XFF;
	P1_1=1;
	while(1)
	{
		if (hcsr501==0||microphone==0)
		{
			light_flag=1;
			current_duty=max_duty;
		}
		Menu_key_set();

	}
	
}
void Timer0() interrupt 1
{
	static u16 i;
	TH0=0Xff;	//给定时器赋初值，定时1ms
	TL0=0X18;
	i++;
	if(i<current_duty)
	{
		led=0;
	}	
	else{
		led=1;
	}
	if(i==100) i=0;
}
void Timer1() interrupt 3
{
	static u16 i;
	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;
	if (light_flag)
	{
		i++;
		if (i%(duration/(max_duty-min_duty))==0)
		{
			current_duty=current_duty-1;
		}
		if(i==duration)
		{
			i=0;
			light_flag=0;
		}	
	}
}
