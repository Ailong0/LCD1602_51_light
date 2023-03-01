

#include "regX52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include <intrins.h>		//��ΪҪ�õ������ƺ��������Լ������ͷ�ļ�
#include "LCD1602.h"
#include "menu.h"
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

#define led P2_1	   // �͵�ƽ����
#define microphone P1_0    //Ĭ�ϸߵ�ƽ �͵�ƽ��Ч
#define hcsr501 P1_1  //Ĭ�ϸߵ�ƽ �͵�ƽ��Ч
u16 min_duty =  10;
u16 max_duty = 100;
u16 current_duty = 0;
u8 light_flag =0;
u16 duration = 10000;


void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������

	TH0=0Xff;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
}
void Timer1Init()
{
	TMOD|=0X10;//ѡ��Ϊ��ʱ��1ģʽ��������ʽ1������TR1��������

	TH1=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL1=0X18;	
	ET1=1;//�򿪶�ʱ��1�ж�����
	EA=1;//�����ж�
	TR1=1;//�򿪶�ʱ��			
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
	TH0=0Xff;	//����ʱ������ֵ����ʱ1ms
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
	TH1=0XFC;	//����ʱ������ֵ����ʱ1ms
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
