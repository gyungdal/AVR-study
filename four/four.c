/*
 * four.c
 *
 * Created: 2016-03-30 오전 9:54:49
 * Author: GyungDal
 */


#include <io.h>
#include <delay.h>  
#include <interrupt.h>
unsigned char i;
interrupt [EXT_INT0] void external_int0(void){
   if(i++ >= 99){
            i= 0x00;
        }
        PORTA = (((i / 10) << 4) | (i % 10));
}
void main(void){

DDRA = 0xff;        //PAx 포트 전부 출력포트 설정
DDRD = 0x00;        //PDx 포트 전부 입력포트 설정
EIMSK = 0x01;		//PD0 포트 인터럽트 Enable
EICRA = 0x02;		//PD0 하강시 실행
SREG = 0x80;	    //인터럽트 활성
i = 0x00;
    while(1){   
       /* if(i >= 99){
            i= 0x00;
        }
        PORTA = (((i / 10) << 4) | (i % 10));
        delay_ms(1);*/
    }
}
