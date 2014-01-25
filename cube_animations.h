#ifndef CUBE_ANIMATIONS_H
#define CUBE_ANIMATIONS_H

#include "led_matrix.h"

typedef struct {
	void * next;
	int loop; //how many loops to do
 	int8_t *data;
	int length;
}animation;

void animation_init();
void set_animation(animation * new_animation);






extern int8_t animation01[][FRAME_SIZE];
extern int8_t animation02[][FRAME_SIZE];
extern int8_t animation03[][FRAME_SIZE];



#endif
