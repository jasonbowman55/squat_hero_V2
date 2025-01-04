// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

#include <Wire.h>

/***********************
*  I2C global defines  *
***********************/
  // I2C clock and data line defines 
  #define SCL_PIN 9
  #define SDA_PIN 8

  // slave address defines (7-bit)
  #define IMU_ADDRESS_FEMUR 0b1101010  // [0] = 0 because address hardware is bridged
  #define IMU_ADDRESS_SHIN 0b1101011   // [0] = 1 because address hardware not bridged     TODO [NOT SURE WHAT ONE IS BRIDGES AND WHAT ONE IS NOT BRIDGED]

  // sub register address defines
  #define WHO_AM_I 0x0F      // used for I2C verification
  #define CTRL1_XL 0x10      // 104kHz - +/- 16g
  #define OUTX_L_A 0x28      // lsb x-axis accel
  #define OUTX_H_A 0x29      // msb x-axis accel
  #define OUTY_L_A 0x2A      // lsb y-axis accel
  #define OUTY_H_A 0x2B      // msb y-axis accel
  #define OUTZ_L_A 0x2C      // lsb z-axis accel
  #define OUTZ_H_A 0x2D      // msb z-axis accel

  // configuration register / 400kHz / 16g / no-filter
  char config_val = 0b01101010;



/****************************************************
* setup and configuration of master and slave chips *
****************************************************/
void setup() {
  // configuring
  Wire.begin(SDA_PIN, SCL_PIN);  // initialize I2C bus
  Wire.setClock(400000);         // set master clock speed to 400kHz high speed I2C
  Serial.begin(115200);
  Serial.println("I2C communication initialized");

  Wire.beginTransmission(IMU_ADDRESS_FEMUR); // Start communication with the slave
  Wire.write(CTRL1_XL);                      // Specify the register address
  Wire.write(config_val);                    // Write the configuration value

}



/***********************
*      main loop       *
***********************/
void loop() {



// // Send the register address you want to read from
// Wire.beginTransmission(IMU_ADDRESS_FEMUR);
// Wire.write(WHO_AM_I);
// Wire.endTransmission(false); // Send the address, but don't release the bus (repeated start)


// // Request 1 byte from the device
// Wire.requestFrom(IMU_ADDRESS_FEMUR, 1); // Read 1 byte from the IMU
// if (Wire.available()) {
//     char who_am_i_read = Wire.read(); // Read the byte from the buffer
//     Serial.print("WHO_AM_I: ");
//     Serial.println(who_am_i_read, HEX); // Print the value in hexadecimal
// } else {
//     Serial.println("Failed to read WHO_AM_I");
// }





 // Send the register address you want to read from
    Wire.beginTransmission(IMU_ADDRESS_FEMUR);  // Start communication with the IMU
    Wire.write(OUTX_L_A);                        // Specify the OUTX_L_A register address
    Wire.endTransmission(false);                 // Keep the bus active (repeated start)

    // Request 1 byte from the device
    Wire.requestFrom(IMU_ADDRESS_FEMUR, 1);      // Request 1 byte of data from the IMU

    // Read the data from the register
    if (Wire.available()) {
        char outx_l_a_value = Wire.read();      // Read the byte from the buffer
        Serial.print("OUTX_L_A: ");
        Serial.println(outx_l_a_value, HEX);   // Print the value in hexadecimal
    } else {
        Serial.println("Failed to read OUTX_L_A");
    }



    // // Read data from the device
    // Wire.requestFrom(0x68, 2); // Request 2 bytes
    // while (Wire.available()) {
    //     char c = Wire.read(); // Read byte
    //     Serial.println(c);
    // }

    // delay(1000);
}