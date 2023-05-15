/*
 * Ethan Robson
 * Promicro data interpretter
 * 
 * Receives the data from the button hub via I2C
 * Uses a joystick library to emulate a game controller
 * Since joystick buttons are mapped to button inputs, buttons are pressed accordingly with the trivia button presses
 */

#include <Joystick.h>
#include <Wire.h>

#define BUTTON_PIN 9

Joystick_ Joystick;

int buttons[32] = {}; // initialize 32 button statuses

int input = 0;

void setup() {
  // Initialize Joystick Library
  Joystick.begin();

  // Initialize Wire Library
  Wire.begin(1); // Join I2C as slave with address 0x01
  Wire.onReceive(receiveEvent);

  // Initialize buttons to a known state, OFF
  for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++) {
    buttons[i] = 0;
  }
}


void loop() {
  for (int i = 0; i < 32; i++) { // loop through all button statuses
    if (buttons[i] == 1) {
      Joystick.pressButton(i);
    } else {
      Joystick.releaseButton(i);
    }
  }
}

void receiveEvent(int bytes) {
  int index = Wire.read(); // first read the id 
  buttons[index - 1] = Wire.read(); // next read the value of button
//  while (Wire.available()) {
//    input = Wire.read();
////    if (input == 1) {
////      Joystick.pressButton(0);
////    } else {
////      Joystick.releaseButton(0);
////    }
//  }
}
