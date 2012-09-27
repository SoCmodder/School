#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar outgoing, incoming;
bit gone, send;

xdata uchar FrameBuffer[384] _at_ 0xFE00;

/* This function lasts approximately x ms */
void msec (uint x)
{
  uchar i;

  while (x-- > 0)
  {
    for (i=14; i; --i) {;}
  }
}

/* This interrupt is triggered when a byte has been sent or recieved */
void serint (void) interrupt 4 using 1
{
  static uchar j=0;

  if (RI)
  {
    incoming = SBUF;
    FrameBuffer[j] = incoming;
    P1 = (incoming | 0x80);
    RI = 0;
    j = (j == 9) ? 0 : (j+1);
  }
  else if (TI && send)
  {
    SBUF = outgoing;
    TI =0;
    gone = 1;
  }
}
void main(void)
{
  uchar i, j;
  uchar omsg[10] = {'C', 'P', 'E', ' ', '2', '1', '4', 'L', 'A', 'B'};

  /* 10416 baud with 12mhz clock */
  PCON = 0;
  IP = 0;
  TMOD = 0x20;
  TH1 = 0xFD;
  TCON = 0x40;
  SCON = 0x50;
  IE = 0x90;

  outgoing = omsg[0];

  gone = 0;

  /* Clear framebuffer */
  for (i = 0; i < 15; ++i)
  {
    for (j =0; j < 8; ++j)
    {
      FrameBuffer[j*32+i] = 26;
    }
  }
  i = j = 0;
  /* Trigger first send */
  send = 1;
  TI = 1;

  while (1)
  {
    if (gone)
    {
      i = (i == 9) ? 0 : (i+1);
      outgoing = omsg[i];
      gone = 0;

      /* Wait for 5 seconds between messages without sending */
      if (i == 0)
      {
        send = 0;
        msec(5000);
        send = 1;
        TI = 1;
      }
    }
  }
}   
