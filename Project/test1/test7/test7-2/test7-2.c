#include<reg51.h>
#define uchar unsigned char
void main(void){
    TMOD=0x20;
    TH1=TL1=0xf4;
    PCON=0;
    SCON=0x50;
    EA=ES=TR1=1;
    while(1){ 
        while(RI==1){
            RI = 0;
            P1 = SBUF;
        }
    }
}

