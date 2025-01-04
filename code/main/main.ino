// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

/***********************
*   header includes    *
***********************/
#include "i2c.h"

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
  //verify_coms(IMU_ADDRESS_FEMUR);
  //config_imu_accel(IMU_ADDRESS_FEMUR, config_val);
}



/***********************
*      main loop       *
***********************/
void loop() {
  byte accel = readRegister(IMU_ADDRESS_FEMUR, OUTX_L_A);

  Serial.print("Accel value: ");
  Serial.println(accel);
  
  delay(5000);
}