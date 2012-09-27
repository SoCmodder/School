/********************************************************/
/*              Define Function Prototypes              */
/********************************************************/
unsigned int get_seed( void );
void initial( void );
char input( void );
void output( char state );
void delay( unsigned int t_delay );
void displ( char state, char button );
void press( char button );
void win( void );
void beep( char mode );
void clk( void );

#define uchar unsigned char
#define INPUT_MASK 0x0F
#define OUTPUT_MASK 0xF0
#define PORT P0
#define N_MILLI 1000
#define FLASH_MAX 4
#define SPEAKER
#define TONE_L 15


/********************************************************/
/*                   Define Macros                      */
/********************************************************/
#define read() ( ~PORT & INPUT_MASK )
#define led_read() ( ~PORT & OUTPUT_MASK ) >> 4


