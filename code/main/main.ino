// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

/***********************
*   header includes    *
***********************/
#include "i2c.h"
#include <stdint.h>

/***********************
*  chip and registers  *
***********************/

  // slave address defines (7-bit)
  #define IMU_ADDRESS_FEMUR 0x6A  // [0] = 0 because address hardware is not bridged
  #define IMU_ADDRESS_SHIN 0x6B   // [0] = 1 because address hardware is bridged

  // sub register address defines
  #define OUTX_L_A 0x28      // lsb x-axis accel
  #define OUTX_H_A 0x29      // msb x-axis accel
  #define OUTY_L_A 0x2A      // lsb y-axis accel
  #define OUTY_H_A 0x2B      // msb y-axis accel
  #define OUTZ_L_A 0x2C      // lsb z-axis accel
  #define OUTZ_H_A 0x2D      // msb z-axis accel

  // configuration register / 400kHz / 16g / no-filter
  byte config_val = 0b01101010;

/****************************************************
* setup and configuration of master and slave chips *
****************************************************/
void setup() {
  Serial.begin(115200);
  init_i2c();
  verify_coms(IMU_ADDRESS_FEMUR);
  config_imu_accel(IMU_ADDRESS_FEMUR, config_val);
}

/***********************
*      main loop       *
***********************/
void loop() {
  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_x = readRegister(IMU_ADDRESS_FEMUR, OUTX_L_A);        // lsb read
  uint8_t msb_x = readRegister(IMU_ADDRESS_FEMUR, OUTX_H_A);        // msb read
  int16_t combinedValue_x = (int16_t)((uint8_t)lsb_x | (msb_x << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_y = readRegister(IMU_ADDRESS_FEMUR, OUTY_L_A);        // lsb read
  uint8_t msb_y = readRegister(IMU_ADDRESS_FEMUR, OUTY_H_A);        // msb read
  int16_t combinedValue_y = (int16_t)((uint8_t)lsb_y | (msb_y << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_z = readRegister(IMU_ADDRESS_FEMUR, OUTZ_L_A);        // lsb read
  uint8_t msb_z = readRegister(IMU_ADDRESS_FEMUR, OUTZ_H_A);        // msb read
  int16_t combinedValue_z = (int16_t)((uint8_t)lsb_z | (msb_z << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // Print all values on one line with labels
  Serial.print("Accel X: ");
  Serial.print(combinedValue_x);
  Serial.print(" | Accel Y: ");
  Serial.print(combinedValue_y);
  Serial.print(" | Accel Z: ");
  Serial.println(combinedValue_z);
}
