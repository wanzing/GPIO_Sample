
#ifndef _PCAL6416A_H_
#define _PCAL6416A_H_

//#define COMPILE

#define I2C_ADDR_PCAL6416 0x40	// Hardware address package pin is LOW 

/* 	Register address of PCAL6416 
	All registers can be read/written in word 
	except Output port configuration register(0x4F) 
	Described in datasheet page 9 - page 16
 */ 
#define PCAL6416_INPUT		0x00	// Input port0: 0x00, Input port1: 0x01 			
#define PCAL6416_OUTPUT		0x02	// Output port0: 0x02, Output port1: 0x03 			
#define PCAL6416_POLARINV	0x04	// Polarity Inversion port0: 0x04, port1: 0x05		
#define PCAL6416_CONFIG		0x06	// Configuration port0: 0x06, port1: 0x07			
#define PCAL6416_OUT_STR0	0x40	// Output drive strength register Port0: 0x40, 0x41	
#define PCAL6416_OUT_STR1	0x42	// Output drive strength register Port0: 0x40, 0x41	
#define PCAL6416_IN_LATCH	0x44	// Input latch register port0: 0x44, port1: 0x45	
#define PCAL6416_PUPD_EN	0x46	// Pull-up/Pull-down Enable port0: 0x46, port1: 0x47	
#define PCAL6416_PUPD_SEL	0x48	// Pull-up/Pull-down Enable port0: 0x48, port1: 0x49	
#define PCAL6416_INT_MASK	0x4A	// Interrupt mask port0: 0x4A, port1: 0x4B		 	
#define PCAL6416_INT_STATUS	0x4C	// Interrupt status port0: 0x4C, port1: 0x4B	
#define PCAL6416_OUT_CONFIG	0x4F	// Output port configuration register	 

#define ODDIS				0x00	//Open Drain Disabled
#define ODEN0				0x01	// Output port0 Open Drain Enable for OUT_CONFIG
#define ODEN1				0x02	// Output port1 Open Drain Enable for OUT_CONFIG

#define BIT0				0x0001
#define PORT1_OFFSET		8



#endif

