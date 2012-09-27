#include <reg51.h>
#include <stdlib.h>
#include <project.h>

/********************************************************/
/*               Setup Power Down Mode                  */
/********************************************************/
unsigned int timeout=0;	//Timeout counter global variable

void powdown( void ) interrupt 1 using 2
{
	timeout++;
	if( timeout == 2000 )
	{
		PORT=0xFF;
		PCON |= 0x02;
	}
}

/********************************************************/
/*                   Setup Speaker                      */
/********************************************************/
#ifdef SPEAKER

#define SPKR P1			//Port that speaker is on
#define SPKR_INIT 0xFF	//Turn off speaker	
#define SPKR_BIT 0x80	//Bit that speaker is on

/********************************************************/
/*                 Speaker Tone Periods                 */
/*														*/
/* Note   Frequency (Hz)    Period (us)   Period/2 (us) */
/* ----   --------------    -----------   ------------- */
/*  A         440.00           2273           1136      */
/*  B         493.88           2025           1012      */
/*  C#        554.37           1804            902      */
/*  D         587.33           1703            851      */
/********************************************************/

#define PER_01 1136
#define PER_02 1012
#define PER_04 902
#define PER_08 851

uchar spkr_out = SPKR_INIT;	//Speaker state global variable

//Period Table for button pressed
int period[] = { 0, PER_01, PER_02, 0, PER_04, 0, 0, 0, PER_08, 0 , 0, 0, 0, 0, 0, 0 };

int *p_per;	//Pointer for table access

#endif

/********************************************************/
/*                  Define Functions                    */
/********************************************************/

/********************************************************/
/*                Get_Seed Function                     */
/*                                                      */
/* INPUT:  NONE                                         */
/* OUTPUT: int value of states before button pressed    */
/*                                                      */
/* The get_seed function takes no arguments and counts  */
/* cycles until a button is pressed to begin the game.  */
/* The function returns this integer value for use with */
/* the srand seed function to enable random light order.*/
/********************************************************/
unsigned int get_seed( void )
{
	unsigned int i=1,j=1,k=1;
	char new, old = 0x00, val = 0x00, val2;

	output(0);
	new = read();

	while( val == old )
	{
		val = (old^new)&new;
		new = read();
		i++;

		if( i%8000==0 )
		{
			k++;
			if( k%8==0 )
			{
			output(j);
			j=j<<1;
			if(j==0x10)
				j=1;
			}
		}

		if( i==0xFFFE )
			i=1;
	}

	val2=val;

	while(val2 == new)
	{
		val = (old^new)&new;
		new = read();
	}

	return i;
}


/********************************************************/
/*                 Initial Function                     */
/*                                                      */
/* INPUT:  NONE                                         */
/* OUTPUT: char value of the initial state of lights    */
/*                                                      */
/* The initial function takes no arguments and returns  */
/* a random initial state for the lights.               */
/********************************************************/
void initial( void )
{
	char i_state;
	
	srand( get_seed() );

	i_state=1+rand()%15;
	output( i_state );
}

/********************************************************/
/*                   Input Function                     */
/*                                                      */
/* INPUT:  NONE                                         */
/* OUTPUT: char value of the state of switches          */
/*                                                      */
/* The input function takes no arguments and returns    */
/* the current state of the switches when a button is   */
/* pressed.  A '1' indicates the switch was pressed; a  */
/* '0' indicates a switch is not pressed.               */
/********************************************************/
char input( void )
{
	char new, old = 0x00, val = 0x00, val2;

	new = read();

	while( val == old )
	{
		val = (old^new)&new;
		new = read();
	}
	
	val2=val;

	while(val2 == new)
	{
		val = (old^new)&new;
		new = read();
	}
	return val;
}

/********************************************************/
/*                   Output Function                    */
/*                                                      */
/* INPUT:  state - desired state for LED's              */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The output function takes a character state argument */
/* and outputs the low 4 bits to the output port.  A '1'*/
/* turns the LED on; a '0' turns the LED off.           */
/********************************************************/
void output( char state )
{
	PORT = ~( (state << 4) & 0xF0);
}


/********************************************************/
/*                    Delay Function                    */
/*                                                      */
/* INPUT:  t_delay-time of delay in milliseconds        */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The delay function takes an integer time argument in */
/* milliseconds.  The program then spins in a loop for  */
/* the indicated amount of time.                        */
/********************************************************/
void delay( unsigned int t_delay ) 
{
	unsigned int i;

	ET0=0;
	
	for(i=t_delay; i>0; i--)
	{
		TH0 = -N_MILLI>>8;
		TL0 = -N_MILLI&0xFF;
		TR0=1;
		while(!TF0);
		TF0=TR0=0;
	}

	ET0=1;
}


/********************************************************/
/*                    Displ Function                    */
/*                                                      */
/* INPUT:  state - state of lights to output            */
/*         button - switch pressed                      */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The displ function takes a character LED state       */
/* argument and a character button pressed argument.    */
/* The function outputs the state of the lights and     */
/* sounds the corresponding tone of the switch pressed  */
/********************************************************/
void displ( char state, char button )
{
	output( state );
	#ifdef SPEAKER
	beep( button );
	#endif
}


/********************************************************/
/*                    Press Function                    */
/*                                                      */
/* INPUT:  button - switch pressed                      */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The press function takes an character switch state   */
/* argument.  The function then inverts the light and   */
/* the lights that are horizontal and vertical to the   */
/* light pressed.                                       */
/********************************************************/
void press( char button )
{
	char new, old;
	old = led_read();

	TR0=0;
	ET0=0;
	timeout=0;

	switch( button )
	{
		case 0x01:
			new = (~old&0x07) | (old&0x08);
			break;	
		case 0x02:
			new = (~old&0x0B) | (old&0x04);
			break;
		case 0x04:
			new = (~old&0x0D) | (old&0x02);
			break;
		case 0x08:
			new = (~old&0x0E) | (old&0x01);
			break;
		default:
			new=old;
			break;
	}
	displ( new, button );
}

/********************************************************/
/*                    Win Function                      */
/*                                                      */
/* INPUT:  NONE                                         */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The press function takes a character switch state    */
/* argument.  The function then inverts the light and   */
/* the lights that are horizontal and vertical to the   */
/* light pressed.                                       */
/********************************************************/
void win( void )
{
	char i,j;
	for( i=0; i<FLASH_MAX; i++)
	{
		for(j=0; j<4; j++)
		{
			displ( 0x01 << j, 0x01<<j );
		}
	}
}


/********************************************************/
/*             Speaker Specific Functions               */
/********************************************************/

#ifdef SPEAKER

/********************************************************/
/*                    Beep Function                     */
/*                                                      */
/* INPUT:  mode - switch pressed to output tone for     */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The beep function takes a char mode argument that is */
/* the switch pressed to output the tone for.  The      */
/* function sets the global pointer with the index and  */
/* initializes Timer 1 with the associated period. The  */
/* tone is allowed to continue for time TONE_L          */
/********************************************************/
void beep( char mode )
{
	p_per = &period[mode];
	if( *p_per != 0 )
	{
		/* Enable timer */
		TH1=-(*p_per)>>8;
		TL1=-(*p_per)&0xFF;
		TR1=1;
		ET1=1;
	}

	delay(TONE_L);

	/* Disable timer */
	ET1=0;
	TR1=0;
	SPKR = SPKR_INIT;
}

/********************************************************/
/*                    Clk Function                      */
/*                                                      */
/* INPUT:  NONE                                         */
/* OUTPUT: NONE                                         */
/*                                                      */
/* The clk function is an interrupt service routine. It */
/* takes no arguments and returns nothing.  The function*/
/* sets up Timer 1 to create a square wave of frequency */
/* pointed to by the p_per pointer.                     */
/********************************************************/
void clk( void ) interrupt 3 using 1
{
	TH1 = -(*p_per)>>8;
	TL1 = -(*p_per)&0xFF;
	spkr_out = spkr_out^SPKR_BIT;
	SPKR = spkr_out;
}

#endif
