/*
 * five_three.c
 *
 * Created: 2016-04-06 오전 10:21:31
 * Author: GyungDal
 */

//Header
#include <io.h>
#include <delay.h>  
#include <interrupt.h>

unsigned int i, p;

//Main Initial work
void main(void){
    DDRA = 0xff;
    DDRF = 0x00;  
    DDRF = 0; // 포트 F 입력
    ADMUX = 0; // 단일 변환모드의 ADC0 입력,
    ADCSRA = 0x87;
    while(1){
        ADCSRA = ADCSRA | 0x40;
        while((ADCSRA & 0x10)== 0);
        i = (int)ADCL + ((int)ADCH<<8); 
        p = (int)((i/1023.0) * 50);
        PORTA = (((p/10) << 4) | (p %10));
        delay_ms(100);
    }
}
