/*
 * six.c
 *
 * Created: 2016-04-12 ¿ÀÈÄ 3:39:23
 * Author: GyungDal
 */

#include <io.h>
#include <delay.h>
void main(void){
int value = 0;
DDRA = 0x01;
ADMUX = 0x06;
ADCSRA = 0x87; 
while (1) {
    ADCSRA = 0xC7;
    while((ADCSRA & 0x10) == 0);
    value = (int)ADCL + ((int)ADCH << 8);
    if(value < 512) 
        PORTA = 0x01;
    else PORTA = 0x00;
    delay_ms(2);
    }
}
