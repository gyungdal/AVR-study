/*
 * first.c
 *
 * Created: 2016-03-16 ���� 11:22:48
 * Author: GyungDal
 */
 
#include <io.h>
#include <delay.h>
const char data[10] = {0x3f ,0x06, 0x5b, 0x4f,
                0x66, 0x6d, 0x7d, 0x07, 0x7f,
                0x67};

void main(void){
DDRA = 0xff;         
          PORTA = 0xff;
    /*while (1){     
        for(i=0; i<10; i++){
            PORTA = ~data[i];
            delay_ms(1000);
        }        
    }      */
}
