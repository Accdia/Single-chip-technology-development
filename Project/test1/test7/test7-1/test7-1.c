#include<reg51.h>
#define uchar unsigned char
char code map[]={0x7e,0x79,0x38,0x39,0x5c,0x37, 0x78,0x5c, 0x78,0x76,0x79, 0x37,0x39,0x3e, 0x7e,0x5c,0x31,0x38,0x5e};

void delay(unsigned int time){
    unsigned int j = 0;
    for(;time>0;time--)
    for(j=0;j<125;j++);
}
void main(void){
    int counter=0;
    TMOD=0x20;
    TH1 = TL1 = 0xf4;
    PCON=0;
    SCON = 0X50;
    EA=ES=TR1=1;
    while(1){
        SBUF = map[counter];
        while(TI==0);
        TI=0;
        if(++counter>18) counter=0;
        delay(1000);
    }
}