#include<reg51.h>
#include <stdio.h>
#include<string.h>
#define uchar unsigned char 
#define uint unsigned int
void Initialize_LCD();	 //LCD��ʼ������
void DelayMS(uint ms);	 //��ʱ����
void ShowString(uchar,uchar,uchar *); //�ַ�����ʾ����
sbit CLK=P3^3;		//ʱ���ź�
sbit TC=P1^0;
sbit LED=P2^3;
uchar  Prompt[16];
//��ʾ���壨2�У�
uchar Disp_Buffer[32];

//������
void main()
{
	double x=0;
	double y=0;
	double m=0;
	uint Count=0;
	//��ʱ����ʼ��
	TMOD=0x02;		
	TH0=0x14;		
	TL0=0x00;
	EA=1;
	ET0=0;		
	TR0=1;	
	LED=0;		
	Initialize_LCD();		 //��ʼ��LCD
	while(1)
	{
		TC=1;
		if(TC==0)
		{	
			sprintf(Prompt,"----warning---------------");	//��ʾ����
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
//T0��ʱ���жϸ��������ṩʱ���ź�
void Timer0_INT() interrupt 1
{
	TH0=0x01;		
	TL0=0x00;
	CLK=~CLK;
}

