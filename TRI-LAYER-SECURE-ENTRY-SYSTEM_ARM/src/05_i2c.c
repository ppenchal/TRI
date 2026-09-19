//i2c.c
#include "i2c.h"
#include "LPC214x.h"  
#include "types.h"   
#include "delay.h"

void i2c_init(void)
{
   
    PINSEL0 &= ~((3 << 4) | (3 << 6)); 
    PINSEL0 |= ((1 << 4) | (1 << 6));   

   
    I2C0SCLH = 75;
    I2C0SCLL = 75;

    I2C0CONSET = (1 << 6);  
    I2C0CONCLR = 0x2C;
}

// Generate START condition
void i2c_start(void)
{
    I2C0CONSET = (1 << 5);          
    while (!(I2C0CONSET & (1 << 3))); 
    I2C0CONCLR = (1 << 5);       
}

// Generate REPEATED START condition
void i2c_restart(void)
{
    I2C0CONSET = (1 << 5);          
    I2C0CONCLR = (1 << 3);          
    while (!(I2C0CONSET & (1 << 3))); 
    I2C0CONCLR = (1 << 5);         
}

// Generate STOP condition
void i2c_stop(void)
{
    I2C0CONSET = (1 << 4);          
    I2C0CONCLR = (1 << 3);          
}

// Write 1 byte to I2C bus
void i2c_write(u8 sDat)
{
    I2C0DAT = sDat;                 
    I2C0CONCLR = (1 << 3);         
    while (!(I2C0CONSET & (1 << 3))); 
}

// Read 1 byte + ACK
u8 i2c_mack(void)
{
    I2C0CONSET = (1 << 2);         
    I2C0CONCLR = (1 << 3);          
    while (!(I2C0CONSET & (1 << 3))); 
    I2C0CONCLR = (1 << 2);          
    return I2C0DAT;
}

u8 i2c_read_nack(void)
{
    I2C0CONCLR = (1 << 2); 
    I2C0CONCLR |= (1 << 3); 
    while (!(I2C0CONSET & (1 << 3))); 
    return I2C0DAT;
}

// EEPROM: Write 1 byte
void i2c_eeprom_bytewrite(u8 slaveAddr, u8 wBuffAddr, u8 data)
{
    i2c_start();
    i2c_write(slaveAddr << 1);  
    i2c_write(wBuffAddr);      
    i2c_write(data);            
    i2c_stop();
    delay_ms(10);               
}

// EEPROM: Read 1 byte (random read)
u8 i2c_eeprom_randomread(u8 slaveAddr, u8 rBuffAddr)
{
    u8 rDat;
    i2c_start();
    i2c_write(slaveAddr << 1);    
    i2c_write(rBuffAddr);          
    i2c_restart();
    i2c_write((slaveAddr << 1) | 1);
    rDat = i2c_read_nack();       
    i2c_stop();
    return rDat;
}
// EEPROM: Write multiple bytes (page write)
void i2c_eeprom_pagewrite(u8 slaveAddr, u8 wBuffStartAddr, u8 *p, u8 nBytes)
{
    u32 i;
    i2c_start();
    i2c_write(slaveAddr << 1);
    i2c_write(wBuffStartAddr);
    for(i = 0; i < nBytes; i++)
    {
        i2c_write(p[i]);
    }
    i2c_stop();
    delay_ms(10);
}

// EEPROM: Read multiple bytes (sequential read)
void i2c_eeprom_sequentialread(u8 slaveAddr, u8 rBuffStartAddr, u8 *p, u8 nBytes)
{
    u32 i;
    i2c_start();
    i2c_write(slaveAddr << 1);
    i2c_write(rBuffStartAddr);
    i2c_restart();
    i2c_write((slaveAddr << 1) | 1);
    for(i = 0; i < (nBytes - 1); i++)
    {
        p[i] = i2c_mack();
    }
    p[i++] = i2c_read_nack();
    p[i] = '\0';
    i2c_stop();
}
