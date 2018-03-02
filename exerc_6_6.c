/* ====================================

File name: exerc_6_6.c

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */

#include <_rtk.h>

#define TIMESLICE 10

#define sem1 1
#define sem2 2
#define sem3 3
#define sem4 4
PROCESS P1(void);
PROCESS P2(void);
PROCESS P3(void);
PROCESS P4(void);
void AtInterrupt(void);
extern void _outchar(char);

void main(){
	InitKernel(TIMESLICE, AtInterrupt);
	initsem(sem1,1);
	initsem(sem2,0);
	initsem(sem3,0);
	initsem(sem4,0);
	if( CreateProcess("P1", P1) == -1){
		printl("\nCan't create process");
        }
	if( CreateProcess("P2", P2) == -1){
		printl("\nCan't create process");
                     
        }
	if( CreateProcess("P3", P3) == -1){
		printl("\nCan't create process");
        }
	if( CreateProcess("P4", P4) == -1){
		printl("\nCan't create process");
         }
	
        StartKernelForSim();
}
void AtInterrupt(){
	insert_last(Running, &ReadyQ); 
	Running= remque(&ReadyQ);
}
PROCESS P1(void){
	DO_FOREVER{
		waitsem(sem1);
		_outchar('1');
		signalsem(sem2);
		
	}
}
 
PROCESS P2(void){
	DO_FOREVER{
		waitsem(sem2);
		_outchar('2');
		signalsem(sem3);
		
	}
}

PROCESS P3(void){
	DO_FOREVER{
		waitsem(sem3);
		_outchar('3');
		signalsem(sem4);
	}
}
 
PROCESS P4(void){
	DO_FOREVER{
		waitsem(sem4);
		_outchar('4');
		signalsem(sem1);
	}
}
