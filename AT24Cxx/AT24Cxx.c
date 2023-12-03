#include "AT24Cxx.h"
#include "i2c.h"

void AT24Cxx_write(unsigned char device_addr, unsigned int rom_addr, unsigned char _data)
{
	if (rom_addr > 0xffff)
		return;
	i2c_start_transmit(device_addr);
	i2c_transmit(rom_addr >> 8);
	i2c_transmit(rom_addr & 0x00ff);
	i2c_transmit(_data);
	i2c_stop();
}

unsigned char AT24Cxx_read(unsigned char device_addr, unsigned int rom_addr)
{
	unsigned char buffer;
	if (rom_addr > 0xffff)
		return '\0';
	i2c_start_transmit(device_addr);
	i2c_transmit(rom_addr >> 8);
	i2c_transmit(rom_addr & 0x00ff);
	i2c_start_receive(device_addr);
	buffer = i2c_receive();
	i2c_nack();
	i2c_stop();
	return buffer;
}

void AT24Cxx_write_array(unsigned char device_addr, unsigned int rom_addr, unsigned char* _data, unsigned int len)
{
	unsigned int i, j, next_addr;
	if (rom_addr > 0xffff)
		return;
	next_addr = rom_addr + 1;
	i2c_start_transmit(device_addr);
	i2c_transmit(rom_addr >> 8);
	i2c_transmit(rom_addr & 0x00ff);
	i2c_transmit(_data[0]);
	for (i=1; i<len; i++)
	{
		if (_data[i] == '\0')
			break;
		if ((next_addr & 0x00ff) == 0x0000)
		{
			i2c_stop();
			for (j = 0; j < 12300; j++); //delay
			i2c_start_transmit(device_addr);
			i2c_transmit(next_addr >> 8);
			i2c_transmit(next_addr & 0x00ff);
		}
		i2c_transmit(_data[i]);
		next_addr++;
	}
	i2c_stop();
}

void AT24Cxx_read_array(unsigned char device_addr, unsigned int rom_addr, unsigned char* buffer, unsigned int len)
{
	unsigned int i, j;
	if (rom_addr > 0xffff)
		return;
	i2c_start_transmit(device_addr);
	i2c_transmit(rom_addr >> 8);
	i2c_transmit(rom_addr & 0x00ff);
	i2c_start_receive(device_addr);
	for (i=0; i<len-1; i++)
	{
		buffer[i] = i2c_receive();
		i2c_ack();
	}
	buffer[i] = i2c_receive();
	i2c_nack();
	i2c_stop();
}
