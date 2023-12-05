/**
 * Library for 24CXXX and 24CXXXX
*/
#ifndef _AT24C3x_H_
#define _AT24C3x_H_

#ifndef I2C_SDA
#define I2C_SDA					P3_4
#endif	//I2C_SDA

#ifndef I2C_SCL
#define I2C_SCL					P3_5
#endif	//I2C_SCL

#ifndef I2C_DELAY
#define I2C_DELAY				10
#endif  //I2C_DELAY


/**
 * Write a byte to EEPROM
 * @note max memory address is 0xFFFF
 * 			 EEPROM I2C address not included R/W bit [0 1 0 1 0 A3 A2 A1]
 *
 * @param EEPROM I2C address
 * @param EEPROM memory address
 * @param byte data to write
*/
void AT24C3x_write(unsigned char, unsigned int, unsigned char);

/**
 * Read a byte from EEPROM
 * @note max memory address is 0xFFFF
 * 			 EEPROM I2C address not included R/W bit [0 1 0 1 0 A3 A2 A1]
 *
 * @param EEPROM I2C address
 * @param EEPROM memory address
 * @return a byte readed
*/
unsigned char AT24C3x_read(unsigned char, unsigned int);

/**
 * Write byte array to EEPROM
 * @note max memory address is 0xFFFF
 * 			 EEPROM I2C address not included R/W bit [0 1 0 1 0 A3 A2 A1]
 * 
 * @param EEPROM I2C address
 * @param EEPROM memory address start write
 * @param array of byte write to EEPROM
 * @param number of byte write to EEPROM
*/
void AT24C3x_write_array(unsigned char, unsigned int, unsigned char*, unsigned int);

/**
 * Read byte array from EEPROM
 * @note max memory address is 0xFFFF
 * 			 EEPROM I2C address not included R/W bit [0 1 0 1 0 A3 A2 A1]
 * 
 * @param EEPROM I2C address
 * @param EEPROM memory address start read
 * @param buffer save data read from EEPROM
 * @param number of byte read from EEPROM
*/
void AT24C3x_read_array(unsigned char, unsigned int, unsigned char*, unsigned int);

/**
 * Open bus and keep for read or write
 * @note max memory address is 0xFFFF
 * 			 EEPROM I2C address not included R/W bit [0 1 0 1 0 A3 A2 A1]
 *
 * @param EEPROM I2C address
 * @param start EEPROM memory address
*/
void AT24C3x_start_stream(unsigned char, unsigned int);

/**
 * Write a byte to bus
 *
 * @param a byte write to EEPROM
*/
void AT24C3x_stream_write(unsigned char);

/**
 * Read a byte from bus
 *
 * @return byte readed from EEPROM
*/
unsigned char AT24C3x_stream_read(void);


/**
 * Close bus
*/
void AT24C3x_stop_stream(void);

#endif //_EPR24C3x_H_