#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#define Button 0
#define LED    1

void UART_init() {
    UCSRB |= (1 << TXEN); // Enable Transmitter
    //UCSRB |= (1 << UDRIE); // Enable UDRE Interrupt

    // BaudRate
    UBRRL = 51;
}

//ISR(USART_UDRE_vect) {
//
//    UDR = 'A'; // Transmit Data
//
//}


int isPressed(int pinNum);
void transmitChar(char data);
void transmitString(char *data);
char str1[] = "LED is ON\t\r";
char str2[] = "LED is OFF\t\r";

int main(void) {
    /* Replace with your application code */
    DDRC &= ~(1 << Button); // Input button
    DDRC |= (1 << LED); // output (LED)
    UART_init(); // Enable Transmitter ONLY


    //    UDR = 'A';
    while (1) {
        while(!(UCSRA &(1<<UDRE)));//UDR empty 1 >>True >> FALSE>> break while loop
        if (isPressed(Button)) {
            // Pooling Interrupt
            //UDR = 'A';
            PORTC ^= (1 << LED);
            if (isPressed(LED)) {
            transmitString(str1);
            }
            else {
               transmitString(str2);
            }
            
            _delay_ms(500);
        }

    }
}

int isPressed(int pinNum) {
    if (PINC & (1 << pinNum)) {
        return 1;
    } else
        return 0;
}

void transmitChar(char data) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = data;
}

void transmitString(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        transmitChar(data[i]);
    }}


//int main(void){
//    UART_init(); 
//        sei();
//
//  //  UDR = 'A'; 
//    while(1){
//        
//    }
//    
//}