#include<reg51.h>
#include <stdio.h>
#include<string.h>
#define uchar unsigned char 
#define uint unsigned int
void Initialize_LCD();	 //LCD初始化函数
void DelayMS(uint ms);	 //延时函数
void ShowString(uchar,uchar,uchar *); //字符串显示函数
sbit CLK=P1^3;		//时钟信号
sbit ST=P1^2;		//启动信号
sbit EOC=P1^1;		//转换结束信号
sbit OE=P1^0;		//输出使能
sbit SPK=P2^3;		//蜂鸣器
sbit QP=P1^4;		//去皮键

uchar  Prompt[16];
//显示缓冲（2行）
uchar Disp_Buffer[32];

//主程序
void main()
{
	double zong=0;
	double Count=0;
	double pi=0x00;
	double jing=0;
	//定时器初始化
	TMOD=0x02;		//T1工作模式2
	TH0=0x14;		//设定定时器初值
	TL0=0x00;
	IE=0x82;		//设置优先级
	TR0=1;			//设置出发方式
	//初始化LCD
	Initialize_LCD();		 

	while(1)
	{
		SPK=0;
		OE=0;
		ST=0;ST=1;ST=0;		//启动A/D转换
		while(EOC==0);		//等待转换完成
		OE=1;		
		if(QP==0)
		{	
			pi=P3;								//记下皮的重量
		}
		zong=P3;								//记下总质量
		jing=zong-pi;							//去皮计算
		if(zong>=255)
		{	
			sprintf(Prompt,"----warnning----");	//超重显示错误
			SPK=1;
		}
		else
		sprintf(Prompt,"Quality:%3.1f kg",(jing-2)/59);   //显示重量
		ShowString(0,0,Prompt);
		ShowString(0,1,Prompt+16);
	}
}
//T0定时器中断给ADC0808提供时钟信号
void Timer0_INT() interrupt 1
{
	TH0=0x14;		
	TL0=0x00;
	CLK=~CLK;
}

