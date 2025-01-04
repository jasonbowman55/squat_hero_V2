



int16_t decode_angle(int body_part, int16_t accel_x, int16_t accel_y, int16_t accel_z) {
    // ANKLE
    if (body_part == ANKLE) { // normal scenario
      if (accel_x < 0) {
        if (accel_y > 0) {
          theta_1 = (int16_t)(atan((float)accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_ankle = 90 + theta_1;
          return theta_ankle;
        } else if (accel_y < 0) {
          theta_1 = (int16_t)(atan((float)-accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_ankle = 90 - theta_1;
          return theta_ankle;
        } else {
          return 90;
        }
      } else if (accel_x > 0) { // unexpected scenario
        if (accel_y > 0) {
          theta_1 = (int16_t)(atan((float)accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_ankle = 270 + theta_1;
          return theta_ankle;
        } else if (accel_y < 0) {
          theta_1 = (int16_t)(atan((float)-accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_ankle = -(360 - (270 - theta_1));
          return theta_ankle;
        } else {
          return 90;
        }
      }
    // KNEE
    } else if (body_part == KNEE) {
      if (accel_x < 0) { // normal scenario
        if (accel_y > 0) {
          theta_2 = theta_ankle;
          theta_3 = (int16_t)(atan((float)accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_4 = 90 - theta_3;
          theta_knee = theta_2 + theta_4;
          return theta_knee;
        } else if (accel_y < 0) {
          theta_2 = theta_ankle;
          theta_3 = (int16_t)(atan((float)-accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_4 = 90 + theta_3;
          theta_knee = theta_2 + theta_4;
          return theta_knee;
        } else {
          theta_knee = 180 - (theta_3 + theta_1);
          return theta_knee;
        }
      } else if (accel_x > 0) { // unexpected scenario
        if (accel_y > 0) {
          theta_2 = theta_ankle;
          theta_3 = (int16_t)(atan((float)accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_4 = 90 + theta_3;
          theta_3 = theta_3 + 180;
          theta_knee = theta_2 - theta_4;
          return theta_knee;
        } else if (accel_y < 0) {
          theta_2 = theta_ankle;
          theta_3 = (int16_t)(atan((float)-accel_y / (float)-accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_4 = -(360 - (270 + theta_3));
          theta_knee = theta_2 + theta_4;
          return theta_knee;
        } else {
          theta_knee = 180 - (theta_3 + theta_1);
          return theta_knee;
        }
      }
    // HIP
    } else if (body_part == HIP) {
      if (accel_x > 0) { // normal scenario
        if (accel_z > 0) {
          theta_5 = 90 - theta_3;
          theta_6 = (int16_t)(atan((float)accel_z / (float)accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_7 = 90 + theta_6;
          theta_hip = theta_5 + theta_7;
          return theta_hip;
        } else if (accel_z < 0) {
          theta_5 = 90 - theta_3;
          theta_6 = (int16_t)(atan((float)-accel_z / (float)accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_7 = 90 - theta_6;
          theta_hip = theta_5 + theta_7;
          return theta_hip;
        } else {
          theta_hip = 180 - theta_3;
        }
      } else if (accel_x < 0) { // unexpected scenario
        if (accel_z > 0) {
          theta_5 = 90 - theta_3;
          theta_6 = (int16_t)(atan((float)accel_z / (float)accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_7 = 90 + theta_6;
          theta_hip = theta_5 - theta_7;
          return theta_hip;
        } else if (accel_z < 0) {
          theta_5 = 90 - theta_3;
          theta_6 = (int16_t)(atan((float)-accel_z / (float)accel_x) * 180 / M_PI); // Convert radians to degrees
          theta_7 = -(360 - (270 - theta_6));
          theta_hip = theta_5 + theta_7;
          return theta_hip;
        } else {
          theta_hip = 180 - theta_3;
        }
      }
    }

    return -1; // Error code for invalid input
}
