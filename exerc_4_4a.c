#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printport(int portvalue){
  int binchar[8], rest,j, i=0;
  rest = portvalue;
  while(rest!=0){
    binchar[i++]= rest % 2;
    rest = rest / 2;
  }
  // Fill to 8 bits
  while( i<8){
    binchar[i++]=0;
  }
  // Print bits and at the end corresponding decimal value
  for(j =i-1 ;j > -1;j--)
    printf("  %d",binchar[j]);
  printf(" --------Porten value = %d  \n", portvalue);
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
  unsigned char bit7;
  unsigned char val;

  srand(time(0));

  while (1) {
    inport = random_inport();
    bit7 = (inport & 0x80) ? 1 : 0; /* 判断第7位是0还是1 */
    if (!bit7) {
      val = inport & 0x0f; /* 有按键按下,获取低4位 */
      printf("%X\n",val); /* 打印低4位 */
    }
    f_delay(5); /* 延迟0.5秒 */
  }
  return 0;
}