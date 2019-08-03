//LCD1602.c
#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
//��ʱ
void DelayMS(uint ms)
{
	uchar i;
	while(ms--) for(i=0;i<120;i++);
}
//æ���
uchar Busy_Check()
{
	uchar LCD_Status;
	RS=0;				//�Ĵ���ѡ��
	RW=1;				//��״̬�Ĵ���
	EN=1;				//��ʼ��
	DelayMS(1);
	LCD_Status=P0;
	EN=0;
	return LCD_Status;
}		 
//дLCD����
void Write_LCD_Command(uchar cmd)
{
	while((Busy_Check()&0x80)==0x80);	//æ�ȴ�
	RS=0;		//ѡ������Ĵ���
	RW=0;		//д
	EN=0;	
	P0=cmd;EN=1;DelayMS(1);EN=0;
}
//��������
void Write_LCD_Data(uchar dat)
{
	while((Busy_Check()&0x80)==0x80);	//æ�ȴ�
	RS=1;RW=0;EN=0;P0=dat;EN=1;DelayMS(1);EN=0;
}
//LCD��ʼ��
void Initialize_LCD()
{
	Write_LCD_Command(0x38);DelayMS(1);
	Write_LCD_Command(0x01);DelayMS(1);	//����
	Write_LCD_Command(0x06);DelayMS(1);	//�ַ�����ģʽ����Ļ�������ַ�����
	Write_LCD_Command(0x0c);DelayMS(1);	//��ʾ��������
}
//��ʾ�ַ���
void ShowString(uchar x,uchar y,uchar *str)
{
	uchar i=0;
	if(y==0) Write_LCD_Command(0x80|x);	//������ʾ��ʼλ��
	if(y==1) Write_LCD_Command(0xc0|x);
	for(i=0;i<16;i++)					//����ַ���
	{
		Write_LCD_Data(str[i]);
	}
}
