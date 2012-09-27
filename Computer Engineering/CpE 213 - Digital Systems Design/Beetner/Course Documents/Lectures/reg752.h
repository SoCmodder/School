/* 
 * Register Declarations for 80752 Processor
 */

/*  BYTE Register  */
sfr P0   = 0x80;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TL   = 0x8A;
sfr RTL  = 0x8B;
sfr TH   = 0x8C;
sfr RTH  = 0x8D;
sfr P1   = 0x90;
sfr ICON = 0x98;
sfr IDAT = 0x99;
sfr IE   = 0xA8;
sfr P3   = 0xB0;
sfr PSW  = 0xD0;
sfr ICFG = 0xD8;
sfr ACC  = 0xE0;
sfr B    = 0xF0;
sfr ISTA = 0xF8;

/* Addition to the 751 part */

sfr16 ADAT = 0x84;
sfr ADCON= 0xA0;
sfr PWCM = 0x8E;
sfr PWENA= 0xFE;
sfr PWMP = 0x8F;
sbit ADCS = ADCON^3;
sbit ADCI = ADCON^4;
sbit ENADC = ADCON^5;


/*  ACC  */
sbit ACC7   = 0xE7;
sbit ACC6   = 0xE6;
sbit ACC5   = 0xE5;
sbit ACC4   = 0xE4;
sbit ACC3   = 0xE3;
sbit ACC2   = 0xE2;
sbit ACC1   = 0xE1;
sbit ACC0   = 0xE0;

/*  B  */
sbit B_7   = 0xF7;
sbit B_6   = 0xF6;
sbit B_5   = 0xF5;
sbit B_4   = 0xF4;
sbit B_3   = 0xF3;
sbit B_2   = 0xF2;
sbit B_1   = 0xF1;
sbit B_0   = 0xF0;

/* ICFG READ */
sbit SLAVEN = 0xDF;
sbit MSTRRQ = 0xDE;
sbit O      = 0xDD;
sbit TIRUN  = 0xDC;
sbit CT1    = 0xD9;
sbit CT0    = 0xD8;

/* ICFG WRITE */
sbit CLRTI  = 0xDD;

/* ICON READ */
sbit CONRDAT = 0x9F;
sbit ATN  = 0x9E;
sbit DRDY = 0x9D;
sbit ARL  = 0x9C;
sbit STR  = 0x9B;
sbit STP  = 0x9A;
sbit MSTR = 0x99;

/* ICON WRITE */
sbit CXA  = 0x9F;
sbit IDLE = 0x9E;
sbit CDR  = 0x9D;
sbit CARL = 0x9C;
sbit CSTR = 0x9B;
sbit CSTP = 0x9A;
sbit XSTR = 0x99;
sbit XSTP = 0x98;

/* IDAT READ */
sbit RDAT  = 0x99;

/* IDAT WRITE */
sbit XDAT  = 0x99;

/* ISTA */
sbit STAIDLE  = 0xFE;
sbit STAXDATA = 0xFD;
sbit XACTV    = 0xFC;
sbit MAKSTR   = 0xFB;
sbit MAKSTP   = 0xFA;
sbit STAXSTR  = 0xF9;
sbit STAXSTP  = 0xF8;

/*  IE   */
sbit EA   = 0xAF;
sbit EAD  = 0xAE;
sbit ETI  = 0xAD;

sbit ES   = 0xAC;
sbit EPWM = 0xAB;
sbit EX1  = 0xAA;
sbit ET0  = 0xA9;
sbit EX0  = 0xA8;

/*  P0   */
sbit PWMO = 0x84;
sbit SDA  = 0x81;
sbit SCL  = 0x80;

/*  P1   */
sbit TO    = 0x97;
sbit INT1  = 0x96;
sbit INT0  = 0x95;
sbit ADC4  = 0x94;
sbit ADC3  = 0x93;
sbit ADC2  = 0x92;
sbit ADC1  = 0x91;
sbit ADC0  = 0x90;

/*  P3  */
sbit B7   = 0xB7;
sbit B6   = 0xB6;
sbit B5   = 0xB5;
sbit B4   = 0xB4;
sbit B3   = 0xB3;
sbit B2   = 0xB2;
sbit B1   = 0xB1;
sbit B0   = 0xB0;

/*  PCON  */
sbit PD  = 0x89;
sbit IDL  = 0x88;

/*  PSW   */
sbit CY   = 0xD7;
sbit AC   = 0xD6;
sbit F0   = 0xD5;
sbit RS1  = 0xD4;
sbit RS0  = 0xD3;
sbit OV   = 0xD2;
sbit P    = 0xD0;

/*  TCON  */
sbit GATE = 0x8F;
sbit CT   = 0x8E;
sbit TF   = 0x8D;
sbit TR   = 0x8C;
sbit IE0  = 0x8B;
sbit IT0  = 0x8A;
sbit IE1  = 0x89;
sbit IT1  = 0x88;
