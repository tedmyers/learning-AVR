#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//Set as PC3 and PCINT11 for fruit
//Set as PC5 and PCINT 13 for vegetable
#define button PC5
#define button_interrupt PCINT13

ISR(PCINT1_vect){
    //Turn on all of port D
    PORTD |= (1 << PD5);
}

void initIO(void) {
    //Define PC3 as input with pullup-resistor
    DDRC &= ~(1 << button);
    PORTC |= (1 << button);
    
    //Enable interrupt for PCINT11
    PCICR |= _BV(PCIE1);
    PCMSK1 |= (_BV(button_interrupt));
    
    //Set LED as output
    DDRD |= (1 << PD5);
}

int main(void) {
    //Initialize all IO ports
	initIO();
    
    //Enable global interrupts
    sei();
    

	while (1) {
        //Nothing happens in while loop
        //Could add something here to run while waiting for button
	}
	return 0; // never reached
}


