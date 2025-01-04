// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

/***********************
*   header includes    *
***********************/
#include "i2c.h"
#include "angle_decode.h"

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
  verify_coms(IMU_ADDRESS_SHIN);
  config_imu_accel(IMU_ADDRESS_SHIN, config_val);
}

/***********************
*      main loop       *
***********************/
void loop() {
  // read and print the X, Y, and Z axis accelerations (FEMUR 0x6A)
  uint8_t lsb_x_femur = readRegister(IMU_ADDRESS_FEMUR, OUTX_L_A);        // lsb read
  uint8_t msb_x_femur = readRegister(IMU_ADDRESS_FEMUR, OUTX_H_A);        // msb read
  int16_t combinedValue_x_femur = (int16_t)((uint8_t)lsb_x_femur | (msb_x_femur << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_y_femur = readRegister(IMU_ADDRESS_FEMUR, OUTY_L_A);        // lsb read
  uint8_t msb_y_femur = readRegister(IMU_ADDRESS_FEMUR, OUTY_H_A);        // msb read
  int16_t combinedValue_y_femur = (int16_t)((uint8_t)lsb_y_femur | (msb_y_femur << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_z_femur = readRegister(IMU_ADDRESS_FEMUR, OUTZ_L_A);        // lsb read
  uint8_t msb_z_femur = readRegister(IMU_ADDRESS_FEMUR, OUTZ_H_A);        // msb read
  int16_t combinedValue_z_femur = (int16_t)((uint8_t)lsb_z_femur | (msb_z_femur << 8)); // combine lsb and msb values to 16-bit signed acceleration



  // read and print the X, Y, and Z axis accelerations (SHIN 0x6B)
  uint8_t lsb_x_shin = readRegister(IMU_ADDRESS_SHIN, OUTX_L_A);        // lsb read
  uint8_t msb_x_shin = readRegister(IMU_ADDRESS_SHIN, OUTX_H_A);        // msb read
  int16_t combinedValue_x_shin = (int16_t)((uint8_t)lsb_x_shin | (msb_x_shin << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_y_shin = readRegister(IMU_ADDRESS_SHIN, OUTY_L_A);        // lsb read
  uint8_t msb_y_shin = readRegister(IMU_ADDRESS_SHIN, OUTY_H_A);        // msb read
  int16_t combinedValue_y_shin = (int16_t)((uint8_t)lsb_y_shin | (msb_y_shin << 8)); // combine lsb and msb values to 16-bit signed acceleration

  // read and print the X, Y, and Z axis accelerations
  uint8_t lsb_z_shin = readRegister(IMU_ADDRESS_SHIN, OUTZ_L_A);        // lsb read
  uint8_t msb_z_shin = readRegister(IMU_ADDRESS_SHIN, OUTZ_H_A);        // msb read
  int16_t combinedValue_z_shin = (int16_t)((uint8_t)lsb_z_shin | (msb_z_shin << 8)); // combine lsb and msb values to 16-bit signed acceleration


  // decode angles
  int16_t angle_ankle = decode_angle(ANKLE, combinedValue_x_shin, combinedValue_y_shin, combinedValue_z_shin);
  int16_t angle_knee = decode_angle(KNEE, combinedValue_x_femur, combinedValue_y_femur, combinedValue_z_femur);

  // // Print all values on one line with labels
  // Serial.println("XF: " + String(combinedValue_x_femur) + 
  //               " | YF: " + String(combinedValue_y_femur) + 
  //               " | ZF: " + String(combinedValue_z_femur) + 
  //               " | XS: " + String(combinedValue_x_shin) + 
  //               " | YS: " + String(combinedValue_y_shin) + 
  //               " | ZS: " + String(combinedValue_z_shin));
  // delay(1000);

  // Print all values on one line with labels
  Serial.println("Ankle: " + String(angle_ankle) + 
                " | Knee: " + String(angle_knee));

}
