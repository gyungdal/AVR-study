/*
 * sr04.c
 *
 * Created: 2016-09-06 ¿ÀÈÄ 2:44:42
 * Author: ±è°æ½Ä007
 */

#include <io.h>
#include <delay.h>   
#include <lcd.h>
#include <stdio.h>
#define TRIGGER PORTD.1
#asm
    .equ __lcd_port = 0x1b 
#endasm      


char str_value[16];
int catch,distance;
void main(void){
    DDRD = 0b00000010;
    TRIGGER = 0;
    EIMSK = 0x01;
    EICRA = 0x02;
    TIMSK = 0x01;
    TCCR0 = 0x0;                                  
    lcd_init(16);
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts("GyungDal");       
    while(1){
        SREG = 0x0;      
        TIFR = 0xff;
        ASSR = 0x0;
        catch = 0;
        TCNT0 = 139;
        TRIGGER = 1;
        delay_ms(1);
        TRIGGER = 0;
        distance = 0;             
        while(1){
            if(catch == 1 || distance >= 300)
                break;
        }
        lcd_clear();                              
        lcd_gotoxy(6,1);   
        sprintf(str_value, "%03d", distance);             
        lcd_puts(str_value);
    }
}

interrupt [TIM0_OVF] void timer_int0(void){
    TCNT0 = 139;
    distance++;
}

interrupt [EXT_INT0] void external_int0(void){
    TCCR0 = 0x0;
    catch = 1;
}