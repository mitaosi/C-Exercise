/* ====================================

File name: exerc_4_3a.c
Date: 2018-02-15

Group Number:  #07

Members of students contributed:

Shengzhi Qiu

Demonstration code: [<Examen code> <24373>]       Note that this is  Important , No code no bonus  !

====================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printport(int inport, unsigned char *outport){
  int binchar[8], rest,j, i=0;
  unsigned char bit4,bit7;


  bit4 = (inport & 0x08) ? 1:0; /* to judge it being 0 or 1 on bit4 */
  if (bit4) { /* if bit 4 is 1 */
    bit7 = (*outport & 0x80) ? 1 : 0; /* get the the bit7 from the last outport*/
    *outport <<= 1; /* left shift 1 bit */
    *outport |= bit7; /* store the bit7 to the bit1*/
  }

  rest = *outport;
  while(rest!=0){
    binchar[i++]= rest % 2;
    rest = rest / 2;
  }
  // Fill to 8 bits
  while( i<8){
    binchar[i++]=0;
  }
  printf("Inbit 4 is %d OUT",bit4);
  // Print bits and at the end corresponding decimal value
  for(j =i-1 ;j > -1;j--)
    printf("  %d",binchar[j]);
  printf(" -------- Port value %d  \n", *outport);
}


void f_delay( int tenth_sec){

  clock_t start_t, end_t;
  long int i;
  start_t = clock();
  do{
    for(i=0; i< 10000000; i++);
    end_t = clock();
  }while ((end_t - start_t) < (tenth_sec*CLOCKS_PER_SEC)/10);
  return;
}

unsigned char random_inport( void){
  unsigned char inport = 0;
  inport=  rand() % 256;
  return (inport);
}

int main() {
  unsigned char inport;
  unsigned char outport = 3; /* the initial value of outport is 3 */

  srand(time(0));

  printport(0,&outport);

  while (1) {
    f_delay(5);
    inport = random_inport(); /* get the value of inport randomly */
    printport(inport,&outport);
  }

  return 0;
}
