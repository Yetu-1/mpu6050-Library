/*
 * mpu6050.h
 *
 *  Created on: Jul 2, 2021
 *      Author: Yetu
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
/***************************************************
  This is a library for MPU6050 (Gyro + Accelerometer)
 ****************************************************/
#endif /* INC_MPU6050_H_ */

#include "I2C.h"

#define MPU6050_ADDR 0xD0
#define PWR_MGMT_1   0x6B
#define PWR_MGMT_2   0x6C
#define WHO_AM_1     0x75
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define ACCEL_CONFIG 0x1C
#define SMPLRT_DIV   0x19

struct{
	uint8_t temp;
	uint8_t acc_x, acc_y, acc_z;
	uint8_t gyro_x, gyro_y, gyro_z;

}mpu6050;

void MPU6050_Config(void);

void write_mpu6050(uint8_t addr, uint8_t byte);

uint8_t read_mpu6050(uint8_t addr);

void update_mpu6050Val(void);