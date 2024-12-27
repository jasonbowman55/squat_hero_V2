// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

//#include "motor_control.h"
#include <Arduino.h>
#include "../Arduino-I2C/I2C_8Bit.h"

/****************
* initial setup *
****************/
 void setup() {

  // initialize and format the LSM6DS3 IMU
  I2C_8Bit_begin(); 
  void I2C_8Bit_writeToModule(uint8_t i2cAddr, uint8_t registerAddr, uint8_t data);

  // pin definitions
  pinMode(17, OUTPUT);

}

/****************
*   main loop   *
****************/
void loop() {

}