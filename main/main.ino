// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

/************************
*    header includes    *
************************/
//#include "motor_control.h"
#include <Arduino.h>
#include <stdint.h>
#include "i2c.h"
#include "../Arduino-I2C/src/I2C_8Bit.h"

uint8_t config_value = 0b01001010;  // Value for 104kHz, +/- 16g in CTRL1_XL register

/****************
* initial setup *
****************/
 void setup() {

  // initialize and format the LSM6DS3 IMU
  I2C_8Bit_begin();                                                    // initialize I2C on esp32
  I2C_8Bit_writeToModule(IMU_ADDRESS_FEMAR, CTRL1_XL, config_value);   // configure accelerometer control register on femar IMU
  I2C_8Bit_writeToModule(IMU_ADDRESS_SHIN, CTRL1_XL, config_value);    // configure accelerometer control register on femar IMU

}

/****************
*   main loop   *
****************/
void loop() {

  uint16_t x_accel = read_accel_I2C(IMU_ADDRESS_FEMAR, X);
  uint16_t y_accel = read_accel_I2C(IMU_ADDRESS_FEMAR, Y);
  uint16_t z_accel = read_accel_I2C(IMU_ADDRESS_FEMAR, Z);

}