#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
 
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit dula=P2^6;
sbit wela=P2^7;
 
uint miao=0;		
uint fen=0;			
uint shi=0;		    
uint n=0;			
uint date[6]={0,0,0,0,0,0};	  
void delay(uint z)			 
{
     uint x,y;
	 for(x=z;x>0;x--)
	  for(y=50;y>0;y--);
}
 
void write_address(uchar address)		 
{
    wela=1;
	P0=address;
	wela=0;
}
 
void write_date(uint n)				     
{
     dula=1;
	 P0=table[n];
	 dula=0;
}										
void display()
{	 	 
       write_date(date[0]);
      P0=0xff;
      write_address(0x7f);
       delay(1);
 
 
     write_date(date[1]);
	 P0=0xff;
	 write_address(0xbf);
	 delay(1);
 
	 write_date(date[2]);
	 P0=0xff;
	 write_address(0xef);
	 delay(1);
	 
 
	 write_date(date[3]);
	 P0=0xff;
	 write_address(0xf7);
	 delay(1);
 
	 write_date(date[4]);
	 P0=0xff;
	 write_address(0xfd);
	 delay(1);
 
 
	 write_date(date[5]);
	 P0=0xff;
	 write_address(0xfe);
	 delay(1);
 
	 
}
void time_init()						   
{
    TMOD=0x02;							  
	TH0=156;							 
	TL0=156;							
	EA=1;								 
	ET0=1;								 
	TR0=1;								 
}
 
void main()
{
   dula=0;								   
   wela=0;
   time_init();
   while(1)
   {
       display();
   }
 
    
}
 
 
 
void timer() interrupt 1					  
{
     n++;
	 if(n==10000)								 
	 {	 
	     n=0;
	     miao++;
		 if(miao==60)
		 {
		     miao=0;
		     fen++;
			 if(fen==60)
			 {
			     fen=0;
				 shi++;
				 if(shi==24)
				 {
				    shi=0;
				 }
			 }
		 }
		 date[0]=miao%10;
		 date[1]=miao/10;
		 date[2]=fen%10;
		 date[3]=fen/10;
		 date[4]=shi%10;
		 date[5]=shi/10;
	
	 }
 
	  
}