#include<reg51.h>
#include <stdio.h>
#include<string.h>
#define uchar unsigned char 
#define uint unsigned int
void Initialize_LCD();	 //LCD初始化函数
void DelayMS(uint ms);	 //延时函数
void ShowString(uchar,uchar,uchar *); //字符串显示函数
sbit CLK=P3^3;		//时钟信号
sbit TC=P1^0;
sbit LED=P2^3;
uchar  Prompt[16];
//显示缓冲（2行）
uchar Disp_Buffer[32];

//主程序
void main()
{
	double x=0;
	double y=0;
	double m=0;
	uint Count=0;
	//定时器初始化
	TMOD=0x02;		
	TH0=0x14;		
	TL0=0x00;
	EA=1;
	ET0=0;		
	TR0=1;	
	LED=0;		
	Initialize_LCD();		 //初始化LCD
	while(1)
	{
		TC=1;
		if(TC==0)
		{	
			sprintf(Prompt,"----warning---------------");	//显示错误
			ET0=1; LED=1;
		}
		else 
		{
			sprintf(Prompt,"----no problem---------------",y);
			ET0=0;  LED=0;
		}
		   
		ShowString(0,0,Prompt);
		ShowString(0,1,Prompt+16);
	}
}
//T0定时器中断给蜂鸣器提供时钟信号
void Timer0_INT() interrupt 1
{
	TH0=0x01;		
	TL0=0x00;
	CLK=~CLK;
}

