#include "AT24C3x.h"
#include "i2c.h"


static unsigned char stream_device_address;
static unsigned int stream_next_rom_address;

static bit send_control_byte(unsigned char device_addr, unsigned int rom_addr)
{
	if (i2c_start_transmit(device_addr))
		return 1;
	if (i2c_transmit(rom_addr >> 8))
		return 1;
	return i2c_transmit(rom_addr & 0x00ff);
}


void AT24C3x_write(unsigned char device_addr, unsigned int rom_addr, unsigned char _data)
{
	if (rom_addr > 0xffff)
		return;
	send_control_byte(device_addr, rom_addr);
	i2c_transmit(_data);
	i2c_stop();
}


unsigned char AT24C3x_read(unsigned char device_addr, unsigned int rom_addr)
{
	unsigned char buffer;
	if (rom_addr > 0xffff)
		return '\0';
	send_control_byte(device_addr, rom_addr);
	i2c_start_receive(device_addr);
	buffer = i2c_receive();
	i2c_nack();
	i2c_stop();
	return buffer;
}


void AT24C3x_write_array(unsigned char device_addr, unsigned int rom_addr, unsigned char* _data, unsigned int len)
{
	bit nack;
	unsigned int i, next_addr;
	if (rom_addr > 0xffff)
		return;
	next_addr = rom_addr;
	send_control_byte(device_addr, rom_addr);
	for (i=0; i<len; i++)
	{
		if (_data[i] == '\0')
			break;
		i2c_transmit(_data[i]);
		next_addr++;
		if ((next_addr & 0x00ff) == 0x0000)
		{
			i2c_stop();
			nack = send_control_byte(device_addr, next_addr);
			while (nack)
				nack = send_control_byte(device_addr, next_addr);
		}
	}
	i2c_stop();
}


void AT24C3x_read_array(unsigned char device_addr, unsigned int rom_addr, unsigned char* buffer, unsigned int len)
{
	unsigned int i;
	if (rom_addr > 0xffff)
		return;
	send_control_byte(device_addr, rom_addr);
	for (i=0; i<len; i++)
	{
		i2c_start_receive(device_addr);
		buffer[i] = i2c_receive();
		i2c_nack();
	}
	i2c_stop();
}

void AT24C3x_start_stream(unsigned char device_addr, unsigned int rom_addr)
{
	if (rom_addr > 0xffff)
		return;
	stream_device_address = device_addr;
	stream_next_rom_address = rom_addr;
	send_control_byte(stream_device_address, rom_addr);
}


void AT24C3x_stream_write(unsigned char _data)
{
	bit nack;
	i2c_transmit(_data);
	stream_next_rom_address++;
	if ((stream_next_rom_address & 0x00ff) == 0x0000)
	{
		i2c_stop();
		nack = send_control_byte(stream_device_address, stream_next_rom_address);
		while (nack)
			nack = send_control_byte(stream_device_address, stream_next_rom_address);
	}
}


unsigned char AT24C3x_stream_read(void)
{
	unsigned char buf;
	i2c_start_receive(stream_device_address);
	buf = i2c_receive();
	i2c_nack();
	return buf;
}


void AT24C3x_stop_stream(void)
{
	i2c_stop();
}