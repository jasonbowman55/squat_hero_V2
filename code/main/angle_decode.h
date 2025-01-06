// Jason Bowman
// jbowman@hmc.edu
// created: 01/04/25
// ANGLE_DECODE_H functions for decoding angles

#ifndef ANGLE_DECODE_H
#define ANGLE_DECODE_H

/***********************
*  Library Includess   *
***********************/
  #include <Wire.h> // holds all I2C communication functions
  #include <Arduino.h>
  #include <stdint.h>
  #include <cstdint>


/***********************************
* function input perameter defines *
***********************************/
  #define ANKLE  0
  #define KNEE   1
  #define HIP    2

/***********************
* function prototypes  *
***********************/
  int16_t decode_angle(int body_part, int16_t accel_x, int16_t accel_y, int16_t accel_z);

#endif 