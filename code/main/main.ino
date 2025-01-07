// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24
// MAIN_INO ...

/***********************
*   header includes    *
***********************/
#include "data_collection.h"
#include "angle_decode.h"
#include "guidance.h"

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

  init_haptics();
}

/***********************
*      main loop       *
***********************/
void loop() {

  readAccel();  // read all accel data (16-bit)
  decodeAngles(x_shin, y_shin, z_shin, x_femur, y_femur, z_femur); // decode ankle and knee angles
  control(angle_ankle, angle_knee);
  
  // Print all values on one line with labels
  // Serial.println("Ankle: " + String(angle_ankle) + 
  //               " | Knee: " + String(angle_knee));

}