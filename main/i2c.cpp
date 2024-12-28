// Jason Bowman
// jbowman@hmc.edu
// created: 12/27/24

/***********************
*   header includes    *
***********************/
#include "i2c.h"

uint16_t read_accel_I2C(uint8_t imu_address, int axis) {

  if(axis == X) {
    // extract lsb and msb from imu
    uint8_t x_lsb = I2C_8Bit_readFromModule(imu_address, OUTX_L_A);
    uint8_t x_msb = I2C_8Bit_readFromModule(imu_address, OUTX_H_A);
    
    // combine lsb and msb
    uint16_t raw_accel_x = (uint16_t)((x_msb << 8) | x_lsb);

    return raw_accel_x; // Return the combined raw value
  }

  else if(axis == Y) {
    // extract lsb and msb from imu
    uint8_t y_lsb = I2C_8Bit_readFromModule(imu_address, OUTY_L_A);
    uint8_t y_msb = I2C_8Bit_readFromModule(imu_address, OUTY_H_A);
    
    // combine lsb and msb
    uint16_t raw_accel_y = (uint16_t)((y_msb << 8) | y_lsb);

    return raw_accel_y; // Return the combined raw value
  }

  else if(axis == Z) {
    // extract lsb and msb from imu
    uint8_t z_lsb = I2C_8Bit_readFromModule(imu_address, OUTZ_L_A);
    uint8_t z_msb = I2C_8Bit_readFromModule(imu_address, OUTZ_H_A);
    
    // combine lsb and msb
    uint16_t raw_accel_z = (uint16_t)((z_msb << 8) | z_lsb);

    return raw_accel_z; // Return the combined raw value
  }

return 0;

}
