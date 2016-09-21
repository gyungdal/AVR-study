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
    .equ __lcd_port = 0x18
#endasm

void main(void){
    DDRC=0xff;
    
    lcd_init(16);
    lcd_gotoxy(0,0);
    lcd_puts("chogyus");

}
