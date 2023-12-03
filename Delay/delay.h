#ifndef _DELAY_H_
#define _DELAY_H_

/**
 * caculate time delay using crystal frequency
 *
 * @param crystal frequency
*/
void delay_init(unsigned long);

/**
 * delay miliseconds
 *
 * @param milisecond
*/
void delay(unsigned int);


#endif // _DELAY_H_