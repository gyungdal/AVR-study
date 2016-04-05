/*
 * five_two.c
 *
 * Created: 2016-04-05 ���� 4:06:44
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
    DDRA = 0xff;        //PAx ��Ʈ ���� �����Ʈ ����
    DDRD = 0x00;        //PDx ��Ʈ ���� �Է���Ʈ ����
    EIMSK = 0x0f;        //PD0 ��Ʈ ���ͷ�Ʈ Enable
    EICRA = 0xff;        //PD0 �ϰ��� ����
    SREG = 0x80;        //���ͷ�Ʈ Ȱ��
    i = 0x00;   
    PORTA = (((i / 10) << 4) | (i % 10));
}