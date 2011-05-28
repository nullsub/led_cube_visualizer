
#include "led_matrix.h"



ISR (TIMER2_COMP_vect)
{
	int8_t static crrnt_collumn = 0;
	register_state[LINE_REG1] = led_matrix_framebffr[(crrnt_collumn*SIZE_Y*SIZE_Z)/8];
	register_state[LINE_REG2] = led_matrix_framebffr[((crrnt_collumn*SIZE_Y*SIZE_Z)/8)+1];
	
	switch(crrnt_collumn){
		case 0: 
			COLLUMN3_PORT &= ~(1<<COLLUMN3_PIN);
			shift_out();
			COLLUMN0_PORT |= (1<<COLLUMN0_PIN);
			break;
		case 1: 
			COLLUMN0_PORT &= ~(1<<COLLUMN0_PIN);
			shift_out();
			COLLUMN1_PORT |= (1<<COLLUMN1_PIN);
			break;
		case 2: 
			COLLUMN1_PORT &= ~(1<<COLLUMN1_PIN);
			shift_out();
			COLLUMN2_PORT |= (1<<COLLUMN2_PIN);
			break;
		case 3: 
			COLLUMN2_PORT &= ~(1<<COLLUMN2_PIN);
			shift_out();
			COLLUMN3_PORT |= (1<<COLLUMN3_PIN);
			break;
	}
	

	crrnt_collumn ++;
	if(crrnt_collumn >= NR_OF_COLLUMNS) crrnt_collumn = 0;
	__asm("wdr"); // reset watchdog
}


void led_matrix_init()
{
	shift_init();

	led_matrix_framebffr = led_matrix_framebffr_;
	  // Timer 0 konfigurieren
	


	COLLUMN0_DDR |= (1<<COLLUMN0_PIN);
	COLLUMN1_DDR |= (1<<COLLUMN1_PIN);
	COLLUMN2_DDR |= (1<<COLLUMN2_PIN);
	COLLUMN3_DDR |= (1<<COLLUMN3_PIN);

	COLLUMN0_PORT &= ~(1<<COLLUMN0_PIN);
	COLLUMN1_PORT &= ~(1<<COLLUMN1_PIN);
	COLLUMN2_PORT &= ~(1<<COLLUMN2_PIN);
	COLLUMN3_PORT &= ~(1<<COLLUMN3_PIN);


 	 // CTC Modus
  	TCCR2 |= (1<<WGM21)|(1<<CS22); // Prescaler 64
	OCR2 = 77;//((0.000625 / (1/F_CPU)) / 64)-1;   //  (TimeToGet/(1/F_CPU))/PRESCALER == to write in OCR0A
 	
  	// Compare Interrupt erlauben
  	TIMSK |= (1<<OCIE2);
 
  	// Global Interrupts aktivieren
	WDTCR |= (1<<WDCE)|(1<<WDE);
	WDTCR |= (1<<WDP0)|(1<<WDP1)|(1<<WDE); //enable watchdog approximatily every 12ms

  	sei();
}
 
void led_matrix_clr_pixel(int8_t x, int8_t y, int8_t z){
	led_matrix_pixel(x,y,z,0);
}

void led_matrix_set_pixel(int8_t x, int8_t y, int8_t z){
	led_matrix_pixel(x,y,z,1);
}

void led_matrix_pixel(int8_t x, int8_t y, int8_t z, int8_t val)
{
	int index = z*2;
	if(x < 0 || y < 0 || z < 0 || x >= SIZE_X || y >= SIZE_Y || z >= SIZE_Z){
		//uart_puts("trying to set invalid pixel\n");
		return;
	}
	x = 1 << x;
	if(y%2){
		x = x << 4; 
	}
	y = y >> 1; // y/2
	index += y;
	if(val == 1){
		led_matrix_framebffr[index] |= x; // set bit
	}
	else{
		led_matrix_framebffr[index] &= ~x; //clear bit
	} 	
}

void led_matrix_clr_all(){
	for(int i = 0; i < (SIZE_X*SIZE_Y*SIZE_Z)/8;i++) led_matrix_framebffr[i] = 0;
}

void led_matrix_set_all(){
	for(int i = 0; i < (SIZE_X*SIZE_Y*SIZE_Z)/8;i++) led_matrix_framebffr[i] = 0xff;
}

