#ifndef SHIFT_REGISTER_C
#define SHIFT_REGISTER_C SHIFT_REGISTER_C

#include "shift_register.h"



void shift_init(){// define shift-register pins as output
	SHIFT_DDR |= (1<<SHIFT_RCK) | (1<<SHIFT_SCK)| (1<<SHIFT_SER)/*|(1<<SHIFT_NOT_ENABLE) | (1<<SHIFT_SCL) */;
	SHIFT_PORT &= ~((1<<SHIFT_RCK) | (1<<SHIFT_SCK) | (1<<SHIFT_SER)/*|(1<<SHIFT_NOT_ENABLE)| (1<<SHIFT_SCL)*/ );
	/*SHIFT_PORT |= (1<<SHIFT_SCL);*/
	
	shift_output_disable();

	return;
}

void shift_out(){
	unsigned char Temp,out_byte;
	int bit_counter, register_cnt;

	for(register_cnt = 0;register_cnt < NR_OF_REGISTERS;register_cnt++){
		out_byte = register_state[(NR_OF_REGISTERS-1)-register_cnt];
		for(bit_counter = 0; bit_counter < BITS_TO_SHIFT; bit_counter ++){
			Temp = (out_byte & 0b10000000);  
        		if(Temp  != 0){
				SHIFT_PORT |= (1<<SHIFT_SER);  
			}
			else{
				SHIFT_PORT &= ~(1<<SHIFT_SER);
			}
			out_byte  = (out_byte  <<  1); 
			SHIFT_PORT |= (1<<SHIFT_SCK); 
			__asm("nop");
			SHIFT_PORT &= ~(1<<SHIFT_SCK);;
		}	
	}

	//Latch-->output
	SHIFT_PORT |= (1<<SHIFT_RCK); 

	//SHIFT_PORT &= ~(1<<SHIFT_NOT_ENABLE); //delay needed anyway
	__asm("nop");

	SHIFT_PORT &= ~(1<<SHIFT_RCK); 


	return;
}


void shift_output_disable(){
//	SHIFT_DDR  |= (1<<SHIFT_NOT_ENABLE);
//	SHIFT_PORT |= (1<<SHIFT_NOT_ENABLE);
}


#endif//SHIFT_REGISTER_C
