/*
 * first.c
 *
 * Created: 2016-04-05 ¿ÀÈÄ 7:45:25
 * Author: GyungDal
 */

#include <mega128a.h>

void main(void)
{
DDRA = 0xff;
while (1)
    {
        PORTA = 0xff;
    }
}
