#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define red PD5
#define blue PD3
#define green PD6

#define button PC3

int i = 0;


void initIO(void) {
    //Set the red, green, and blue pins as output
    DDRD |= ((1 << red) | (1 << blue) | (1 << green));
    
    //Set the button pin as an input
    DDRC &= ~(1 << button);
    
    //Enable pullup resistor on the button pin
    PORTC |= (1 << button);
    
}


int main(void) {
    //Initialize input/output and interrupts
    initIO();
    
    while (1) {
        if((PINC & _BV(button)) == 1){
            i++;
        }
        
        if(i >= 3){i = 0;}
        
        if(i == 0){
            PORTD |= _BV(PC3);
            PORTD &= ~_BV(PC5);
            PORTD &= ~_BV(PC6);
        }
        else if(i == 1){
            PORTD |= _BV(PC5);
            PORTD &= ~_BV(PC3);
            PORTD &= ~_BV(PC6);
        }
        else{
            PORTD |= _BV(PC6);
            PORTD &= ~_BV(PC5);
            PORTD &= ~_BV(PC3);
        }
        
    }
    
    
    return 0;
}