/*
 * I2C.c
 *
 *  Created on: Jul 2, 2021
 *      Author: Yetu
 */
#include "I2C.h"

void i2c_Config(){
	RCC->APB4ENR |= RCC_APB4ENR_I2C4EN;       		// Enable the I2C4 clock in the RCC_RCC_APB4ENR peripheral clock enable register
	I2C4->TIMINGR |= 0x10C0EFFC;              		// Configure timings in the I2C_TIMINGR register (standard : 100Mhz)
	I2C4->CR1 |= I2C_CR1_PE;                  		// Enable 12C4 by setting the PE bit in the I2C_CR1 register
	I2C4->CR2 &= ~I2C_CR2_AUTOEND;            		// Don't auto-end after N-bytes have been transfer/received

	/* I WILL BE USING THE DEFAULT CONFIG FOR 12C: 7BIT ADDR MODE... */
}
void i2c_SetSlaveAddr(uint8_t device_addr){
	I2C4->CR2 |= device_addr;	              		// Set slave address
}
void i2c_Start(uint8_t numBytes, uint8_t readORwrite){
	I2C4->CR2 |= (numBytes << I2C_CR2_NBYTES_Pos); 	// Set number of bytes to be transmitted/received

	// Request for a Read or Write transfer (read:1 - write:0)
	if(readORwrite){
		I2C4->CR2 |= I2C_CR2_RD_WRN;          		// Set read/write bit for a read operation
		I2C4->CR2 |= I2C_CR2_START;           		// Generate start condition
	}
	else{
		I2C4->CR2 &= ~I2C_CR2_RD_WRN;         		// Set read/write bit for a write operation
		I2C4->CR2 |= I2C_CR2_START;           		// Generate start condition
		while(!(I2C4->ISR & I2C_ISR_TXIS));   		// Wait for TXIS flag
	}
}

void i2c_Stop(){
	I2C4->CR2 |= I2C_CR2_STOP;                		// Generate Stop condition
}

void i2c_writeByte(uint8_t byte){
	I2C4->TXDR = byte;                        		// Set data byte to be transmitted to the I2C bus
	while(!(I2C4->ISR & I2C_ISR_TXE));        		// Wait until transmit data register empty flag is set
}
uint8_t i2c_readByte(){
	uint8_t byte;
	while(!(I2C4->ISR & I2C_ISR_RXNE));             // Wait until receive data register not empty flag is set
	byte = I2C4->RXDR;                              // Read byte...
	return byte;
}