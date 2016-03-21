/* included header files - necessary for functions and defined pins */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//void pwm_init(void);


// Pin Definitions (same for fruit and vegetable boards)
#define RED_PIN     PD3
#define GREEN_PIN   PD6
#define BLUE_PIN    PD5
#define LED_PORT    PORTD
#define LED_DDR     DDRD
#define ROT_A       PC0
#define ROT_B       PC1
#define BUTTON      PC3

int main(void)
{
    
    // Set all three pins to output
    LED_DDR |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN);
    
    int delay_amount = 1000;
    
    // loop forever
    while(1)
    {
        // light red LED, then turn off
        LED_PORT |= (1<<RED_PIN);
        _delay_ms(delay_amount);
        LED_PORT &= ~(1<<RED_PIN);
        _delay_ms(delay_amount);
        
        // light green LED, then turn off
        LED_PORT |= (1<<GREEN_PIN);
        _delay_ms(delay_amount);
        LED_PORT &= ~(1<<GREEN_PIN);
        _delay_ms(delay_amount);
        
        
        // light blue LED, then turn off
        LED_PORT |= (1<<BLUE_PIN);
        _delay_ms(delay_amount);
        LED_PORT &= ~(1<<BLUE_PIN);
        _delay_ms(delay_amount);
    }
    
}