/*
 * seven_two.c
 *
 * Created: 2016-04-20 ¿ÀÀü 10:37:25
 * Author: GyungDal
 */

#include <io.h>
#include <lcd.h>
#include <delay.h>
#include <stdio.h>

#asm
    .equ __lcd_port = 0x12
#endasm

unsigned char key(void);
void key_scan(void);
unsigned char key_value;                                                                        

void main(void){
    unsigned char sbuf[10];
    DDRA = 0x0f;
    SFIOR = 0x00;
    PORTA = 0xff;
    lcd_init(16);
    lcd_gotoxy(0,0);
    lcd_puts("4x4 Keypad");
    lcd_gotoxy(0,1);
    
    while(1){
        key_scan();
        if(key_value != 0xf0){
            sprintf(sbuf, "%d", key_value);
            lcd_puts(sbuf);       
        }
    }
}

unsigned char key(void){
    unsigned char a, key_buf;
    unsigned char row = 0xfe;
    PORTA = 0xff;
    for(a = 0;a<4;a++){
        PORTA = row;
        delay_us(20);
        key_buf = PINA;
        switch(PINA){
            case 0xd7 : key_buf = 0x00; break;
            case 0xee : key_buf = 0x01; break;
            case 0xde : key_buf = 0x02; break;
            case 0xbe : key_buf = 0x03; break;
            case 0xed : key_buf = 0x04; break;
            case 0xdd : key_buf = 0x05; break;
            case 0xbd : key_buf = 0x06; break;
            case 0xeb : key_buf = 0x07; break;
            case 0xdb : key_buf = 0x08; break;
            case 0xbb : key_buf = 0x09; break;
            case 0x7e : key_buf = 0x0a; break;
            case 0x7d : key_buf = 0x0b; break;
            case 0x7b : key_buf = 0x0c; break;
            case 0x77 : key_buf = 0x0d; break;
            case 0xe7 : key_buf = 0x0f; break;
            case 0xb7 : key_buf = 0x10; break;
        }
        if(key_buf != 0xf0) return key_buf;
        row =(row<<1)|0x01;
    }
    return key_buf;
}

void key_scan(void){
    key_value = key();
    if(key_value != 0xf0){
        while(key() != 0xf0);
    }
}