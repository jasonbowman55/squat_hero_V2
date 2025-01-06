// Jason Bowman
// jbowman@hmc.edu
// created: 01/03/25
// DATA_COLLECTION_H functions for running I2C commuications and decoding those to angles

#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

/***********************
*  Library Includes    *
***********************/
#include <Wire.h>
#include <Arduino.h>
#include <cstdint>

/***********************
*  chip and registers  *
***********************/
// IMU slave addresses
#define IMU_ADDRESS_FEMUR 0x6A
#define IMU_ADDRESS_SHIN 0x6B

// internal IMU registers
#define OUTX_L_A 0x28
#define OUTX_H_A 0x29
#define OUTY_L_A 0x2A
#define OUTY_H_A 0x2B
#define OUTZ_L_A 0x2C
#define OUTZ_H_A 0x2D

// I2C communication pincs
#define SCL_PIN 15
#define SDA_PIN 16
#define WHO_AM_I 0x0F
#define CTRL1_XL 0x10

/***********************
* Function Prototypes  *
***********************/
void init_i2c();
void config_imu_accel(byte imu_slave_address, byte config_val);
void verify_coms(byte imu_slave_address);
byte readRegister(byte chip, byte reg);
void writeRegister(byte chip, byte reg, byte value);
void readAccel();
void decodeAngles(int16_t x_shin, int16_t y_shin, int16_t z_shin, int16_t x_femur, int16_t y_femur, int16_t z_femur);

/***********************
* Global Variable Declarations (not definitions) *
***********************/
extern int16_t x_shin, y_shin, z_shin, x_femur, y_femur, z_femur;
extern int16_t angle_ankle, angle_knee;

#endif // End of I2C_H
