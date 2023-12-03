#ifndef _EPR24Cxx_H_
#define _EPR24Cxx_H_

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
void AT24Cxx_write(unsigned char, unsigned int, unsigned char);

/**
 * Read a byte from EEPROM
 * @note max memory address is 0xFFFF
 * 			 EEPROM I2C address not included R/W bit [0 1 0 1 0 A3 A2 A1]
 *
 * @param EEPROM I2C address
 * @param EEPROM memory address
 * @return a byte readed
*/
unsigned char AT24Cxx_read(unsigned char, unsigned int);

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
void AT24Cxx_write_array(unsigned char, unsigned int, unsigned char*, unsigned int);

#endif //_EPR24Cxx_H_