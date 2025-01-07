// Jason Bowman
// jbowman@hmc.edu
// created: 01/06/25
// GUIDANCE_CPP functions for guiding users through squat with haptics

#include "guidance.h"

/************************
* local variable define *
************************/

// configure the pins
void init_haptics() {
  pinMode(REAR_HAPTIC, OUTPUT);
  pinMode(FRONT_HAPTIC, OUTPUT);
}

// FUNCTION
void control(int16_t angle_ankle, int16_t angle_knee) {

  //Serial.println("Ratio: " + String(ratio));

  //Serial.println(": " + String(ratio) + " | Knee: " + String(angle_knee));

  if ((angle_knee - 90) < angle_ankle) {
    digitalWrite(REAR_HAPTIC, HIGH);
    digitalWrite(FRONT_HAPTIC, LOW);
  } else {
    digitalWrite(REAR_HAPTIC, LOW);
    digitalWrite(FRONT_HAPTIC, HIGH);
  }
}
