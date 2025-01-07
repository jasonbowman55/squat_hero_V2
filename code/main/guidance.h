// Jason Bowman
// jbowman@hmc.edu
// created: 01/06/25
// GUIDANCE_H functions for guiding users through squat with haptics

#ifndef GUIDANCE_H
#define GUIDANCE_H

/***********************
*  Library Includess   *
***********************/
  #include <stdint.h>
  #include "data_collection.h"
  #include <Arduino.h>
  #include <cstdint>
  #include <math.h>

/***********************
*   Global Variabels   *
***********************/
  // haptic motor pins
  #define REAR_HAPTIC 45
  #define FRONT_HAPTIC 48

/***********************
* function prototypes  *
***********************/
  void init_haptics();
  void control(int16_t angle_ankle, int16_t angle_knee);

#endif 