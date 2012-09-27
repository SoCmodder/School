#include <reg51.h>

sbit SQRWV=P1^0;
bit sigcur, sigprev;

void main(void) {


SQRWV=1;
sigcur=SQRWV;
do { sigprev=sigcur; sigcur=SQRWV;}
	while (!(~sigprev&sigcur));


/*SQRWV=1;
sigcur=SQRWV;
do { sigprev=sigcur; sigcur=SQRWV;}
	while (~sigcur || sigprev );
*/
while(1);


/*SQRWV=1;
sigcur=SQRWV;
sigprev=sigcur;
sigcur=SQRWV;
while(!(~sigprev&sigcur))
{
	sigprev=sigcur;
	sigcur=SQRWV;
}*/

/*char temp1, temp2,temp3, temp4, temp5;
temp1 = (-512)>>8;
temp2 = -(512>>8);
temp3 = 512;
temp4 = -512;
temp5 = 0>>8;

while(1);*/

}

