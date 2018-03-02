/* ====================================

File name: exerc_6_4_a.c 

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */

// Following TYPES is defined, local in this modul,  and could be used to specify type of interrupt with 
// the global variable int interruptType. ( Not : The name is convered to _interruptType by the C-compiler)

#define NO_IRQ_TYPE	0	 // Set to a IRQ value when IRQ request 
#define SENSOR		1
#define CLOSED_DOOR	2    // Door is closed
#define OPENED_DOOR	4    // Door is fully open


// Codes for closing/opening the door.
#define OPEN_DOOR       0x01
#define CLOSE_DOOR	    0x02

// Register addresses in ML13 door unit
#define ML13_Status	     0x0B00
#define ML13_Control	 0x0B00
#define ML13_IRQ_Control 0x0B01
#define ML13_IRQ_Status  0x0B01

// Macros for read and write in ML13 register.

#define REG8(x) *((unsigned char *)(x))

// Macro for write IRQ routin adress in vector table.
#define  SET_IRQ_VECTOR(interrupt_handler, address)    *((unsigned int *) address )= &(interrupt_handler)


// -------  Declaration of functions in this modul ------------
void IRQ_init(void);


// ------    Declaration of the interrupt routine
__interrupt void  ML13_interrupt( void );   

// A global variable affected by the interrupt service routine handler: void  ML13_interrupt( void ). 

int	interruptType=0; 

// ----------   Main program   -------
void	main(){
    puts("Started...");  
    IRQ_init(); // Set up the system for interrupt
    while(1)    {
        interruptType = NO_IRQ_TYPE;
        while(interruptType==NO_IRQ_TYPE){};   // Wait for a IRQ
        interruptType =CLOSED_DOOR;// Do something depending on the value for interruptType
		set_control(0x2);
		
    }

}
// -----------------------------------------------------------------------------------------
// Interrupt service function for hardware irq ( vector address 0x3FF2 )
// This routin will be called for any IRQ from the ML13 modul( Sensor, door opened, door closed..)

__interrupt void  ML13_interrupt( void ){
    puts("interrupt");  // This function will be activated for every IRQ request from the Door unit.
                        // Check IRQ source and set Interrupt_Type
	printf("IRQ %#x\n",REG8(ML13_IRQ_Status)); 
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
	
    REG8(ML13_IRQ_Control)=0x01;  // Ack of the hardware irq. 
	                              //Continue in normal mode at the nstruction taht was interrupted. 
}

// Function for system setup ( IRQ ....)
void IRQ_init(void){
  // This function is ok already, don´t change any in this 	
  SET_IRQ_VECTOR(ML13_interrupt, 0x3FF2)  // Save start address for irq function to Vector table.
  __asm("CLI"); 			              // Allow CPU affect on IRQ signals
  REG8(ML13_IRQ_Control)= 0x00;           // Enable IRQ from ML13 unit ( To be sure but == 0 at start)

}





     
