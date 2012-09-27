#include <reg51.h>

/*void main(void) {
unsigned char brc,c,i;
c=0x80;
for (i=8;i>0;i--) {
	brc=(brc<<1) + c%2;
	c=c>>1;
	};
	while(1){};
	}
*/

void main(void) {
unsigned char i;
ACC=0x80;
for(i=8;i>0;i--) {
	ACC=ACC<<1;
	B=ACC;
	ACC=ACC>>1;
	B=ACC;
};
	
	while(1){
	}
}

