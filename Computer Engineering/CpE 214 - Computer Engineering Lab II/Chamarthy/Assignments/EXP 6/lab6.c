/* lab6.c
 *
 * Scroll a message across the screen
 */

#define uchar unsigned char
#define uint unsigned int
#define MSGLEN 6

/* DISPLAY macro puts a byte at the specified row and column
 */
#define DISPLAY(r,c,b) FrameBuffer[r*32+c] = b

xdata uchar FrameBuffer[384] _at_ 0xFE00;

void main(void)
{
	uchar i, j, msgpos;
	uint delay;
	uchar msg[MSGLEN] = {7, 4, 11, 11, 14, 26}; /* HELLO  */
	
	/* Clear screen */
	for (j = 0; j < 8; ++j)
		for (i = 0; i < 16; ++i)
			DISPLAY(j,i,26);
	
	/* Scroll message across first line of screen */
	msgpos = 0;
	while (1)
	{
		j = msgpos;
		/* repeat message across the first line */
		for (i = 0; i < 16; ++i)
		{
			DISPLAY(0,i,msg[j]);
			++j;
			if (j == MSGLEN) j = 0;
		}
		
		/* delay lasts about 1 second on my compiler */
		for (delay = 0; delay < 33000; ++delay);

		/* increment message position, or start over */
		++msgpos;
		if (msgpos == MSGLEN) msgpos = 0;
	}
}
