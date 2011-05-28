

#include "led_matrix.h"
#include "cube_animations.h"
#include <util/delay.h>
#include <stdlib.h>




int main(){
	led_matrix_init();
	animation_init();
	animation animation1,animation2,animation3;
	animation1.data = (int8_t *)animation01;
	animation1.length = 8;
	animation1.loop = 20;
	animation1.next = &animation2;

	animation2.data = (int8_t *)animation02;
	animation2.length = 8;
	animation2.loop = 20;
	animation2.next = &animation3;

	animation3.data = (int8_t *)animation03;
	animation3.length = 7;
	animation3.loop = 20;
	animation3.next = &animation1;
	set_animation(&animation1);
	while(1){
			
	}

}

