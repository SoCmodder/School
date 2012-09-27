/* define toolbox button for 87c752 ADC function */

define button "ADC", "adc()"

/* define analog inputs (there are 5 channels) */
DEFINE float adin0
adin0 = 0
DEFINE float adin1
adin1 = 0
DEFINE float adin2
adin2 = 0
DEFINE float adin3
adin3 = 0
DEFINE float adin4
adin4 = 0

/* this signal isn't perfect since I've included a 20 cycle  */
/* wait in the start test loop. At least it avoids having to */
/* manually set ADCI and clear ADCS.  ADAT should be set     */
/* manually with the command adat=xxx */
/* can let dscope free-run the program while changing adat.  */

signal void adc (void) {
 int temp;

 while(1){
  while ((ADCON & 0x28)!= 0x28) {twatch(20);}; /* wait until started */
  twatch(40); /* ADC takes 40 cycles to complete */

  /* write appropriate output */
  switch (ADCON & 0x03){
    case 0:
      ADAT = (adin0/5 * 1023);
      break;
    case 1:
      ADAT = (adin1/5 * 1023);
      break;
    case 2:
      ADAT = (adin2/5 * 1023);
      break;
    case 3:
      ADAT = (adin3/5 * 1023);
      break;
    case 4:
      ADAT = (adin4/5 * 1023);
      break;
    default:
      ADAT = 0x0000;
      break;
  }

  /* make sure within appropriate bounds */
  if ((ADAT>1023)||(ADAT<0)){
    ADAT = 0x00;
  }
  
  /* notify of completion */
  ADCON=  (ADCON & 0xf7 ) | 0x10; /* clear adcs, set adci */
 }
}


