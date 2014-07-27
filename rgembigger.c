/*-------|---------|---------|---------|---------|---------|---------|---------|
rgembigger.c	

a PWM controller for RGB photo enlarger head

by chaz miller for ATMEGAxx8 set at 1MHz running at 5V. 

This is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 or any later
version. This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
******************************************************************/
//todo: calibrate for Ilford VC paper to maintain same exposure 
//for a given contrast
//question: is 8 bits enough color resolution for color printing?

#include <avr/io.h>
#include <adc.h>

void delay(uint16_t);
void blink (uint8_t);

int main(){
    //set up PWMS for LED dimmage
    //8-bit Timer 0 used for green PWM 
        TCCR0B = (1<<CS01);                  //timer clock is CPU/8 (15kHz pwm)
        TCCR0B = (1<<WGM01)|(1<<WGM00);      //Fast pwm mode p.108
        TCCR0B = (1<<COM0B1);                //clear on compare match
    //16-bit Timer 1 used as blue PWM on OC1B PB2 (Arduino pin 10) p.115
    //noninverting fast PWM mode p135 
        TCCR1B = (1<<CS11)|(1<<WGM12);                    // clk/8; fast pwm
        TCCR1A = (1<<COM1B1)|(1<<WGM10);                  //TOP=0xFF; fast pwm
    //8 bit Timer 2 for red PWM 
        TCCR2B = (1<<CS21);                  //timer clock is CPU/8 (15kHz pwm)
        TCCR2B = (1<<WGM21)|(1<<WGM20);      //Fast pwm mode p.160
        TCCR2B = (1<<COM2B1);                //clear on compare match
    PORTB = 0xFF;
    DDRB = 0b000100100;              //LED on PB5; OC1B is PB2
    PORTB|=1<<5;                     //turn on LED
    adc_init();
    /****************************************
    *****main loop***************************
    ****************************************/
    for(;;){  
        OCR0A=adc_read_8bit(0);     //set green 
        OCR1A=adc_read_8bit(1);     //set blue 
        OCR2A=adc_read_8bit(2);     //set red
   } //infty
}//main
