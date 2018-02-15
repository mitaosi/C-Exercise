#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printport(int inport, unsigned char *outport){
  int binchar[8], rest,j, i=0;
  unsigned char bit4,bit7;


  bit4 = (inport & 0x08) ? 1:0; /* 判断第4位是0还是1 */
  if (bit4) { /* 第4位是1 */
    bit7 = (*outport & 0x80) ? 1 : 0; /* 取得之前outport的第7位 */
    *outport <<= 1; /* 左移1位 */
    *outport |= bit7; /* 将第7位的值保存到第1位 */
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
  printf(" --------Porten value = %d  \n", *outport);
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
  unsigned char outport = 3; /* outport 的初始值是3 */

  srand(time(0));

  printport(0,&outport);

  while (1) {
    f_delay(5);
    inport = random_inport(); /* 随机获得inport的值 */
    printport(inport,&outport);
  }

  return 0;
}
