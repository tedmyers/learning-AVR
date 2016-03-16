/* included header files - necessary for functions and defined pins */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void pwm_init(void);


int main(void)
{
    //Initialize PWM
    pwm_init();
    
    // OC0A is tied to pin PD6 (pin 12 on 328 chip)
    // OC0B is tied to pin PD5 (pin 11 on 328 chip)
    // OC2B is tied to pin PD3 (pin 5 on 328 chip)
    // Set all three pins to output
    DDRD |= (1 << PD6) | (1 << PD5) | (1 << PD3);
    
    // Start all color channels off
    OCR0A = 255;
    OCR0B = 255;
    OCR2B = 255;
    
    int delay_amount = 2; // milliseconds to delay between changing PWM values
    
    while(1)
    {
        // fade green up
        for (int i = 0; i < 256; i++)
        {
            OCR0A = (255-i);
            _delay_ms(delay_amount);
        }
        // fade green down
        for (int j = 255; j >= 0; j--)
        {
            OCR0A = (255-j);
            _delay_ms(delay_amount);
        }
        
        
        //fade blue up
        for (int i = 0; i < 256; i++)
        {
            OCR0B = (255-i);
            _delay_ms(delay_amount);
        }
        // fade blue down
        for (int j = 255; j >= 0; j--)
        {
            OCR0B = (255-j);
            _delay_ms(delay_amount);
        }
        
        //fade red up
        for (int i = 0; i < 256; i++)
        {
            OCR2B = (255-i);
            _delay_ms(delay_amount);
        }
        // fade red down
        for (int j = 255; j >= 0; j--)
        {
            OCR2B = (255-j);
            _delay_ms(delay_amount);
        }
        
    }

}

// Initialize PWM: set the mode for timers, configure settings
void pwm_init(void)
{
    // Fast PWM mode for timers 0 and 2 (p.106)
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    
    // clear OC0A on compare match, set on BOTTOM (inverting) (p.104)
    // 255 is fully off, 0 is fully on
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0); // set for A0 & B0
    TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
    
    // Use clock directly, no prescaler (p.107)
    TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
    TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
    
    // initialize counter for TIMER 0 and TIMER 2 (p.108)
    TCNT0 = 0;
    TCNT2 = 0;
}