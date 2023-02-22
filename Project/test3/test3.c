#include <reg51.h>
void main() {
	P0=0x00;
	P2=0xff;
	while(1) {
			P0=P2; 
	}
}