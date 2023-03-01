#include "LCD1602.h"
#include "menu.h"
#include "stdio.h"
static void (*current_operation_index)(void);
typedef struct
{
    unsigned char current;//��ǰ״̬������
    unsigned char next; //����һ��
		unsigned char last;//����һ��
    unsigned char enter; //ȷ��
		unsigned char back;	//����
    void (*current_operation)(void); //��ǰ״̬Ӧ��ִ�еĲ���
} Menu_table;

Menu_table  table[5]=
{
    {0,1,1,2,0,(*fun0)},//һ������  
    {1,0,0,3,1,(*fun1)},
		
    {2,2,2,2,0,(*fun2)},
		{3,4,4,3,4,(*fun3)},
		{4,3,3,3,0,(*fun4)},

};
void delay(unsigned int i)
{
	while(i--);	
}
unsigned char  func_index = 0;//�������ʱ���ڽ��������ֵ
void  Menu_key_set(void)
{
		if(next_key == 0)
		{   
			while(next_key==0);
			delay(10000);
			func_index=table[func_index].next;//����next���º��������
		}
	 if(last_key == 0)
		{
			while(last_key==0);
			delay(10000);
			func_index=table[func_index].last;
		}
		if(enter_key == 0)
		{
			LCD_clear();
			while(enter_key==0);
			func_index=table[func_index].enter;

		}
		if(back_key == 0)
		{
			LCD_clear();
			while(back_key==0);
			func_index=table[func_index].back;

		}
  current_operation_index=table[func_index].current_operation;//ִ�е�ǰ����������Ӧ�Ĺ��ܺ�����
  (*current_operation_index)();//ִ�е�ǰ��������
}
void fun0(void)
{
	LCD_disp_string(1,0,"->  set time");
	LCD_disp_string(2,0,"    set power");
}
void fun1()
{
	LCD_disp_string(1,0,"    set time");
	LCD_disp_string(2,0,"->  set power");
}
void fun2()
{
	unsigned char time_str[10]="";
		while(1){
	sprintf((char*)time_str,"time:%2ds",duration/1000);

	if (next_key==0)
	{while(next_key==0);
		duration=duration+1000;
	}
	if (last_key==0)
	{
		while(last_key==0);
		duration=duration-1000;
		if (duration==0)
		{
			duration==0;
		}	
	}
	if(back_key==0)
	{
		func_index=0;
		break;
	}
	LCD_disp_string(1,0,time_str);
}
}
void fun3()
{
	LCD_disp_string(1,0,"-> min:");
	LCD_disp_string(2,0,"   max:");
	while(1)
	{
		if (next_key==0)
		{
			while(next_key==0);
			min_duty=min_duty+5;
		}
		if (last_key==0)
		{
			while(last_key==0);
			min_duty=min_duty-5;
			if (min_duty==0)
			{
				min_duty==0;
			}	
			if(min_duty>=max_duty)
			{
				min_duty=max_duty;
			}
		}
		
		LCD_disp_number(1,7,min_duty,3);
		LCD_disp_number(2,7,max_duty,3);
		if(back_key==0) 
		{
			while(back_key==0);
			func_index=4;
			break;
		}
	}
}
void fun4()
{
	LCD_disp_string(1,0,"   min:");
	LCD_disp_string(2,0,"-> max:");
	while(1)
	{
		if (next_key==0)
		{
			while(next_key==0);
			max_duty=max_duty+5;
		}
		if (last_key==0)
		{
			while(last_key==0);
			max_duty=max_duty-5;
			if (max_duty==100)
			{
				max_duty==100;
			}	
			if(max_duty<=min_duty)
			{
				max_duty=min_duty;
			}
		}
		
		LCD_disp_number(1,7,min_duty,3);
		LCD_disp_number(2,7,max_duty,3);
		if(back_key==0)
		{		
			while(back_key==0);
			func_index=0;
			break;
		}
	}
}



