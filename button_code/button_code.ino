/*
   Ethan Robson
   Button Code for mna-buttons project

   Uses a simple button debouncer library along with the ESP-NOW protocol
   Sends data to the hub when the button is pressed or depressed

   Data consists of new button state, along with the button ID
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Bounce2.h>

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x60, 0x01, 0x94, 0x1F, 0x1B, 0x8C};

String my_mac = "";

typedef struct struct_message {
  int id; // id number of button
  int stat; // pressed or unpressed status
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Set your Board ID (ESP32 Sender #1 = BOARD_ID 1, ESP32 Sender #2 = BOARD_ID 2, etc)
#define BOARD_ID 22

//
// BUTTON DATA
//
#define BUTTON_PIN 0
Bounce2::Button button = Bounce2::Button();


// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(9600);
  Serial.println("starting the serial");

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Set ESP-NOW role
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  // Once ESPNow is successfully init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Obtain and store board id
  myData.id = BOARD_ID;

  // BUTTON DECLARATIONS
  button.attach(BUTTON_PIN, INPUT_PULLUP); // attach button with internal pullup resistor
  button.interval(5); // 5ms debounce time
  button.setPressedState(LOW); // LOW is when button is pressed

}

void loop() {
  //Update the status of the button
  button.update();

  // Sending data via ESP-NOW
  if (button.fell()) { // trigger if button goes from low to high(pressed)
    Serial.println("pressed");
    myData.stat = 1;
    esp_now_send(0, (uint8_t *) &myData, sizeof(myData)); // send to board id 0, data of my_mac
  } else if (button.rose()) {
    Serial.println("rose");
    myData.stat = 0;
    esp_now_send(0, (uint8_t *) &myData, sizeof(myData)); // send to board id 0, data of my_mac
  }
}
