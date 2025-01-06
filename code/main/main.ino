// Jason Bowman
// jbowman@hmc.edu
// created: 12/26/24

/***********************
*   header includes    *
***********************/
#include <WiFi.h>
#include <WebServer.h>
#include "i2c.h"
#include "angle_decode.h"

/***********************
*  chip and registers  *
***********************/

// WiFi credentials
const char* ssid = "NETGEAR65";
const char* password = "quietoctopus488";

// Web server on port 80
WebServer server(80);

// Slave address defines (7-bit)
#define IMU_ADDRESS_FEMUR 0x6A  // [0] = 0 because address hardware is not bridged
#define IMU_ADDRESS_SHIN 0x6B   // [0] = 1 because address hardware is bridged

// Sub-register address defines
#define OUTX_L_A 0x28      // lsb x-axis accel
#define OUTX_H_A 0x29      // msb x-axis accel
#define OUTY_L_A 0x2A      // lsb y-axis accel
#define OUTY_H_A 0x2B      // msb y-axis accel
#define OUTZ_L_A 0x2C      // lsb z-axis accel
#define OUTZ_H_A 0x2D      // msb z-axis accel

// Configuration register / 400kHz / 16g / no-filter
byte config_val = 0b01101010;

// Global variables for angles
int16_t angle_ankle = 0;
int16_t angle_knee = 0;

/****************************************************
* setup and configuration of master and slave chips *
****************************************************/
void setup() {
  Serial.begin(115200);

  // Initialize I2C and IMU
  init_i2c();
  verify_coms(IMU_ADDRESS_FEMUR);
  config_imu_accel(IMU_ADDRESS_FEMUR, config_val);
  verify_coms(IMU_ADDRESS_SHIN);
  config_imu_accel(IMU_ADDRESS_SHIN, config_val);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define web server routes
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("HTTP server started");

  pinMode(45, OUTPUT);
  pinMode(48, OUTPUT);

}

/***********************
*      main loop       *
***********************/
void loop() {

  digitalWrite(45, HIGH);
  digitalWrite(48, HIGH);
  
  server.handleClient(); // Handle client requests


}

/***********************
*      Functions       *
***********************/

// Read IMU and calculate angles
void updateAngles() {

  // Read accelerations for femur (0x6A)
  uint8_t lsb_x_femur = readRegister(IMU_ADDRESS_FEMUR, OUTX_L_A);
  uint8_t msb_x_femur = readRegister(IMU_ADDRESS_FEMUR, OUTX_H_A);
  int16_t combinedValue_x_femur = (int16_t)((uint8_t)lsb_x_femur | (msb_x_femur << 8));

  uint8_t lsb_y_femur = readRegister(IMU_ADDRESS_FEMUR, OUTY_L_A);
  uint8_t msb_y_femur = readRegister(IMU_ADDRESS_FEMUR, OUTY_H_A);
  int16_t combinedValue_y_femur = (int16_t)((uint8_t)lsb_y_femur | (msb_y_femur << 8));

  uint8_t lsb_z_femur = readRegister(IMU_ADDRESS_FEMUR, OUTZ_L_A);
  uint8_t msb_z_femur = readRegister(IMU_ADDRESS_FEMUR, OUTZ_H_A);
  int16_t combinedValue_z_femur = (int16_t)((uint8_t)lsb_z_femur | (msb_z_femur << 8));

  // Read accelerations for shin (0x6B)
  uint8_t lsb_x_shin = readRegister(IMU_ADDRESS_SHIN, OUTX_L_A);
  uint8_t msb_x_shin = readRegister(IMU_ADDRESS_SHIN, OUTX_H_A);
  int16_t combinedValue_x_shin = (int16_t)((uint8_t)lsb_x_shin | (msb_x_shin << 8));

  uint8_t lsb_y_shin = readRegister(IMU_ADDRESS_SHIN, OUTY_L_A);
  uint8_t msb_y_shin = readRegister(IMU_ADDRESS_SHIN, OUTY_H_A);
  int16_t combinedValue_y_shin = (int16_t)((uint8_t)lsb_y_shin | (msb_y_shin << 8));

  uint8_t lsb_z_shin = readRegister(IMU_ADDRESS_SHIN, OUTZ_L_A);
  uint8_t msb_z_shin = readRegister(IMU_ADDRESS_SHIN, OUTZ_H_A);
  int16_t combinedValue_z_shin = (int16_t)((uint8_t)lsb_z_shin | (msb_z_shin << 8));

  // Decode angles
  angle_ankle = decode_angle(ANKLE, combinedValue_x_shin, combinedValue_y_shin, combinedValue_z_shin);
  angle_knee = decode_angle(KNEE, combinedValue_x_femur, combinedValue_y_femur, combinedValue_z_femur);
}

// Handle the root webpage
void handleRoot() {
  server.send(200, "text/html",
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<title>ESP32 IMU Data</title>"
    "<script>"
    "async function fetchData() {"
    "  const response = await fetch('/data');"
    "  const json = await response.json();"
    "  document.getElementById('ankle').innerText = json.ankle;"
    "  document.getElementById('knee').innerText = json.knee;"
    "}"
    "setInterval(fetchData, 50);" // Fetch every 50ms
    "</script>"
    "</head>"
    "<body onload='fetchData()'>"
    "<h1>Real-Time ESP32 IMU Data</h1>"
    "<p>Ankle Angle: <span id='ankle'>Loading...</span> degrees</p>"
    "<p>Knee Angle: <span id='knee'>Loading...</span> degrees</p>"
    "</body>"
    "</html>");
}

// Serve the angle data as JSON
void handleData() {
  updateAngles(); // Fetch the latest angles
  String json = "{\"ankle\":" + String(angle_ankle) + ",\"knee\":" + String(angle_knee) + "}";
  server.send(200, "application/json", json);
}
