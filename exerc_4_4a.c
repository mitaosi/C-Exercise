/* ====================================

File name: exerc_4_4a.c
Date: 2018-02-15

Group Number:  #07

Members of students contributed:

Shengzhi Qiu

Demonstration code: [<Examen code> <24916>]       Note that this is  Important , No code no bonus  !

====================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  unsigned char bit7;
  unsigned char val;

  srand(time(0));

  while (1) {
    inport = random_inport();
    bit7 = (inport & 0x80) ? 1 : 0; /* to judge bit7 being 0 or 1 */
    if (!bit7) {
      val = inport & 0x0f; /* when pressed, get the lower 4 bits*/
      printf("%X\n",val); /* print out the lower 4 bits*/
    }
    f_delay(5); /* delay 0.5 sec */
  }
  return 0;
}