/*
 * lcd.c
 *
 * Created: 2016-08-16 오후 3:26:11
 * Author: 김경식007
 */


#include <io.h>
#include <lcd.h>
#include <delay.h>
#include <stdio.h>
#include <interrupt.h>  
#define sbi(port, bit) (port) |= (1 << (bit))
#define cbi(port, bit) (port) &= ~(1 << (bit))
#asm
    .equ __lcd_port = 0x1b 
#endasm                  
                   
#define RTC_PORT PORTE
#define RTC_PIN PINE
#define RTC_DDR DDRE
#define RTC_CLK 0
#define RTC_DAT 1
#define RTC_RST 2

#define ds1302_sec 0x80
#define ds1302_min (ds1302_sec + 0x02)
#define ds1302_hour (ds1302_min + 0x02)
#define ds1302_control 0x8e
#define ds1302_charger 0x90

unsigned char count, test[16];
char m, s, tmp;

unsigned char ds1302_read(unsigned char addr);  
void ds1302_write(char adr, char dat);


interrupt [TIM0_OVF] void timer_int0(void){
    TCNT0 = 0x00;  
    if(count++ == 30){
        count = 0x00;                               
        lcd_clear();
        lcd_gotoxy(5,0);
        lcd_puts("WATCH");       
        lcd_gotoxy(4,1);  
        
        tmp = ds1302_read(ds1302_min);
        m = (((tmp & 0x70) >> 4)*10) + (tmp & 0x0f);
        
        tmp = ds1302_read(ds1302_sec);                                                                                                          
        s = (((tmp & 0x70) >> 4)*10) + (tmp & 0x0f);
        sprintf(test, "%02d:%02d:%02d",s, s, s);
        lcd_puts(test);       
    }                        
}


void main(void){      
    DDRA = 0xff;
    count = 0x00;
    TIMSK = 0x01;
    TCCR0 = 0x07;   //1024분주
    TCNT0 = 0x00;
    SREG = 0x80;   //모든 레지스터 활성화 
    lcd_init(16);         
    ds1302_write(ds1302_control, 0x00);
    ds1302_write(ds1302_sec, 0x51);
    ds1302_write(ds1302_min, 0x59);
    ds1302_write(ds1302_hour, 0x11);
    ds1302_write(ds1302_control, 0x80);
    
    while(1);  
}


unsigned char ds1302_read(unsigned char addr) {
      char return_data = 0;
      int i = 0;
      
      addr += 1;
      sbi(RTC_DDR, RTC_DAT);
      sbi(RTC_PORT, RTC_RST);

      for(i = 0; i < 8; i++) {
            cbi(RTC_PORT, RTC_CLK);
            if (addr & 0x01) 
                  sbi(RTC_PORT, RTC_DAT);
            else 
                  cbi(RTC_PORT, RTC_DAT);
            
            sbi(RTC_PORT, RTC_CLK);
      
            addr >>= 1;
      }
      
      cbi(DDRC, RTC_DAT);
      
      for(i = 0; i < 8; i++) {
            cbi(RTC_PORT, RTC_CLK);
            if (RTC_PIN.RTC_DAT)
                  return_data |= 0x80;
            
            sbi(RTC_PORT, RTC_CLK);
            return_data >>= 1;
      }
         
      cbi(PORTC, RTC_CLK);
      cbi(PORTC, RTC_RST);
      
      return return_data;
}

void ds1302_write(char adr, char dat){
    char a;
    sbi(RTC_DDR, RTC_DAT);
    sbi(RTC_PORT, RTC_RST);
    
    for(a = 0;a<8;++a){
        cbi(RTC_PORT, RTC_CLK);
        if(adr & 0x1) 
            sbi(RTC_PORT, RTC_DAT);
        else   
            cbi(RTC_PORT, RTC_DAT);
        sbi(RTC_PORT, RTC_CLK);
        adr >>= 1;
    }
    
    for(a = 0;a<8;++a){
        cbi(RTC_PORT, RTC_CLK);
        if(dat & 0x1)
            sbi(RTC_PORT, RTC_DAT);
        else   
            cbi(RTC_PORT, RTC_DAT);
        sbi(RTC_PORT, RTC_CLK);
        dat >>= 1;
    }
    cbi(RTC_PORT, RTC_CLK);
    cbi(RTC_PORT, RTC_RST);
}     