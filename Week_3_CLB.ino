#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

/* Function: 
 * Timer0 | 8-bit timer 
 * Page 94 in data sheet describes the registers associated with this timer
 * We will be using PWM mode 
 */
void setupTimer0(void){
  // Setup pins associated with Timer0 as outputs
  DDRD |= (1<<0);   // Motor B Speed (OC0B)
  DDRB |= (1<<7);   // Motor A Speed (OC0A)

  TCCR0B |= (1<<2); // Set the prescaler to 256
  
  TCCR0A |= (1<<7) | (1<<5);  // Set Motor 1 input 1 (OC0A) and Motor 2 input 1 (OC0B) to Compare Match 
  TCCR0A |= (1<<1)|1;         // Set the Timer0 to Fast-PWM mode
  
  OCR0A = 0;          // Set duty cycle of PWM on OC0A to 20%  (255 * 0.2 = 51)
  OCR0B = 0;          // Set duty cycle of PWM on OC0B to 20%  (255 * 0.2 = 51)
  
  TCNT0=0;  // Set Timer0 counter to zero
}

/*  
 * Timer1 | 16-bit timer 
 * Page 131 in data sheet describes the registers associated with this timer
 * We will be operating this timer in  8-bit PWM mode. This means that the timer
 * will overflow when it reaches 255 rather than 65535
 */
void setupTimer1(void){
  // Setup pins associated with Timer1 as outputs
  DDRB |= (1<<5);   // Motor A Direction (OC1A)
  DDRB |= (1<<6);   // Motor B Direction (OC1B)
  
  // Timer 1 
  // Only needed to set motors backwards (if you've wired in your motors in the same manner as me)
  TCCR1B |=  (1<<2); // Set the prescaler to 256
  TCCR1B |= (1<<3); // Set to Fast PWM - 8 Bit

  TCCR1A |= (1<<7) | (1<<5) | 1;    // Set OC1B and OC1A to Clear on Compare Match
  
  OCR1B = 0;          // Set duty cycle of PWM on OC1B to 20%  (255 * 0.2 = 51)
  OCR1A = 0;          // Set duty cycle of PWM on OC1A to 20%  (255 * 0.2 = 51)
}

// Main function
int main(){
     
  // Setup Timer0
  setupTimer0();

  // Setup Timer1
  setupTimer1();

  // Delay
  
  // Setup infinite loop
  while (1){

    // Increment the compare match value
    OCR0A = 110;
    OCR0B = 102;

    /* If the compare match values are greater than overflow value (minus increment)
     * then reset the compare match value to intial */
    /*if (OCR0A >= 245 || OCR0B >= 245){
        OCR0A = 51;
        OCR0B = 51;
        */
    _delay_ms(1970);
    OCR0A = 0;
    OCR0B = 0;
    break;    
    }

  }

  //return 0;
