// Jason Bowman
// jbowman@hmc.edu
// created: 01/03/25
// DATA_COLLECTION_CPP functions for running I2C commuications and decoding those to angles

#include "data_collection.h"
#include "angle_decode.h"

/***********************
* Global Variable Definitions *
***********************/
int16_t x_shin, y_shin, z_shin, x_femur, y_femur, z_femur;
int16_t angle_ankle, angle_knee;

// Function implementations remain the same
void init_i2c() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);
  Serial.println("I2C communication initialized");
}

void config_imu_accel(byte imu_slave_address, byte config_val) {
  writeRegister(imu_slave_address, CTRL1_XL, config_val);
}

void verify_coms(byte imu_slave_address) {
  byte who_am_i_val = readRegister(imu_slave_address, WHO_AM_I);
  if (who_am_i_val == 0x6C) {
    Serial.println("Communication lock");
  } else {
    Serial.println("Failed communication lock");
  }
}

byte readRegister(byte chip, byte reg) {
  Wire.beginTransmission(chip);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(chip, 1);
  if (Wire.available()) {
    return Wire.read();
  } else {
    Serial.println("Failed to read from device!");
    return 0xFF;
  }
}

void writeRegister(byte chip, byte reg, byte value) {
  Wire.beginTransmission(chip);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void readAccel() {
  uint8_t lsb_x_femur = readRegister(IMU_ADDRESS_FEMUR, OUTX_L_A);
  uint8_t msb_x_femur = readRegister(IMU_ADDRESS_FEMUR, OUTX_H_A);
  x_femur = (int16_t)((uint8_t)lsb_x_femur | (msb_x_femur << 8));

  uint8_t lsb_y_femur = readRegister(IMU_ADDRESS_FEMUR, OUTY_L_A);
  uint8_t msb_y_femur = readRegister(IMU_ADDRESS_FEMUR, OUTY_H_A);
  y_femur = (int16_t)((uint8_t)lsb_y_femur | (msb_y_femur << 8));

  uint8_t lsb_z_femur = readRegister(IMU_ADDRESS_FEMUR, OUTZ_L_A);
  uint8_t msb_z_femur = readRegister(IMU_ADDRESS_FEMUR, OUTZ_H_A);
  z_femur = (int16_t)((uint8_t)lsb_z_femur | (msb_z_femur << 8));

  uint8_t lsb_x_shin = readRegister(IMU_ADDRESS_SHIN, OUTX_L_A);
  uint8_t msb_x_shin = readRegister(IMU_ADDRESS_SHIN, OUTX_H_A);
  x_shin = (int16_t)((uint8_t)lsb_x_shin | (msb_x_shin << 8));

  uint8_t lsb_y_shin = readRegister(IMU_ADDRESS_SHIN, OUTY_L_A);
  uint8_t msb_y_shin = readRegister(IMU_ADDRESS_SHIN, OUTY_H_A);
  y_shin = (int16_t)((uint8_t)lsb_y_shin | (msb_y_shin << 8));

  uint8_t lsb_z_shin = readRegister(IMU_ADDRESS_SHIN, OUTZ_L_A);
  uint8_t msb_z_shin = readRegister(IMU_ADDRESS_SHIN, OUTZ_H_A);
  z_shin = (int16_t)((uint8_t)lsb_z_shin | (msb_z_shin << 8));
}

void decodeAngles(int16_t x_shin, int16_t y_shin, int16_t z_shin, int16_t x_femur, int16_t y_femur, int16_t z_femur) {
  angle_ankle = decode_angle(ANKLE, x_shin, y_shin, z_shin);
  angle_knee = decode_angle(KNEE, x_femur, y_femur, z_femur);
}
