/* ====================================

File name: Exerc_6_3.c 

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */


#include <stdio.h>

#define ML13_statCtrl 0xB00
#define read_control *((char *)ML13_statCtrl)
#define set_control(x) *((char *)ML13_statCtrl)=x
int main(){
	
	while(1){
		if( read_control & 0x1 ||  read_control & 0x2){
			set_control(0x1);
		}else{
			if(read_control & 0x8){
				int i;
				for(i=0;i<300;i++){}
				set_control(0x2);
			}
		}
	}

return 0;
}

