//main.c
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
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
                    主程序
------------------------------------------------*/
main()
{
 unsigned char num,i,sign;                  
 unsigned char temp[16];        //最大输入16个
 bit firstflag;
 float a=0,b=0;
 unsigned char s;

  TMOD=0x01;
  TH0=(65536-50000)/256;
  TL0=(65536-50000)%256;
  TR0=1;
  IE=0x8F;
 
 LCD_Init();         //初始化液晶屏
 DelayMs(10);        //延时用于稳定，可以去掉
 LCD_Clear();        //清屏
 LCD_Write_String(0,0,"welcome calculator");    //写入第一行信息，主循环中不再更改此信息，所以在while之前写入
 for(s=0;s<25;s++)//延时5s
  {  DelayMs(200);  
  } 
 LCD_Clear();
while (1)         //主循环
  {
	num=KeyPro();  //扫描键盘
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
 if(num!=0xff)  //如果扫描是按键有效值则进行处理
   { 
    if(i==0)    //输入是第一个字符的时候需要把改行清空，方便观看
	  LCD_Clear();

	if(('+'==num)|| (i==16) || ('-'==num) || ('x'==num)|| ('/'==num) || ('='==num))//输入数字最大值16，输入符号表示输入结束
	  {
	  i=0;  //计数器复位

	 if(firstflag==0)  //如果是输入的第一个数据，赋值给a，并把标志位置1，到下一个数据输入时可以跳转赋值给b
	     {
	     sscanf(temp,"%f",&a);
         firstflag=1;
		 }
	  else  
	     sscanf(temp,"%f",&b);
	  for(s=0;s<16;s++) //赋值完成后把缓冲区清零，防止下次输入影响结果
		    temp[s]=0;
      LCD_Write_Char(0,1,num); 
	  ///////////////////////
	  if(num!='=')      //判断当前符号位并做相应处理
	     sign=num;      //如果不是等号记下标志位
	  else
	     {  
		 firstflag=0;   //检测到输入=号，判断上次读入的符合
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
		 sprintf(temp,"%g",a);    //输出浮点型，无用的0不输出
         LCD_Write_String(1,1,temp);//显示到液晶屏
		 sign=0;a=b=0;            //用完后所有数据清零
		 for(s=0;s<16;s++)
		    temp[s]=0;
		 }
	  }

  else	if(i<16)
	  {
	   if((1==i)&& (temp[0]=='0') )//如果第一个字符是0，判读第二个字符
	     {
		  if(num=='.')  //如果是小数点则正常输入，光标位置加1
		    {
		    temp[1]='.';
			LCD_Write_Char(1,0,num);//输出数据
			i++;
            }           //这里没有判断连续按小数点，如0.0.0 
		 else
		  {
		   temp[0]=num; //如果是1-9数字，说明0没有用，则直接替换第一位0
		   LCD_Write_Char(0,0,num);//输出数据
		   }
		 }
	   else
	     {
         temp[i]=num; 
         LCD_Write_Char(i,0,num);//输出数据
	     i++;   //输入数值累加
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
