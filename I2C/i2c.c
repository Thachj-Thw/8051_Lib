#include "i2c.h"


static void delay(void)
{
	unsigned char i;
	for (i=0; i<I2C_DELAY; i++);
}

void i2c_start()
{
	I2C_SCL = 1;
	I2C_SDA = 1;
	delay();
	I2C_SDA = 0;
	delay();
	I2C_SCL = 0;
}

void i2c_stop()
{
	I2C_SDA = 0;
	delay();
	I2C_SCL = 1;
	delay();
	I2C_SDA = 1;
	delay();
}

void i2c_ack()
{
	I2C_SDA = 0;
	delay();
	I2C_SCL = 1;
	delay();
	I2C_SCL = 0;
}

void i2c_nack()
{
	I2C_SDA = 1;
	delay();
	I2C_SCL = 1;
	delay();
	I2C_SCL = 0;
}

bit i2c_transmit(unsigned char _data)
{
	bit ACK;
	char i;
	for (i = 7; i >= 0; i--)
	{
		I2C_SDA = (_data >> i) & 0x01;
		delay();
		I2C_SCL = 1;
		delay();
		I2C_SCL = 0;
	}
	delay();
	I2C_SCL = 1;
	ACK = I2C_SDA;
	delay();
	I2C_SCL = 0;
	return ACK;
}

unsigned char i2c_receive()
{
	char i;
	unsigned char _data;
	_data = 0x00;
	for (i = 7; i > 0; i--)
	{
		delay();
		I2C_SCL = 1;
		_data = (_data | I2C_SDA) << 1;
		delay();
		I2C_SCL = 0;
	}
	delay();
	I2C_SCL = 1;
	_data |= I2C_SDA;
	delay();
	I2C_SCL = 0;
	return _data;
}

bit i2c_start_transmit(unsigned char device_adr)
{
	i2c_start();
	return i2c_transmit(device_adr << 1);
}

bit i2c_start_receive(unsigned char device_adr)
{
	i2c_start();
	return i2c_transmit((device_adr << 1) | 0x01);
}
