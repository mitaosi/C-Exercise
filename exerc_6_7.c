/* ====================================

File name: exerc_6_7.c

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */
#include <_rtk.h>

#define TIMESLICE 10
#define ML13_Status	 0x0B00
#define ML13_Control	 0x0B00

#define REG8(x) *((unsigned char *)(x))
#define set_control(x) *((char *)ML13_Control)=x

#define sem_wait_open 1
#define sem_open 2
#define sem_wait_opened 3
#define sem_opened 4
int isLocked;

extern void _outchar(int);
extern int _tstchar(void);
extern int get_rtk_time(void);
extern void dispatch(void);
extern void suspend(PCB *);

void sleep(int);
void yield(int);

PROCESS KEY_EVENT(void);
PROCESS manage_door(void);
PROCESS door_open_check(void);
PROCESS door_opened_check(void);
void AtInterrupt (void);


int main(){
	isLocked=0;
	InitKernel(TIMESLICE, AtInterrupt);
	
	if( CreateProcess("KEY_EVENT", KEY_EVENT) == -1){
		printl("Can't create process\n");
        }
	
	if( CreateProcess("manage_door", manage_door) == -1){
		printl("Can't create process\n");
        }
	
	if( CreateProcess("door_open_check", door_open_check) == -1){
		printl("Can't create process\n");
	}
	
	if( CreateProcess("door_opened_check", door_opened_check) == -1){
		printl("Can't create process\n");
        }
	
	initsem(sem_wait_open,0);
	initsem(sem_open,0);
	initsem(sem_wait_opened,0);
	initsem(sem_opened,0);
	
        StartKernelForSim();

return 0;
}



void AtInterrupt(){
	insert_last(Running, &ReadyQ); 
	Running= remque(&ReadyQ);
}

PROCESS door_open_check(void){
	DO_FOREVER{
		waitsem(sem_wait_open);
		//printl("hej");
		DO_FOREVER{
			if(!isLocked&&(REG8(ML13_Status)&0x1 || REG8(ML13_Status)&0x2)){
				signalsem(sem_open);
				break;
			}else{
				yield(0);
			}
		}
	
	}
}


PROCESS door_opened_check(void){
	DO_FOREVER{
		waitsem(sem_wait_opened);
		DO_FOREVER{
			if(REG8(ML13_Status)&0x8 ){
				signalsem(sem_opened);
				break;
			}else{
				yield(0);
			}
		}
	
	}
}

PROCESS manage_door(void){
	DO_FOREVER{
		signalsem(sem_wait_open);
		waitsem(sem_open);
		set_control(0x1);
		signalsem(sem_wait_opened);
		waitsem(sem_opened);
		sleep(2);
		set_control(0x2);
	}

}

PROCESS KEY_EVENT(void){
	DO_FOREVER{
		int i;
		i=_tstchar();
		_outchar(i);
		if(i==117){
			isLocked=0;
		}
		
		if(i==108){
			isLocked=1;
		}
	}
}

void sleep(int delay){ 
	int wakeup; 
	wakeup = get_rtk_time() + delay; /* sleep for delay * TIMESLICE*/ 
 
	while(1){ 
		if( wakeup > get_rtk_time() ) 
		yield(0);
		else 
			return; 
	} 
}


void yield(int dummy) { 			// Dummy parameter is for the 'suspend' to work well 
	dummy=0; 						//remove warning
	DISABLE; 						// can't take process switch here 
	insert_last(Running, &ReadyQ);  // Calling Process last in Rea 
	suspend(Running); 				// Saving context for Calling process 
	dispatch(); 					// Start next process in ready queue 
}
