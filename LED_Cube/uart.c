#ifndef UART_C
#define UART_C 

#include "uart.h"
 
//static prototype
static void  uart_write_fifo(char data);

void uart_init(){
    	UBRRH = UBRR_VAL >> 8; // set baud-rate
    	UBRRL = UBRR_VAL & 0xFF;//set baud-rate

	UCSRB |= ( 1 << RXEN ); //enable rx zum empfangen
	UCSRB |= (1<<TXEN);                // UART TX einschalten
	UCSRB |= (1<<RXCIE); //enable interupt for recieve ....

    	UCSRC |= (1<<URSEL)|(3<<UCSZ0);    // Asynchron 8N1 
	__asm("sei");
	current_write = &r_buffer[0];
	current_read = &r_buffer[0];
	fifo_cnt = 0;
	return;
}

static void  uart_write_fifo(char data){ // write data to the circular buffer
	if(fifo_cnt< RECIEVE_BUFFER_SIZE - 2){
		
		if(current_write == (&r_buffer[0] + RECIEVE_BUFFER_SIZE)){
			current_write = &r_buffer[0];
		}
		else{
			*current_write = data;
			current_write ++;
		}
		
		fifo_cnt++;
	}
	else{	
		uart_putc('F');	
		uart_putc('U');
		uart_putc('L');
		uart_putc('L');
		uart_putc('\n');
		uart_putc('\r');

	}

}
/* Zeichen empfangen */
unsigned char uart_getc(void) // fetch charackter from rinbuffer
{	unsigned char data = 0x00;
	if(fifo_cnt == 0){	
		return 0;
	}
	if(current_read == (&r_buffer[0] + RECIEVE_BUFFER_SIZE)){
		current_read = &r_buffer[0];
	}
	else{
		data = *current_read;
		current_read ++;
	}
	fifo_cnt--;
	return data;
}

void uart_putc(char data){
	while (!(UCSRA & (1<<UDRE)));  /* warten bis Senden moeglich                   */
	UDR = data;
}

void uart_puts(char * data){
	while(*data){
		uart_putc(*data);
		data++;
	}
}



ISR(USART_RXC_vect){
	uart_write_fifo(UDR);	
}


#endif //UART_C
