#include<reg51.h>
void delay(int a)
{
while(a--);
}
main()
{
unsigned char i;
while(1)
{
P0=0x00;
for(i=0;i<8;i++){P0=(P0>>1)|0x80;delay(30000);}
}
}