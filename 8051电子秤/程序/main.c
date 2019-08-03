#include<reg51.h>
#include <stdio.h>
#include<string.h>
#define uchar unsigned char 
#define uint unsigned int
void Initialize_LCD();	 //LCD��ʼ������
void DelayMS(uint ms);	 //��ʱ����
void ShowString(uchar,uchar,uchar *); //�ַ�����ʾ����
sbit CLK=P1^3;		//ʱ���ź�
sbit ST=P1^2;		//�����ź�
sbit EOC=P1^1;		//ת�������ź�
sbit OE=P1^0;		//���ʹ��
sbit SPK=P2^3;		//������
sbit QP=P1^4;		//ȥƤ��

uchar  Prompt[16];
//��ʾ���壨2�У�
uchar Disp_Buffer[32];

//������
void main()
{
	double zong=0;
	double Count=0;
	double pi=0x00;
	double jing=0;
	//��ʱ����ʼ��
	TMOD=0x02;		//T1����ģʽ2
	TH0=0x14;		//�趨��ʱ����ֵ
	TL0=0x00;
	IE=0x82;		//�������ȼ�
	TR0=1;			//���ó�����ʽ
	//��ʼ��LCD
	Initialize_LCD();		 

	while(1)
	{
		SPK=0;
		OE=0;
		ST=0;ST=1;ST=0;		//����A/Dת��
		while(EOC==0);		//�ȴ�ת�����
		OE=1;		
		if(QP==0)
		{	
			pi=P3;								//����Ƥ������
		}
		zong=P3;								//����������
		jing=zong-pi;							//ȥƤ����
		if(zong>=255)
		{	
			sprintf(Prompt,"----warnning----");	//������ʾ����
			SPK=1;
		}
		else
		sprintf(Prompt,"Quality:%3.1f kg",(jing-2)/59);   //��ʾ����
		ShowString(0,0,Prompt);
		ShowString(0,1,Prompt+16);
	}
}
//T0��ʱ���жϸ�ADC0808�ṩʱ���ź�
void Timer0_INT() interrupt 1
{
	TH0=0x14;		
	TL0=0x00;
	CLK=~CLK;
}

