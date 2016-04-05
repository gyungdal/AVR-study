/*
 * five_two.c
 *
 * Created: 2016-04-05 오후 4:06:44
 * Author: GyungDal
 */



//Header
#include <io.h>
#include <delay.h>  
#include <interrupt.h>

//Time value 00 ~ 99
unsigned char i;

//Button0 Interrupt
interrupt [EXT_INT0] void button0(void){
    for(i = 1;i<10;i++){
         PORTA = (((i / 10) << 4) | (i % 10)); 
         delay_ms(100);
    }
}

//Button1 Interrupt
interrupt [EXT_INT1] void button1(void){
    for(i = 11;i<20;i++){
         PORTA = (((i / 10) << 4) | (i % 10)); 
         delay_ms(100);
    }
}

//Button2 Interrupt
interrupt [EXT_INT2] void button2(void){
    for(i = 21;i<30;i++){
         PORTA = (((i / 10) << 4) | (i % 10)); 
         delay_ms(100);
    }
}

//Button3 Interrupt
interrupt [EXT_INT3] void button3(void){
    for(i = 31;i<40;i++){
         PORTA = (((i / 10) << 4) | (i % 10)); 
         delay_ms(100);
    }
}
//Main Initial work
void main(void){
    DDRA = 0xff;        //PAx 포트 전부 출력포트 설정
    DDRD = 0x00;        //PDx 포트 전부 입력포트 설정
    EIMSK = 0x0f;        //PD0 포트 인터럽트 Enable
    EICRA = 0xff;        //PD0 하강시 실행
    SREG = 0x80;        //인터럽트 활성
    i = 0x00;   
    PORTA = (((i / 10) << 4) | (i % 10));
}