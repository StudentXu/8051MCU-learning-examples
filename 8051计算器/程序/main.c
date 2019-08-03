//main.c
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<stdio.h>
#include"1987.h"
#include"1602.h"
#include"delay.h"
#include"keyboard.h"

#define uchar unsigned char
#define uint  unsigned int

 sbit KEY1=P2^0;
 sbit KEY2=P2^1;
 sbit KEY3=P2^2;

uchar flag=0,shi=06,fen=23,miao=24,nian=15,yue=4,ri=29;
uchar flag_Q=0,flag_QQ=0;
uint wendu_date;
 void xianshi(uchar date,uchar dizhi)
 {
 	 uchar dateshi=0,datege=0;

	 dateshi=date/10;
	 datege=date%10;
     LCD_Write_Com(dizhi) ;
     LCD_Write_Data(dateshi+'0') ;
	 LCD_Write_Com(dizhi+1) ;
     LCD_Write_Data(datege+'0') ;

 }
 void shijian()
 {
     uchar 	wendu_dateshi=0,wendu_datebai=0,wendu_datege=0;

	 wendu_date=wendu();
	 wendu_date=wendu();
	 wendu_date=wendu();
	 wendu_date=wendu();

	 wendu_datebai=wendu_date/100;
	 wendu_dateshi=wendu_date/10%10;
	 wendu_datege=wendu_date%10;;

 	 xianshi(20,0x80);
 	 xianshi(nian,0x82);

 	 LCD_Write_Com(0x84) ;
     LCD_Write_Data(':') ;

	 xianshi(yue,0x85);

 	 LCD_Write_Com(0x87) ;
     LCD_Write_Data(':') ;

     xianshi(ri,0x88);


	 xianshi(shi,0xC0);

 	 LCD_Write_Com(0xC2) ;
     LCD_Write_Data(':') ;

	 xianshi(fen,0xC3);

 	 LCD_Write_Com(0xC5) ;
     LCD_Write_Data(':') ;

     xianshi(miao,0xC6);


	  	 LCD_Write_Com(0xCa) ;
     LCD_Write_Data(wendu_datebai+'0') ;

	  	 LCD_Write_Com(0xCb) ;
     LCD_Write_Data(wendu_dateshi+'0') ;

	   	 LCD_Write_Com(0xCc) ;
     LCD_Write_Data('`') ;

	   	 LCD_Write_Com(0xCd) ;
     LCD_Write_Data('C') ;
}
/*------------------------------------------------
                    ������
------------------------------------------------*/
main()
{
 unsigned char num,i,sign;                  
 unsigned char temp[16];        //�������16��
 bit firstflag;
 float a=0,b=0;
 unsigned char s;

  TMOD=0x01;
  TH0=(65536-50000)/256;
  TL0=(65536-50000)%256;
  TR0=1;
  IE=0x8F;
 
 LCD_Init();         //��ʼ��Һ����
 DelayMs(10);        //��ʱ�����ȶ�������ȥ��
 LCD_Clear();        //����
 LCD_Write_String(0,0,"welcome calculator");    //д���һ����Ϣ����ѭ���в��ٸ��Ĵ���Ϣ��������while֮ǰд��
 for(s=0;s<25;s++)//��ʱ5s
  {  DelayMs(200);  
  } 
 LCD_Clear();
while (1)         //��ѭ��
  {
	num=KeyPro();  //ɨ�����
   if(KEY1==0)
   {
   	  DelayMs(10);
   	  if(KEY1==0)
	  {
	  	flag_Q++;
		while(KEY1==0);
	  }
   }  
   if(KEY2==0&&flag_Q%2==0)
   {
   	 DelayMs(10);
   	 if(KEY2==0)
	 {
	  flag_QQ++;
	  while(KEY2==0);	    
	 }
   }
   if(flag_QQ==1)  TR0=0;
   if(flag_QQ==7)  TR0=1;

      if(KEY3==0&&flag_Q%2==0)
   {
   	 DelayMs(10);
   	 if(KEY3==0)
	 {
      if(flag_QQ==1)   {miao++;if(miao==60)miao=0;}  
      if(flag_QQ==2)   {fen++; if(fen==60)fen=0;} 
      if(flag_QQ==3)   {shi++; if(shi==12)shi=0;} 
      if(flag_QQ==4)   {ri++;  if(ri==31)ri=0;}
      if(flag_QQ==5)   {yue++;  if(yue==12)yue=0;}
      if(flag_QQ==6)  { nian++;  if(nian==20)nian=0;}
	  while(KEY3==0);
	 }
   }
 if(flag_Q%2==0)shijian(); 

 if(flag_Q%2==1)
{	  
 if(num!=0xff)  //���ɨ���ǰ�����Чֵ����д���
   { 
    if(i==0)    //�����ǵ�һ���ַ���ʱ����Ҫ�Ѹ�����գ�����ۿ�
	  LCD_Clear();

	if(('+'==num)|| (i==16) || ('-'==num) || ('x'==num)|| ('/'==num) || ('='==num))//�����������ֵ16��������ű�ʾ�������
	  {
	  i=0;  //��������λ

	 if(firstflag==0)  //���������ĵ�һ�����ݣ���ֵ��a�����ѱ�־λ��1������һ����������ʱ������ת��ֵ��b
	     {
	     sscanf(temp,"%f",&a);
         firstflag=1;
		 }
	  else  
	     sscanf(temp,"%f",&b);
	  for(s=0;s<16;s++) //��ֵ��ɺ�ѻ��������㣬��ֹ�´�����Ӱ����
		    temp[s]=0;
      LCD_Write_Char(0,1,num); 
	  ///////////////////////
	  if(num!='=')      //�жϵ�ǰ����λ������Ӧ����
	     sign=num;      //������ǵȺż��±�־λ
	  else
	     {  
		 firstflag=0;   //��⵽����=�ţ��ж��ϴζ���ķ���
         switch(sign)
	       {
		    case '+':a=a+b;
			break;
			case '-':a=a-b;
			break;
			case 'x':a=a*b;
			break;
			case '/':a=a/b;
			break;
			default:break;
		   }
		 sprintf(temp,"%g",a);    //��������ͣ����õ�0�����
         LCD_Write_String(1,1,temp);//��ʾ��Һ����
		 sign=0;a=b=0;            //�����������������
		 for(s=0;s<16;s++)
		    temp[s]=0;
		 }
	  }

  else	if(i<16)
	  {
	   if((1==i)&& (temp[0]=='0') )//�����һ���ַ���0���ж��ڶ����ַ�
	     {
		  if(num=='.')  //�����С�������������룬���λ�ü�1
		    {
		    temp[1]='.';
			LCD_Write_Char(1,0,num);//�������
			i++;
            }           //����û���ж�������С���㣬��0.0.0 
		 else
		  {
		   temp[0]=num; //�����1-9���֣�˵��0û���ã���ֱ���滻��һλ0
		   LCD_Write_Char(0,0,num);//�������
		   }
		 }
	   else
	     {
         temp[i]=num; 
         LCD_Write_Char(i,0,num);//�������
	     i++;   //������ֵ�ۼ�
		 }
	   }
  
    }	
  }
}
}
  void tim0 ()	interrupt 1
  {
    flag++;
  	if(flag==20)
	{
	 miao++;
	 flag=0;
	}
	 if(miao==60)
	 {
	  fen++;
	  miao=0;
	  if(fen==60)
	  {
	  	 fen=0;
		 shi++;
	  
	  }
	 }
  
  
  
  }
