#ifndef _DELAY_H_
#define _DELAY_H_
#include "main.h"

#ifndef XTAL_FREQ
#define XTAL_FREQ 12000000ul // crystal frequency
#endif //XTAL_FREQ

/**
 * delay miliseconds
 *
 * @param milisecond
*/
void delay(unsigned int);


#endif // _DELAY_H_