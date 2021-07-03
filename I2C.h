/*
 * I2C.h
 *
 *  Created on: Jul 2, 2021
 *      Author: Yetu
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_
/***************************************************
  This is a library for I2C peripheral for the stm32h745 discovery board
 ****************************************************/
#endif /* INC_I2C_H_ */
#include <stm32h745xx.h>

// configure i2c ( default config )
void i2c_Config(void);

// set start bit, number of bytes to transfer/receive and read or write bit
void i2c_Start(uint8_t numbytes, uint8_t readORWrite);

// set stop bit
void i2c_Stop(void);

// set slave address
void i2c_SetSlaveAddr(uint8_t);

// write a byte to the I2C bus
void i2c_writeByte(uint8_t);

// read a byte from the I2C bus
uint8_t i2c_readByte(void);
