#ifndef	_I2C_H_
#define	_I2C_H_

#include <REGX51.H>
#include "main.h"

#ifndef I2C_SDA
#define I2C_SDA	P3_4
#endif	//I2C_SDA

#ifndef I2C_SCL
#define I2C_SCL	P3_5
#endif	//I2C_SCL

#ifndef I2C_DELAY
#define I2C_DELAY	250			// max 655535
#endif  //I2C_DELAY

/**
 * send start condition
*/
void i2c_start(void);

/**
 * send stop condition
*/
void i2c_stop(void);

/**
 * send bit ACK
*/
void i2c_ack(void);

/**
 * send bit NACK
*/
void i2c_nack(void);

/**
 * transmit data on SDA bus
 *
 * @param a byte to send
 * @return bit ACK from slave
*/
bit i2c_transmit(unsigned char);

/**
 * receive a byte from SDA bus
 *
 * @return byte readed from data bus
*/
unsigned char i2c_receive(void);

/**
 * send start condition, byte slave address and read/write bit = 0
 *
 * @param slave addreass
 * @return bit ACK from slave
*/
bit i2c_start_transmit(unsigned char);

/**
 * send start condition, byte slave address and read/write bit = 1
 *
 * @param slave addreass
 * @return bit ACK from slave
*/
bit i2c_start_receive(unsigned char);

#endif	//_I2C_H_