#include <reg51.h>
#include <stdlib.h> 

/* Constants */ 

#define O_SANE 0x00
#define O_LOSE 0x0f
#define O_WIN 0x01
#define I_MASK 0x0f
#define N_FLASH 0x04
#define N_PAUSE 125
#define MAX_LEVELS 32
#define INIT_LEVELS 0x0f
#define MAX_DELAY 700
#define SPEAKER

#ifdef SPEAKER

#define SPKR P3
#define SPKR_INIT 0x7f
#define SPKR_BIT 0x80

/* Speaker tone periods */

#define PER_01 3000
#define PER_02 3434
#define PER_04 3931
#define PER_08 4500
#define PER_0f 5900

#endif

#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif


#define write(A) P2 = ~( ( (A) << 4 ) & 0xf0 )
#define read() ( (~P2) & I_MASK )

/* Function prototypes */
int get_seed( void );
char getval( void );
void displ( char );
char input( void );
void loose( void );
char win( char );
void delay( void );
void beep( char );

/* Global vars */
unsigned int delay_t = MAX_DELAY;
char trans[] = { 0 , 8 , 4 , 0 , 2 , 0 , 0 , 0 , 1 };

#ifdef SPEAKER

unsigned char spkr_out = SPKR_INIT;

int period[] = { 0 , PER_01 , PER_02 , 0 , PER_04, 0 , 0 , 0 ,PER_08, 0 , 0 , 0 , 0 , 0, 0 , PER_0f };

int *p_per;
char levels=0; 

/* Interrupt Handler for Real-Time Clock */

void clk( void ) interrupt 3 using 1

 {
 TH1=-(*p_per)>>8;
 TL1=-(*p_per)&0x0ff;
 spkr_out = spkr_out^SPKR_BIT;
 SPKR = spkr_out;
 }

#endif

/* Power down handler */
unsigned int timeout=0;

void pd( void ) interrupt 1 using 2


 {
 EA=0;
 timeout++;
 if(timeout == 833)

   {
   P2=0xFF;
   PCON |= 0x02;
   }

 TR0=1;
 EA=1;
 ET0=1;
 } 


void main( void )

 {
 char i,j;
 char value;
 char pat[MAX_LEVELS];


 EA=1; 
 TMOD |= 0x01;
 ET0=1;
 TH0=0x00;
 TL0=0x01;
 TR0=1;
 win(8);

while(1) 
   {


   restart:

   srand( get_seed() );

   for( i=0 ; i<levels ; i++ ) {

     timeout=0; 
     value = getval();
     pat[i] = value;
     displ(0); /* output nothing for a time */

     for( j=0 ; j<=i ; j++ ) {

       delay_t /= 2; /* shorten the delay time */
       displ(0); /* display a blank */
       delay_t = MAX_DELAY - i*40; /* shorten the delay 29 */

       if (delay_t <200)
          {
          delay_t=200;
          }

       displ( pat[j] );
       }

     for( j=0 ; j<=i ; j++ ) {

       if( input() != pat[j] ) {

       loose();
       levels = INIT_LEVELS;
       goto restart;
       }
      }
    }

 levels = win(levels);

   }
 }



int get_seed( void )

 {
 unsigned int i=1;
 char new, old = 0x00, val = 0x00;

 write( O_SANE );
 new = read();

 while( val == old ) {

   val = (old^new)&new;
   new = read();
   i++;

  if( i >= 0xfffe ) {
     i = 1;
     }

   }
   switch(new)
   {

   case 0x01: levels = 8; break;
   case 0x02: levels = 16; break;
   case 0x04: levels = 24; break;
   case 0x08: levels = 32; break;
   } 

 return i;
 }

char getval( void )

 {
 char val;
 val = (char)(1+(int)(4.0*rand()/(RAND_MAX+1.0)));

 /* Make the value a power of 2 */

 if( val == 3 ) {
   val = 8;
   }
 return val;
 }


char input( void )

 {
 char new, old = 0x00, val = 0x00;

 write( O_SANE );
 new = read();

 while( val == old ) {

   val = (old^new)&new;
   new = read();
   }

 val = trans[val];
 displ( val );
 return val;
 }


void displ( char val )

 {
 write( val );

 #ifdef SPEAKER
 beep( val );

 #else 
 delay();
 #endif

 write( O_SANE );
 }

void loose( void )

 {
 char i;
 delay_t = MAX_DELAY;

 for( i=0 ; i<N_FLASH ; i++ ) {

   displ( O_LOSE );
   }
 }


char win( char levels )

 {
 char i,j;
 delay_t = MAX_DELAY>>2;

 for( i=0 ; i<N_FLASH ; i++ ) {

   for( j=0 ; j<N_FLASH ; j++ ) {

     displ( O_WIN<<j );
     }
   }
 levels = (levels<<1)^levels;

 if ( levels == MAX_LEVELS ) {

   for( i=0 ; i<N_FLASH ; i++ ) {

     loose();
     (void) win( 0 );
     }
   levels = INIT_LEVELS;
   }

 delay_t = MAX_DELAY;
 return levels;
 }


void delay( void ) 

 {
 unsigned int time = delay_t;
 char i;

 while( time-- > 0 ) {
   for( i=0 ; i<N_PAUSE ; i++ ) ;
   }
}


#ifdef SPEAKER

void beep( char mode )

 {
 p_per = &period[mode];

 if( *p_per != 0 ) {

   /* Enable timer */

   TH1=-(*p_per)>>8;
   TL1=-(*p_per)&0x0ff;
   TR1=1;
   ET1=1;
   }

 delay();

 /* Disable timer */

 ET1=0;
 TR1=0;
 SPKR = SPKR_INIT;
 }

#endif

