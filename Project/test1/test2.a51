#include <reg52.h>
#include <intrins.h>

#define uint unsigned int

unsigned char LED;
void delay(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
      for(y=60;y>0;y--);
}
void main()
{
  LED=0xf0;
  P1=LED;
  delay(60);
  while(1)
  {
    LED=_cror_(LED,1);
	P1=LED;
	delay(60);
}
