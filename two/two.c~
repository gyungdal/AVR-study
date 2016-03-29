/*
 * two.c
 *
 * Created: 2016-03-23 ¿ÀÀü 8:59:05
 * Author: GyungDal
 */

#include <io.h>
#include <delay.h>
const char data[10] = {0x3f ,0x06, 0x5b, 0x4f,
                0x66, 0x6d, 0x7d, 0x07, 0x7f,
                0x67};  
unsigned char i;

void main(void){
DDRA = 0xff;        
i = 0x00;
    while(1){
         if(i++ >= 0x09)
            i = 0x00;
         PORTA = i; 
         delay_ms(400);
    }
}
