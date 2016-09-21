/*
 * motor.c
 *
 * Created: 2016-08-23 ���� 4:09:32
 * Author: ����007
 */

#include <io.h>
#include <delay.h>
#define M_A1 PORTB.2
#define M_A2 PORTB.3
#define M_B1 PORTB.4
#define M_B2 PORTB.5

void right();
void back();
void front();
void left();
void main(void){
DDRB = 0xff;
while (1){
        right();
        delay_ms(1000);
        left();
        delay_ms(1000);
        back();
        delay_ms(1000);
        front();
        delay_ms(1000);
    }
}
    // Front
    //A     B
void right(){
    M_A1 = 0x1;
    M_A2 = 0x0;
    M_B1 = 0x0;
    M_B2 = 0x1;    
}

void left(){   
    M_A1 = 0x0;
    M_A2 = 0x1;
    M_B1 = 0x1;
    M_B2 = 0x0;
}
void back(){   
    M_A1 = 0x0;
    M_A2 = 0x1;
    M_B1 = 0x0;
    M_B2 = 0x1;
}
void front(){  
    M_A1 = 0x1;
    M_A2 = 0x0;
    M_B1 = 0x1;
    M_B2 = 0x0;
}