/*
 * four_two.c
 *
 * Created: 2016-03-30 오후 12:13:03
 * Author: GyungDal
 */

#include <io.h>
#include <interrupt.h>
unsigned char i, count;
//1/16us*1024분주*(256-) = 16.384
interrupt [TIM0_OVF] void timer_int0(void){
    TCNT0 = 0x00;             
    if(count++ == 6){
        count = 0x00;
        if(i++ >= 99)
            i = 0x00;
        PORTA = (((i / 10) << 4) | (i % 10));                                                       
    }
}
void main(void){
DDRA = 0xff;
i = 0x00;
count = 0x00;
TIMSK = 0x01;
TCCR0 = 0x07;   //1024분주
TCNT0 = 0x00;
SREG = 0x80;   //모든 레지스터 활성화 

while(1);

}
