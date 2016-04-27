/*
 * seven_first.c
 *
 * Created: 2016-04-19 오후 2:04:36
 * Author: GyungDal
 */

/*
 * seven_first.c
 *
 * Created: 2016-04-19 오후 2:04:36
 * Author: GyungDal
 */

#include <io.h>
#include <delay.h>

#define H 1
#define L 0

#define TRUE 1
#define FALSE 0

#define RS PORTB.0
#define RW PORTB.1
#define E PORTB.2
#define DATA PORTD

#define INTERFACE_8BIT 0x30
#define INTERFACE_4BIT 0x20
#define LINE_1 0x20
#define LINE_2 0x28

unsigned char FUNCTION_SET = INTERFACE_8BIT | LINE_2;

#define LEFT_SHIFT 0x07
#define RIGHT_SHIFT 0x05
#define SHIFT_OFF 0x00

unsigned char ENTRY_SET = RIGHT_SHIFT;

#define DISPLAY_ON 0x0c
#define DISPLAY_OFF 0x08
#define CUSER_ON 0x0a
#define CURSER_OFF 0x08
#define CURSER_BLANK_ON 0x09
#define CURSER_BLANK_OFF 0x08

unsigned char DISPLAY_SET = DISPLAY_ON | CURSER_OFF | CURSER_BLANK_OFF;

#define CLEAR 0x01
#define RETURN_HOME 0x02

void portSet(void){
    DDRB = 0xff;
    DDRD = 0xff;

    PORTB = 0x00;
    PORTD = 0x00;                 
}

void instructionSet(unsigned char data){
    RS = L;
    RW = L;
    delay_ms(1);
    E = H;
    DATA = data;
    delay_ms(1);
    E = L;
    RS = L;
    RW = L;
    delay_ms(1);
}

void charPosition(int x, int y){
    unsigned char position;
    if(y > 1) y = 1;
    if(x > 15) x = 15;
    position = y ? x + 0xc0 : x + 0x80;
    instructionSet(position);
}

void charDisplay(char display){
    RW = L;
    RS = H;      
    delay_ms(1);
    E = H;      
    delay_ms(1);
    DATA = display;
    delay_ms(1);   
    RW = L;
    RS = H;
    E = L;
    delay_ms(1); 
}

void stringDisplay(char* str){
    while(*str){
        charDisplay(*(str++));
    }
}

void initLCD(void){
    delay_ms(15);
    instructionSet(FUNCTION_SET);
    instructionSet(DISPLAY_SET);
    instructionSet(CLEAR);
}

void main(void){
    char *str = "TEST!!!";
    portSet();
    initLCD();
    
    charPosition(0,0);
    stringDisplay(str);
    while(TRUE){
    }
}