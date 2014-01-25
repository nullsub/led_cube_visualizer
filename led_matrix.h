#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "shift_register.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define SIZE_Z 4
#define SIZE_X 4
#define SIZE_Y 4

//shift register index

#define LINE_REG1    0
#define LINE_REG2    1

#define COLLUMN0_PORT 	PORTD
#define COLLUMN1_PORT	PORTD
#define COLLUMN2_PORT	PORTD
#define COLLUMN3_PORT	PORTB

#define COLLUMN0_PIN 5
#define COLLUMN1_PIN 6
#define COLLUMN2_PIN 7
#define COLLUMN3_PIN 0

#define NR_OF_COLLUMNS 4

#define COLLUMN0_DDR 	DDRD
#define COLLUMN1_DDR	DDRD
#define COLLUMN2_DDR	DDRD
#define COLLUMN3_DDR	DDRB

#define FRAME_SIZE (SIZE_X*SIZE_Y*SIZE_Z)/8

int8_t led_matrix_framebffr_[FRAME_SIZE]; //staticly alloc some space

int8_t *led_matrix_framebffr; //[(SIZE_X*SIZE_Y*SIZE_Z)/8];

#define ANIMATION_01_LENGTH 10
/*

*/
							

void led_matrix_init();
void led_matrix_clr_all(); // clear all leds
void led_matrix_set_all(); // set ---------
void led_matrix_set_pixel(int8_t x, int8_t y, int8_t z); //set pixel
void led_matrix_clr_pixel(int8_t x, int8_t y, int8_t z); //clear pixel
void led_matrix_pixel(int8_t x,int8_t y, int8_t z, int8_t val); //set ,pixel to val.

#endif
