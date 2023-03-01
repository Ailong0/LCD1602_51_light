#ifndef __menu_h
#define __menu_h
#include "regx52.h"
#define back_key	  P3_0
#define enter_key  	P3_1
#define last_key   	P3_2
#define next_key	  P3_3

extern unsigned int min_duty;
extern unsigned int max_duty;
extern unsigned int duration;
void delay(unsigned int i);
void  Menu_key_set(void);
void fun0(void);
void fun1(void);
void fun2(void);
void fun3(void);
void fun4(void);
//void fun5(void);
//void fun6(void);
#endif

