/*
 * four.c
 *
 * Created: 2016-03-30 ���� 9:54:49
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

DDRA = 0xff;        //PAx ��Ʈ ���� �����Ʈ ����
DDRD = 0x00;        //PDx ��Ʈ ���� �Է���Ʈ ����
EIMSK = 0x01;		//PD0 ��Ʈ ���ͷ�Ʈ Enable
EICRA = 0x02;		//PD0 �ϰ��� ����
SREG = 0x80;	    //���ͷ�Ʈ Ȱ��
i = 0x00;
    while(1){   
       /* if(i >= 99){
            i= 0x00;
        }
        PORTA = (((i / 10) << 4) | (i % 10));
        delay_ms(1);*/
    }
}
