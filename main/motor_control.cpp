// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

/************************
*    header includes    *
************************/
#include "motor_control.h"

/*****************************************
*    Converts duty cycle to PWM output
      and outputs it to variable pin     *
******************************************/
void pwm_out(char pin, char duty_cycle){
  digitalWrite(17, HIGH);
  delayMicroseconds(800); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(17, LOW);
  delayMicroseconds(200);
}