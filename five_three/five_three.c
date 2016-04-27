/*
 * five_three.c
 *
 * Created: 2016-04-06 ���� 10:21:31
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
    DDRF = 0; // ��Ʈ F �Է�
    ADMUX = 0; // ���� ��ȯ����� ADC0 �Է�,
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
