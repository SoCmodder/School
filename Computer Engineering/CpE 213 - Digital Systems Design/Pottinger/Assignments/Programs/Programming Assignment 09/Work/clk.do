/* toggle T2 every 20 instr cycles */
signal void clk(){
 while(1){
   twatch(10);
   P3.5=~P3.5;
 }
}
