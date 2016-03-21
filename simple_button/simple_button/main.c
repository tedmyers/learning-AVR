/* included header files - necessary for functions and defined pins */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void pwm_init(void);
// Note: change button pin for fruit/vegetable boards

// Pin Definitions (same for fruit and vegetable boards)
#define RED_PIN     PD3
#define GREEN_PIN   PD6
#define BLUE_PIN    PD5
#define LED_PORT    PORTD
#define LED_DDR     DDRD
#define ROT_A       PC0
#define ROT_B       PC1

#define BUTTON    PC3 // Fruit
//#define BUTTON    PC5 // Vegetable

#define BUTTON_PORT PORTC
#define BUTTON_DDR  DDRC
#define BUTTON_PIN  PINC

int main(void)
{
    
    // Set all three pins to output
    LED_DDR |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN);
    
    // Set Button to input
    BUTTON_DDR &= ~(1<<BUTTON);
    
    // Set internal pull-up resistor
    BUTTON_PORT |= (1<<BUTTON);
    // (same as PORTC |= (1<<3) )
    
    while (1)
    {
        if ( (BUTTON_PIN & (1<<BUTTON)) == 0 )
            LED_PORT |= (1<<RED_PIN) | (1<<BLUE_PIN) | (1<<GREEN_PIN);
        else
            LED_PORT &= ~( (1<<RED_PIN) | (1<<BLUE_PIN) | (1<<GREEN_PIN) );
    }
    
    
    

    
}