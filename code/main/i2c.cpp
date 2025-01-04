// Jason Bowman
// jbowman@hmc.edu
// created: 01/03/25
// functions for running I2C commuications

/***********************
*   header includes    *
***********************/
#include "i2c.h"

/***********************
*         INIT         *
***********************/
void init_i2c() {
  Wire.begin(SDA_PIN, SCL_PIN);  // initialize I2C bus
  Wire.setClock(400000);         // set master clock speed to 400kHz high speed I2C
  Serial.println("I2C communication initialized");
}
/***********************
*   IMU ACCEL CONFIG   *
***********************/
void config_imu_accel(byte imu_slave_address, byte config_val) {
  writeRegister(imu_slave_address, CTRL1_XL, config_val);
}

/***********************
*   IMU VERIFY COMS    *
***********************/
void verify_coms(byte imu_slave_address) {
  byte who_am_i_val = readRegister(imu_slave_address, WHO_AM_I);
  if (who_am_i_val == 0x6C) {
    Serial.println("Communication lock");
  } else {
    Serial.println("Failed communication lock");
  }
}

/***********************
*         READ         *
***********************/
byte readRegister(byte chip, byte reg) {
  Wire.beginTransmission(chip); // begin transmition with given chip
  Wire.write(reg);              // send the register address to read from
  Wire.endTransmission(false);  // repeated start
  
  Wire.requestFrom(chip, 1);
  if (Wire.available()) {
    return Wire.read(); // Return the received byte
  } else {
    Serial.println("Failed to read from device!");
    return 0xFF; // Return an invalid value if read fails
  }
}

/***********************
*        WRITE         *
***********************/
void writeRegister(byte chip, byte reg, byte value) {
  Wire.beginTransmission(chip); // Start communication
  Wire.write(reg);  // Send the register address
  Wire.write(value); // Send the value to write
  Wire.endTransmission(); // End
}