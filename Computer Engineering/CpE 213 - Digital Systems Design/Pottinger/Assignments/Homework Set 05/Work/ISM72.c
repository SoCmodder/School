#include <reg51.h>

void f1(void){ P2=0x01; }
void f2(void){ P2=0x02; }
void f3(void){ P2=0x04; }

void main(void) {
	while(1) {
		switch (P1) {
			case 0: f1(); break;
			case 1: f2(); break;
			default: f3(); break;
		}
	}
}
