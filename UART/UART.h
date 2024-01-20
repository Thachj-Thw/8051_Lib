#ifndef _UART_H_
#define _UART_H_
///#include "main.h"


#ifndef	XTAL_FREQ
#define XTAL_FREQ				22118400ul
#endif


#define UART_read(s)							_UART_read(s, sizeof(s) / sizeof(s[0]))

#define UART_read_until(s, c) 		_UART_read_until(s, sizeof(s) / sizeof(s[0]), c)

/**
 * initialize UART
 * 
 * @param baud rate
 * @return null
 */
void UART_init(unsigned int);


/**
 * put a char to Serial
 *
 * @param char to put
 * @return null
 */
void UART_putchar(char);

/**
 * get a char from Serial and put to buffer paramenter
 * not return until readed a char
 * 
 * @param buffer
 * @return null
 */
void UART_getchar(char*);


/**
 * Send array of char to Serial
 * 
 * @param char pointer or char array to send
 * @return null
 */
void UART_print(char*);


/**
 * Send array of char to Serial and put \r\n at end
 * 
 * @param char pointer or char array to send
 * @return null
 */
void UART_println(char*);


/**
 * get max len of char from Serial and put to buffer
 * 
 * @param buffer char array to save data
 * @param maxlen max length to read (defaut length of buffer)
 * @return number of char readed, 0 if no data to read
 */
int _UART_read(char[], int);


/**
 * get max len of char from Serial and put to buffer until readed char end
 * not return until readed char end
 * 
 * @param buffer	char array to save data
 * @param maxlen	max length to read (defaut length of buffer)
 * @param end			char end of reading
 * @return number of char readed
 */
int _UART_read_until(char[], int, char);


/**
 * check Serial had data to read
 * 
 * @param null
 * @return 0 if no data to read, 1 if had data
 */
bit UART_available(void);


/**
 * Clear serial buffer
 * 
 * @param null
 * @return null
 */
void UART_clear(void);

#endif	// _UART_H_