/* ====================================

File name: exerc_6_3.c 

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */


#include <stdio.h>

#define ML13_Status   0xB00
#define ML13_Control  0xB00
#define read_control *((char *)ML13_Status)
#define set_control(x) *((char *)ML13_Control)=x
void main(){
	
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

}

