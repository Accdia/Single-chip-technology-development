#include<reg51.h>
#include<intrins.h>
unsigned char code seg[]={0xC0,0x99,0x80,0xc6,0xF9,0x92,0x90,0xA1,0xA4,0x82,0x88,0x86,0xB0,0xF8,0x83,0x8e};
unsigned char temp,i;
sbit k1=P1^0;
sbit k2=P1^1;
sbit k3=P1^2;
sbit k4=P1^3;

void delay(int a)
{
	while(a--);
}

void main()
{	
	while(1)
   {  
   	  P1=0xef;  
	  for(i=0;i<=3;i++)
	  {
	  	if(k1==0)
			P0=seg[i*4+0];
		if(k2==0)
			P0=seg[i*4+1];
		if(k3==0)	
			P0=seg[i*4+2];
		if(k4==0)
			P0=seg[i*4+3];
		delay(30);
		temp=P1;
		temp=temp<<1;
		temp=temp | 0x0f;  
		P1=temp;
   	   }
	} 
}	