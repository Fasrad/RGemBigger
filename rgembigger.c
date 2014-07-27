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
        TCCR0B = (1<<CS22)|(1<<CS21)|(1<<CS20);                //CPU/1024; 2Hz
    //16-bit Timer 1 used as blue PWM on OC1B PB2 (Arduino pin 10) p.115
    //noninverting phase correct, CTC-PWM hybrid mode p135 
        TCCR1A = (1<<COM1B1)|(1<<WGM11)|(1<<WGM10); 
        OCR1A = 0x0FF0;             //sets pwm TOP 
        OCR1B = 0;
        TCCR1B = (1<<WGM13)|(1<<CS10);                 //  clk/1; 240kHz
        CLKPR = 0x80; CLKPR = 0;                       //  clk*8; 2kHz
    //8 bit Timer 2 for red PWM 
        TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);                //CPU/1024; 2Hz
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
