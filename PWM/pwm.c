/*
 * pwm.c
 *
 * Created: 2016-08-30 오후 2:57:19
 * Author: 김경식007
 */

#include <io.h>
#include <delay.h>   
#include <lcd.h>
#include <stdio.h>

#asm
    .equ __lcd_port = 0x1b 
#endasm                
      
void SetTimer1(short A, short B){
    OCR1AL = ((A << 8) >> 16);
    OCR1AH = (A >> 8);        
    OCR1BL = ((B << 8) >> 16);
    OCR1BH = (B >> 8); 
}

void SetTimer3(short A, short B){
    OCR3AL = ((A << 8) >> 16);
    OCR3AH = (A >> 8);        
    OCR3BL = ((B << 8) >> 16);
    OCR3BH = (B >> 8); 
}

char str_value[16];
int value, key;
void main(void){        
    DDRF = 0xf0;
    DDRA = DDRE = DDRB = 0xff;
//    TCCR0 = 0x7d;
    TCCR1A = 0xa3;
    TCCR1B = 0x05; 
    TCCR3A = 0xa3;
    TCCR3B = 0x05;
    SREG = 0x80;  
    ADCSRA = 0x87;
    //OCR0 = 0; // 정지       
    SetTimer3(0,0);
    SetTimer1(0,0);
                  
    //lcd_init(16);  
    //lcd_clear(); 
    //lcd_gotoxy(6,1); 
    while (1){         
        ADMUX = 0x00;   
        ADCSRA=ADCSRA|0x40; //ADSC=1변환 시작
        while((ADCSRA&0x10)==0); //ADIF=1이 될떄까지
        value = (int)((((int)ADCL+((int)ADCH<<8))/1024.0)*254); //A/D변환값 읽기 
        
        ADMUX = 0x01;   
        ADCSRA=ADCSRA|0x40; //ADSC=1변환 시작
        while((ADCSRA&0x10)==0); //ADIF=1이 될떄까지
        key = (int)((((int)ADCL+((int)ADCH<<8))/1024.0)*254); //A/D변환값 읽기 
        
        //SetTimer1(255 * 255, 0);     
        //SetTimer3(0, 30000);    
        
        OCR1A = value * value;
        OCR1B = 0;          
        if(key > 128){
            OCR3BH = OCR1AH; 
            OCR3BL = OCR1AL;
            OCR3AH = OCR1BH; 
            OCR3AL = OCR1BL;   
        }else{
            OCR3BH = OCR1BH; 
            OCR3BL = OCR1BL;
            OCR3AH = OCR1AH; 
            OCR3AL = OCR1AL; 
        }
        
        //SetTimer1(100 * 100, 0);
        //SetTimer3(30000, 0); 
        //lcd_clear();            
        //lcd_gotoxy(6,1);
        //sprintf(str_value, "%03d, %03d", (255 - value), key);             
        //lcd_puts(str_value);
   }
}
