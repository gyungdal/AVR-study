/*
 * five.c
 *
 * Created: 2016-04-05 ���� 1:49:19
 * Author: GyungDal
 */


#include <io.h>
#include <delay.h>  
#include <interrupt.h>
unsigned char i;
interrupt [EXT_INT0] void external_int0(void){
   if(TIMSK == 0x02){ 
        TIMSK = 0x00;
   }else TIMSK = 0x02;
}
interrupt [TIM0_COMP] void timer(void){
         if(i++ >= 99){
            i= 0x00;
        }
        PORTA = (((i / 10) << 4) | (i % 10));
}
void main(void){
    DDRA = 0xff;        //PAx ��Ʈ ���� �����Ʈ ����
    DDRD = 0x00;        //PDx ��Ʈ ���� �Է���Ʈ ����
    EIMSK = 0x01;        //PD0 ��Ʈ ���ͷ�Ʈ Enable
    EICRA = 0x02;        //PD0 �ϰ��� ����
    SREG = 0x80;        //���ͷ�Ʈ Ȱ��
    TIMSK = 0x02;       //Ÿ�̸� ���ͷ�Ʈ Enable
    TCNT0 = 0x00;       //Ÿ�̸�/ī����0 �������� �ʱⰪ
    TCCR0 = 0x0f;       //CTC���, 1024����
    OCR0 = 155;         //��º� �������Ͱ�(9.98ms)
    i = 0x00;
    PORTA = (((i / 10) << 4) | (i % 10));
}