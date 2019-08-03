//LCD1602.c
#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
//延时
void DelayMS(uint ms)
{
	uchar i;
	while(ms--) for(i=0;i<120;i++);
}
//忙检查
uchar Busy_Check()
{
	uchar LCD_Status;
	RS=0;				//寄存器选择
	RW=1;				//读状态寄存器
	EN=1;				//开始读
	DelayMS(1);
	LCD_Status=P0;
	EN=0;
	return LCD_Status;
}		 
//写LCD命令
void Write_LCD_Command(uchar cmd)
{
	while((Busy_Check()&0x80)==0x80);	//忙等待
	RS=0;		//选择命令寄存器
	RW=0;		//写
	EN=0;	
	P0=cmd;EN=1;DelayMS(1);EN=0;
}
//发送数据
void Write_LCD_Data(uchar dat)
{
	while((Busy_Check()&0x80)==0x80);	//忙等待
	RS=1;RW=0;EN=0;P0=dat;EN=1;DelayMS(1);EN=0;
}
//LCD初始化
void Initialize_LCD()
{
	Write_LCD_Command(0x38);DelayMS(1);
	Write_LCD_Command(0x01);DelayMS(1);	//清屏
	Write_LCD_Command(0x06);DelayMS(1);	//字符进入模式：屏幕不动，字符后移
	Write_LCD_Command(0x0c);DelayMS(1);	//显示开，光标关
}
//显示字符串
void ShowString(uchar x,uchar y,uchar *str)
{
	uchar i=0;
	if(y==0) Write_LCD_Command(0x80|x);	//设置显示起始位置
	if(y==1) Write_LCD_Command(0xc0|x);
	for(i=0;i<16;i++)					//输出字符串
	{
		Write_LCD_Data(str[i]);
	}
}
