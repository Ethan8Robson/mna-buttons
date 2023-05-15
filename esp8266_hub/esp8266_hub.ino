/*
 * Ethan Robson
 * ESP8266 button hub
 * 
 * Receives the new button data from the various wireless buttons
 * Sends the data to an HID-capable arduino via I2C
 */

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>

typedef struct struct_message {
    int id;
    int stat;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create button variable
int button = 0;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.println("ID: " + myData.id);
  Serial.println(myData.stat);
  
  Wire.beginTransmission(1); // sending data to 0x01
  Wire.write(byte(myData.id));
  Wire.write(byte(myData.stat));
  Wire.endTransmission();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  // Join i2c bus as a controller
  Wire.begin();
}

void loop(){
  // Access the variables for each board
  /*int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board2X = boardsStruct[1].x;
  int board2Y = boardsStruct[1].y;
  */
  // This runs when nothing is pressed
//  Wire.beginTransmission(1);
//  Wire.write(0);
//  Wire.endTransmission();
}
