/*
 * five.c
 *
 * Created: 2016-04-05 오후 1:49:19
 * Author: GyungDal
 */                                    
/*
//Header
#include <io.h>
#include <delay.h>  
#include <interrupt.h>

//Time value 00 ~ 99
unsigned char i, num;
              //  COMP
//Timer Interrupt 
interrupt [TIM0_OVF] void timer(void){
    TCNT0 = 0x00;
    if(i++ == 31){
        if(num++ > 10) {
            num = 0x00; 
        }
        PORTA = num;
        i = 0x00;
    }
}                       

//Main Initial work
void main(void){
    i = num = 0x00;        
    DDRA = 0xff;        //PAx 포트 전부 출력포트 설정
    TIMSK = 0x01;
    TCCR0 = 0x07;
    TCNT0 = 0x00;
    SREG = 0x80;
    while(1){
        //Somethine?
    }
}                                  
*/  
       
#include <io.h>
int value;
void main(void){
    DDRA = 0xff;
    ADCSRA = 0x87;
    ADMUX = 0x00;
    while(1){
        ADCSRA = ADCSRA | 0x40;
        while((ADCSRA & 0x10) == 0);
        value = (((int)ADCL+((int)ADCH<<8)/1023.0)*9);
        PORTA = value % 10;
    }
}