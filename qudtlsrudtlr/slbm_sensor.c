/*
 * slbm_sensor.c
 *
 * Created: 2016-09-06 오후 3:00:56
 * Author: Continue
 */

#include <io.h>
#include <delay.h>
#include <stdio.h>

#asm
    .equ __lcd_port = 0x1b
#endasm
#include <lcd.h>

#define TRIGGER PORTD.1

unsigned short temp;
int count, distance, catch, speed, key, i;    
char Info[16], arrow;
void lcd_display();

void main(void)
{
    DDRC = 0x00;
    DDRA = DDRE = DDRB = 0xff;
    TCCR1A = 0xa3;
    TCCR1B = 0x05; 
    TCCR3A = 0xa3;
    TCCR3B = 0x05;
    SREG = 0x80;  
    ADCSRA = 0x87;
    DDRD = 0b00000010;
    count = TRIGGER = 0;
    
    EIMSK = 0b00000001;
    EICRA = 0b00000010;       
    
    TIMSK = 0x01;
    TCCR0 = 0x0;
    lcd_init(16);
    lcd_clear();
                   
    while (1) {                  
        ADMUX = 0x00;   
        ADCSRA=ADCSRA|0x40; //ADSC=1변환 시작
        while((ADCSRA&0x10)==0); //ADIF=1이 될떄까지
        speed = (int)((((int)ADCL+((int)ADCH<<8))/1024.0)*254); //A/D변환값 읽기 
        
        ADMUX = 0x01;   
        ADCSRA=ADCSRA|0x40; //ADSC=1변환 시작
        while((ADCSRA&0x10)==0); //ADIF=1이 될떄까지
        key = (int)((((int)ADCL+((int)ADCH<<8))/1024.0)*254); //A/D변환값 읽기 
                               
        ADCSRA = 0x87;
        TIFR = 0xff;
        ASSR = 0x0;
        TCNT0 = 139;
    
        TRIGGER = 1;
        delay_ms(1);
        distance = TRIGGER = 0;
        
        TCCR0 = 0x02;
   
        catch = 0;
        
        while(1){
            if(catch == 1) break;
            else if(distance >= 300) break;
        }    
        
        if(count++ < 5000){
            lcd_display();   
            count = 0;
        }       
        arrow = (PINC.0 & 1);
        arrow = !arrow; 
        if(distance > 30){                          
            if(key <= 130 && key >= 120){
                if(arrow){
                    OCR1A = (speed % 255) * (speed % 255);
                    OCR1B = 0;   
                    OCR3BH = OCR1BH; 
                    OCR3BL = OCR1BL;
                    OCR3AH = OCR1AH; 
                    OCR3AL = OCR1AL;
                }else{
                    OCR1A = 0;
                    OCR1B =  (speed % 255) * (speed % 255);
                    OCR3AH = OCR1AH;
                    OCR3AL = OCR1AL;
                    OCR3BH = OCR1BH;
                    OCR3BL = OCR3BL;
                }      
            }else if(key > 130){          
                temp = 0xffff;
                if(arrow){                                      
                    //OCR1A = temp;                                  
                    OCR3AH = (temp >> 8); 
                    OCR3AL = temp;     
                    //temp = (speed % 255) * (speed % 255);       
                    OCR3BH = OCR3BL = 0;
                    OCR1B = OCR1A = 0x0;
                }else{
                    //OCR1B = temp;  
                    OCR3BH = (temp >> 8); 
                    OCR3BL = temp;      
                    //temp = (speed % 255) * (speed % 255);  
                    OCR3AH = OCR1BH; 
                    OCR3AL = OCR1BL;       
                    OCR1B = OCR1A = 0x0;
                    //OCR3BH = (temp >> 8); 
                    //OCR3BL = ((temp << 8) >> 8); 
                }
            }else{                                        
            temp = (speed % 255) * (speed % 255);
                if(arrow){                                      
                    //OCR1A = temp;  
                    OCR1A = temp;
                    OCR3AH = OCR3AL = 0x0;                                
                    //temp = (speed % 255) * (speed % 255);       
                    OCR1B = 0;   
                    OCR3BH = OCR3AH; 
                    OCR3BL = OCR3AL;
                    //OCR3AH = (temp >> 8); 
                    //OCR3AL = ((temp << 8) >> 8);     
                }else{
                    //OCR1B = temp;
                    OCR1B = temp;
                    //OCR3BH = (temp >> 8); 
                    //OCR3BL = ((temp << 8) >> 8);        
                    //temp = (speed % 255) * (speed % 255);  
                    OCR1A = 0;
                    OCR3AH = OCR3AL = OCR3BH = OCR3BL = 0x0; 
                }    
            }   
        }else{       
            OCR1A = 0;
            OCR1B = 0;
            OCR3BH = OCR1BH; 
            OCR3BL = OCR1BL;
            OCR3AH = OCR1AH; 
            OCR3AL = OCR1AL;     
            delay_ms(1000);
        }   
    }
}    

void lcd_display()
{   
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts("DIS, SPE, ANG");
    lcd_gotoxy(0,1);
    sprintf(Info, "%3d, %3d, %3d %d",distance, speed, key, PINC);
    lcd_puts(Info); 
    
}

interrupt [TIM0_OVF] void timer_int0(void){
    TCNT0 = 139;
    distance++;
}

interrupt [EXT_INT0] void external_int0(void)
{

    TCCR0 = 0x0;
    catch = 1;
}
