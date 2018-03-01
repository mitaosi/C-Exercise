/* ====================================

File name: Exerc_6_4.c 

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */
#include <stdio.h>

#define NO_IRQ_TYPE	0
#define CLOSED_DOOR	2
#define OPENED_DOOR	4

#define TIME_OUT	32   // Common define in the assembly file is needed

// Codes for closing/opening the door.
#define OPEN_DOOR       0x01
#define CLOSE_DOOR	0x02

// Register addresses
#define ML13_Status	 0x0B00
#define ML13_Control	 0x0B00
#define ML13_IRQ_Control 0x0B01
#define ML13_IRQ_Status  0x0B01


#define REG8(x) *((unsigned char *)(x))
#define set_control(x) *((char *)ML13_Control)=x


typedef void (*pointer_to_ISR)(void);
	
extern void standby(void);
extern void timerSetup(void);
extern void setTimeout(int);


int	interruptType;


void IRQ_init(void);
__interrupt void  ML13_interrupt( void );
int main(){
	IRQ_init(); // Set up the sytem for interrupt
	while(1){
		standby();
		if(interruptType==OPENED_DOOR){
			interruptType=NO_IRQ_TYPE;
			setTimeout(2);
			while(interruptType!=TIME_OUT){}
			interruptType=CLOSE_DOOR;
			set_control(0x2);
		}
	}
  return 0;
}


void IRQ_init(void){
  *(pointer_to_ISR *)0x3FF2 = ML13_interrupt;   // Start address for IRQ function to Vector table.
  timerSetup();                           		// Configure the timer module 
  __asm("CLI"); 			  					// Allow CPU affect on IRQ signals

}



__interrupt void  ML13_interrupt( void ){
	
	printf("IRQ %#x\n",REG8(ML13_IRQ_Status)); 	//print IRQ
	
	if(REG8(ML13_IRQ_Status) & 0x1){
		interruptType=OPENED_DOOR;
	}
	if(REG8(ML13_IRQ_Status) & 0x2){
		interruptType=CLOSED_DOOR;
	}
	
	if(REG8(ML13_IRQ_Status) & 0x4){
		set_control(0x1);
		interruptType=OPEN_DOOR;
	}
	
	if(REG8(ML13_IRQ_Status) & 0x8){
		set_control(0x1);
		interruptType=OPEN_DOOR;
	}
	
     
     REG8(ML13_IRQ_Control)=0x01;   		 // Ack of the hardware irq 
}


     
