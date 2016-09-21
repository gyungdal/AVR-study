/*
 * time.c
 *
 * Created: 2016-06-07 오후 3:08:19
 * Author: 김경식007
 */

/*
 * five.c
 *
 * Created: 2016-04-05 오후 1:49:19
 * Author: GyungDal
 */

//Header
#include <io.h>
#include <delay.h>  
#include <interrupt.h>

//Time value 00 ~ 99
unsigned char i, num;

//Timer Interrupt 
interrupt [TIM0_COMP] void timer(void){
        if(i++ >= 50){
            if(num++ > 10)
                num = 0x00;
            i= 0x00;
        }
        PORTA = num;
}

//Main Initial work
void main(void){
    DDRA = 0xff;        //PAx 포트 전부 출력포트 설정
    SREG = 0x80;        //인터럽트 활성
    TIMSK = 0x02;       //타이머 인터럽트 Enable
    TCNT0 = 0x00;       //타이머/카운터0 레지스터 초기값
    TCCR0 = 0x0f;       //CTC모드, 1024분주
    OCR0 = 155;         //출력비교 레지스터값(9.98ms)
    num = i = 0x00;
    PORTA = (((i / 10) << 4) | (i % 10));
}