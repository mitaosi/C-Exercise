#include <stdio.h>
#define REG(x) *((unsigned char *)(x))
#define OUTPORT 0x09C0
#define INPORT 0x09C1

unsigned int getRange(unsigned int val){
	int mappedValue;
	mappedValue=0;
	while(!(val%2)){
		
		val=(val>>1)&127;
		mappedValue++;
	}
	return mappedValue;
}


int main(){
	unsigned int cols=0x001;
	while(1){	
		int i;
		unsigned int in;
		for(i=0;i<8;i++){
			for(i=0;i<100;i++){}
			REG(OUTPORT)=(cols=(cols << 1)%15);
		
			in=REG(INPORT);
			//Key is numbered as top row from left 0 , 1 , 2 , 3 , 4 and next row 5 , 6 , 7 , 8 etc
			if(in!=255) printf("key pressed %x\n",((getRange(~in)-3)*-1)|(getRange(cols)<<2));
		}
		//skip every iteraion where i is odd
		i++;
	}
return 0;
}
