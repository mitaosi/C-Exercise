#include <stdio.h>
#define PORT 0x09C0
#define REG(x) *((unsigned int *)(x))

int main(){
	while(1){
			int n;
			int in;
			for(n=0; n<100; n++){
			}
	
			in=REG(PORT);
	
			if(in/(16*16*16)==0){
			printf("key pressed %x\n",in/(16*16));
			}
		
		}

	return 0;
}
