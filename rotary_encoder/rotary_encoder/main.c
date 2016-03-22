#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t knob1_value = 0;
volatile uint8_t portchistory = 0;

//Set to PC3 and PCINT11 for fruit
//Set to PC5 and PCINT13 for vegetable
#define button PC5
#define button_interrupt PCINT13

//PCINT1 interrupt
ISR(PCINT1_vect)
{
    uint8_t changedbits;
    
    //capture which bits have changed since last time
    
    changedbits = PINC ^ portchistory;
    portchistory = PINC;
    
    if(changedbits & _BV(PC0))
    {
        /* PCINT8 changed */
        // Knob 1
        
        if (_BV(PC0) & PINC) //rising edge
        {
            if (_BV(PC1) & PINC) //clockwise
                knob1_value++;
            else
                knob1_value--;
        }
        else //falling edge
        {
            if (_BV(PC1) & PINC)
                knob1_value--;
            else
                knob1_value++;
        }
    }
    
    else if(changedbits & _BV(button) && ((PINC & _BV(button)) == 0)){
        /*Button Pressed*/
        
        //Toggles LED when pressed
        PORTD ^= (1 << PD5);
    }
}

void pwm_init(void)
{
    // Fast PWM mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // clear OC0A on compare match, set on BOTTOM (inverting)
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
    
    // Use clock directly, no prescaler
    TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
    
    // initialize counter for TIMER 0
    TCNT0 = 0;
}

void IO_init(void){
    //Set two LEDs as output
    DDRD |= (1 << DDD6) | (1 << PD5);
    
    /* set PD2 and PD3 as input */
    DDRC &= ~(1 << PCINT8);
    DDRC &= ~(1 << PCINT9);
    PORTC |= (1 << PCINT8)|(1 << PCINT9);  //enable pullups
    
    //Set PC5 as input with pullup
    DDRC &= ~(1 << button);
    PORTC |= (1 << button);
    
    //enable PCINT1 interrupt signal
    PCICR |= _BV(PCIE1);
    //enable interrupts on four pins
    PCMSK1 |= (_BV(PCINT8) | _BV(PCINT10) | _BV(PCINT12) | _BV(button_interrupt));
}

int main(void)
{
    //Initialize PWM and IO
    pwm_init();
    IO_init();
    
    //Enable global interrupts
    sei();
    
    while(1)
    {
        //Set the value of PD6 to the knob value
        OCR0A = knob1_value;
        _delay_ms(1);
    }
}