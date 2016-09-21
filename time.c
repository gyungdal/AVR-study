/*
 * time.c
 *
 * Created: 2016-06-07 ���� 3:08:19
 * Author: ����007
 */

/*
 * five.c
 *
 * Created: 2016-04-05 ���� 1:49:19
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
    DDRA = 0xff;        //PAx ��Ʈ ���� �����Ʈ ����
    SREG = 0x80;        //���ͷ�Ʈ Ȱ��
    TIMSK = 0x02;       //Ÿ�̸� ���ͷ�Ʈ Enable
    TCNT0 = 0x00;       //Ÿ�̸�/ī����0 �������� �ʱⰪ
    TCCR0 = 0x0f;       //CTC���, 1024����
    OCR0 = 155;         //��º� �������Ͱ�(9.98ms)
    num = i = 0x00;
    PORTA = (((i / 10) << 4) | (i % 10));
}