/*
 * UART.c
 *
 * Created: 2016-11-09 ¿ÀÀü 11:26:14
 * Author: ±è°æ½Ä007
 */

#include <io.h>
#include <delay.h>
#include <stdio.h>
#include <lcd.h>

#asm
    .equ __lcd_port = 0x1b
#endasm
void putch(char);
char getch();
void lcd_display(char data);

char* test = "GyungDal";
char temp[16];
void main(void){
    lcd_init(16);
    lcd_clear(); 
    lcd_gotoxy(0,0); 
    lcd_puts("TEST!!!");
    UCSR0A = 0x0;
    UCSR0B = 0b00011000;
    UCSR0C = 0b00000110;
    UBRR0H = 0x0;
    UBRR0L = 103;      
     
   while(*test){
        putch(*test++);
        lcd_display(getch());
        delay_ms(100);
    }
}


void putch(char data){
    while(!(UCSR0A & 0x20));
    UDR0 = data;
}

char getch(){
    while(!(UCSR0A & 0x80));
    return UDR0;
}

                            
void lcd_display(char data){
    lcd_gotoxy(0,1);
    lcd_putchar(data);
}