//i2c.h
#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include "types.h"  // For u8, u32

/***************** LPC21xx I2C Helper Functions *****************/

void i2c_init(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
void i2c_write(u8 sDat);
u8 i2c_mack(void);
u8 i2c_read_nack(void);

/***************** EEPROM High-Level Functions *****************/

void i2c_eeprom_bytewrite(u8 slaveAddr, u8 wBuffAddr, u8 data);
u8 i2c_eeprom_randomread(u8 slaveAddr, u8 rBuffAddr);
void i2c_eeprom_pagewrite(u8 slaveAddr, u8 wBuffStartAddr, u8 *p, u8 nBytes);
void i2c_eeprom_sequentialread(u8 slaveAddr, u8 rBuffStartAddr, u8 *p, u8 nBytes);

#endif /* I2C_HELPER_H */
