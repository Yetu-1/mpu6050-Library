/*
 * mpu6050.c
 *
 *  Created on: Jul 2, 2021
 *      Author: Yetu
 */

#include "mpu6050.h"

uint8_t address = 0;					// starting address for read operation (corresponds to acc_y register)

void MPU6050_Config(){
	write_mpu6050(SMPLRT_DIV, 0x00);
	write_mpu6050(CONFIG, 0x00);
	write_mpu6050(GYRO_CONFIG, 0x08);
	write_mpu6050(ACCEL_CONFIG, 0x00);
	write_mpu6050(PWR_MGMT_1, 0x01);
}

void write_mpu6050(uint8_t addr, uint8_t byte){
	i2c_SetSlaveAddr(0xD0);             // Set slave address
	i2c_Start(0x02,0);                  // Start communication with the MPU-6050.
	i2c_writeByte(addr);                // Set address to write to
	i2c_writeByte(byte);                // Write byte to the specified address
	i2c_Stop(); 						// End communication with the MPU-6050
}

uint8_t read_mpu6050(uint8_t addr){
	uint8_t byte;
	i2c_SetSlaveAddr(0xD0);             // Set slave address
 	i2c_Start(1,0);						// Start communication with the MPU-6050
 	i2c_writeByte(addr);                // Set address to read from
 	i2c_SetSlaveAddr(0xD0);             // Set slave address
 	i2c_Start(1,1);                     // Generate a RESTART condition
 	byte = i2c_readByte();              // Read byte from I2C bus
 	i2c_Stop();                         // End communication with the MPU-6050
 	address++;
 	return byte;
}
void update_mpu6050Val(){
	address =  0x3B;
	mpu6050.acc_x	=	read_mpu6050(address) << 8 | read_mpu6050(address);
	mpu6050.acc_y	=	read_mpu6050(address) << 8 | read_mpu6050(address);
	mpu6050.acc_z	=	read_mpu6050(address) << 8 | read_mpu6050(address);
	mpu6050.temp	=	read_mpu6050(address) << 8 | read_mpu6050(address);
	mpu6050.gyro_x	=	read_mpu6050(address) << 8 | read_mpu6050(address);
	mpu6050.gyro_y	=	read_mpu6050(address) << 8 | read_mpu6050(address);
	mpu6050.gyro_z	=	read_mpu6050(address) << 8 | read_mpu6050(address);
}
