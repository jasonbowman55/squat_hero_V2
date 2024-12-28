// Jason Bowman
// jbowman@hmc.edu
// created: 12/27/24

#ifndef I2C_H
#define I2C_H

#include <Arduino.h>
#include <stdint.h>
#include "../Arduino-I2C/src/I2C_8Bit.h"

/***********************
*  I2C global defines  *
***********************/

// I2C clock and data line defines 
#define SCL 1 
#define SDA 2
// TODO: FIX THE PINS FOR THE SCL AND SDA

// slave address defines
#define IMU_ADDRESS_SHIN 0x6B   // [0] = 1 because address hardware not bridged     TODO [NOT SURE WHAT ONE IS BRIDGES AND WHAT ONE IS NOT BRIDGED]
#define IMU_ADDRESS_FEMAR 0x6A  // [0] = 0 because address hardware is bridged

// sub register address defines
#define WHO_AM_I 0x0F      // used for I2C verification
#define CTRL1_XL 0x10      // 104kHz - +/- 16g
#define OUTX_L_A 0x28      // lsb x-axis accel
#define OUTX_H_A 0x29      // msb x-axis accel
#define OUTY_L_A 0x2A      // lsb y-axis accel
#define OUTY_H_A 0x2B      // msb y-axis accel
#define OUTZ_L_A 0x2C      // lsb z-axis accel
#define OUTZ_H_A 0x2D      // msb z-axis accel

// axis defines
#define X 1
#define Y 2
#define Z 3

/**********************
* function prototypes *
**********************/
uint16_t read_accel_I2C(uint8_t IMU_ADDRESS, int axis);

#endif