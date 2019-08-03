#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int

/*------------------------------LCD1602��Ҫ�����ĺ���------------------------------
void WR_data(uchar ,uchar *,uchar,uchar);	   //"()"������������ԣ�1����λ�ã�2��Ҫ��ʾ�����ݣ�3�������е�λ����4����ʾ���ݵĳ���
void intint();								   //LCD1602��ʼ��
void write_com(uchar);							   //��LCD1602дָ��
----------------------------------------------------------------------------------*/
sbit RS=P2^0;
sbit EN=P2^2;
sbit RW=P2^1; 

#define DATAQ P0
void delay(uint ms)
{
	uchar i;
	while(ms--) for(i=0;i<120;i++);
}
/*void busy_check()
{	
	P0=0xff;
	RS=0;
	RW=1;	
	delay(1);
	EN=1;
	while((P0&0x80)==0x80);
	EN=0;	
}*/
void write_com(uchar com)
{
//	busy_check();
	RS=0;
	RW=0;
	EN=0;
	DATAQ=com;
	delay(1);
	EN=1;
	delay(1);
	EN=0;
}

void write_date(uchar date)
{
//	busy_check();
	RS=1;
	RW=0;
	EN=0;
	DATAQ=date;
	delay(1);
	EN=1;
	delay(1);
	EN=0;
}
void intint()
{
	write_com(0x3c);delay(1);
	write_com(0x01);delay(1);
	write_com(0x02);delay(1);
	write_com(0x06);delay(1);
	write_com(0x0c);delay(1);	
}
void WR_data(uchar u,uchar *p,uchar set)
{
	uchar *i;
	write_com(0x0c);
	switch(u)
	{
		case 1:
				write_com(0x80+set);
				for(i=p;(*i)!='\0';i++)
				{
					write_date(*i);
				} break;
		case 2:
				write_com(0xc0+set);
				for(i=p;*i!='\0';i++)
				{
					write_date(*i);
				} break;
		default :break;
	}
	write_com(0x80|set);
	write_com(0x0f);
}
void WR_data_one(uchar u,uchar p,uchar set)
{
	write_com(0x0c);
	switch(u)
	{
		case 1:
				write_com(0x80+set);
				write_date(p);
				 break;
		case 2:
				write_com(0xc0+set);		
				write_date(p);
				 break;
		default :break;
	}
	write_com(0x80|set);
	write_com(0x0f);
}