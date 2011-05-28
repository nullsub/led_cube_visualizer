#ifndef UART_H
#define UART_H


//#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define RECIEVE_BUFFER_SIZE 99
char r_buffer[RECIEVE_BUFFER_SIZE]; // the recieve buffer
char * current_write;
char * current_read;
int fifo_cnt;



void uart_init();
unsigned char uart_getc();
void uart_putc(char data);
void uart_puts(char * data);



/* UART-Init beim AT90S2313 */
 
#ifndef F_CPU
#error "F_CPU is not defined"
#endif
 
#define BAUD 9600UL      // Baudrate
 
// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.
 
#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif
 







#endif // UART_H
