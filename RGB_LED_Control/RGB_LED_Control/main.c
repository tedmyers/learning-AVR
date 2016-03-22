#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t green_value = 255;
volatile uint8_t blue_value = 255;
volatile uint8_t red_value = 255;
volatile uint8_t portchistory = 0;

int i = 0;

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
        // Change values based on current channel defined by button
        
        if (_BV(PC0) & PINC) //rising edge
        {
            if (_BV(PC1) & PINC){
                if(i == 0){red_value++;}
                else if(i == 1){blue_value++;}
                else if(i == 2){green_value++;}
            }

            else{
                if(i == 0){red_value--;}
                else if(i == 1){blue_value--;}
                else if(i == 2){green_value--;}
            }
                
        }
        else //falling edge
        {
            if (_BV(PC1) & PINC){
                if(i == 0){red_value--;}
                else if(i == 1){blue_value--;}
                else if(i == 2){green_value--;}
            }

            else{
                if(i == 0){red_value++;}
                else if(i == 1){blue_value++;}
                else if(i == 2){green_value++;}

            }
        }
    }
    
    else if(changedbits & _BV(PC5) && ((PINC & _BV(PC5)) == 0)){
        /* button pressed */
        // change the channel the rotary encoder is controlling
        
        i++;
        if(i == 3){i = 0;}
    }
}

void pwm_init(void)
{
    // Fast PWM mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    
    // clear OC0A on compare match, set on BOTTOM (inverting)
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0);
    TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
    
    // Use clock directly, no prescaler
    TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
    TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);

    
    // initialize counter for TIMER 0
    TCNT0 = 0;
    TCNT2 = 0;
    
    //Set LED pins as output
    DDRD |= ((1 << PD3) | (1 << PD5) | (1 << PD6));
    
    //Rotary encoder pins as input
    DDRC &= ~(1 << PCINT8);
    DDRC &= ~(1 << PCINT9);
    PORTC |= (1 << PCINT8)|(1 << PCINT9);
    
    //Button as input
    DDRC &= ~(1 << PC5);
    PORTC |= (1 << PC5);
    
    //Enable Interrupts
    PCICR |= _BV(PCIE1);
    PCMSK1 |= (_BV(PCINT8) | _BV(PCINT10) | _BV(PCINT12) | _BV(PCINT13));
}

int main(void)
{
    // Initialize all IO pins and PWM
    pwm_init();
    
    // Enable global interrupts
    sei();
    
    // Start all channels at no brightness
    OCR0B = 255;
    OCR0A = 255;
    OCR2B = 255;
    
    while(1)
    {
        OCR0A = red_value;
        OCR0B = blue_value;
        OCR2B = green_value;
        _delay_ms(1);
    }
}