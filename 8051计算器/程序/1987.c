#include<reg52.h>
#include"1987.h"
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit wd=P3^7;
uchar wdtable[10];
void delay(uint z)
{
   while(z--);
}
void init1820()
{
 uchar i=250;
  wd=1;   _nop_();_nop_();_nop_();
  wd=0;   delay(80);
  wd=1;   delay(1);
  while((i--)&&wd);
  delay(20);
  wd=1;
  _nop_();_nop_();
}
void write1820(uchar date)
{
 uchar i,bz;
 for(i=0;i<8;i++)
 {
   wd=0;    _nop_();_nop_();_nop_();_nop_();
   bz=date&0x01;
   wd=bz;
   delay(3);
   wd=1;
   _nop_();_nop_();
   date=date>>1;
 
 }
}
uchar read1820()
{
 uchar i,rwd=0;
 for(i=0;i<8;i++)
 {
  wd=0;     	_nop_();  _nop_();_nop_();
   rwd=rwd>>1;  
  wd=1;    	    _nop_();_nop_();
  if(wd==1)  rwd=rwd|0x80;
  delay(2);
    
}
 return rwd;
}  

void gettemp()
 {
  uchar i;
  init1820();
  write1820(0xcc);
  write1820(0xbe);
  for(i=0;i<9;i++)
  {
  	wdtable[i]=read1820();
  }
} 		
uint wendu()
{
 uchar temp1,temp2,temp,x;
 uint y;
  init1820();
  write1820(0xcc);
  write1820(0x44);
 gettemp();
 temp1=wdtable[1]<<4;
 temp1+=(wdtable[0]&0xf0)>>4;

 temp2= wdtable[0]&0x0f;
 temp=((wdtable[1]*256+ wdtable[0])>>4)  ;

  x=temp2*0.0625*10;
  y=temp*10+(x%10);
}	