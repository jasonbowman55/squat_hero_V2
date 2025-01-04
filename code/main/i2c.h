// Jason Bowman
// jbowman@hmc.edu
// created: 01/03/25
// functions for running I2C commuications

#ifndef I2C_H
#define I2C_H

/***********************
*  Library Includess   *
***********************/
#include <Wire.h> // holds all I2C communication functions
#include <Arduino.h>

/***********************
*  I2C clock and data line defines 
***********************/
#define SCL_PIN 15
#define SDA_PIN 16
#define WHO_AM_I 0x0F      // used for I2C verification
#define CTRL1_XL 0x10      // 104kHz - +/- 16g

/***********************
* function prototypes  *
***********************/
void init_i2c();
void config_imu_accel(byte imu_slave_address, byte config_val);
void verify_coms(byte imu_slave_address);
byte readRegister(byte chip, byte reg);
void writeRegister(byte chip, byte reg, byte value);

#endif // End of I2C_H
