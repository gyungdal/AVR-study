/*
 * two_homework.c
 *
 * Created: 2016-03-23 ¿ÀÈÄ 6:10:16
 * Author: GyungDal
 */
 #include <io.h>
#include <delay.h>  
unsigned char i;

void main(void){
DDRA = 0xff;        
i = 0x00;
    while(1){
        if(i++ >= 100){
            i= 0x00;
        }
        PORTA = (((i / 10) << 4) | (0x0F & (i % 10)));
        delay_ms(300);
    }
}
