#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H SHIFT_REGISTER_H

#include <avr/io.h>
// defines the üpins
#define SHIFT_RCK 	2
#define SHIFT_SCK       1
//#define SHIFT_SCL	2 no reset needed. is directly connected to VCC
#define SHIFT_SER     	3
//#define SHIFT_NOT_ENABLE 4 
#define SHIFT_DDR 	DDRC
#define SHIFT_PORT 	PORTC

 
#define BITS_TO_SHIFT 8 // how many shift registers are connected
#define NR_OF_REGISTERS 2 // how many registers are in a row

int8_t current_byte;
int8_t register_state[NR_OF_REGISTERS];



void shift_init();
void shift_out();
void shift_output_disable();


#endif //SHIFT_REGISTER_H
