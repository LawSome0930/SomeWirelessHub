#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "ButtonMatrix.h"
#include "RotaryEncoder.h"


RF24 radio(9, 10); // CE, CSN
boolean buttonState = 0;
const byte address[6] = "00001";
int text=666;

// initialize button matrix ///////////////////////////////////////////////////
const uint8_t NUM_ROW_PINS = 4; //Number of rows of keyboard matrix
const uint8_t ROW_PINS[NUM_ROW_PINS] = {A0, A1, A2, A3};   //The pin corresponding to the row of keyboard matrix
const uint8_t NUM_COL_PINS = 5; //Number of columns of keyboard matrix
const uint8_t COL_PINS[NUM_COL_PINS] = {4, 5, 6, 7, 8};  //The pin corresponding to the columns of keyboard matrix
ButtonMatrix matrix(
    ROW_PINS, NUM_ROW_PINS,
    COL_PINS, NUM_COL_PINS
);
// map the buttons of the matrix to Joystick HID button using a map
const uint8_t NUM_MAPPED_BUTTONS = 18;    
const uint8_t BUTTON_MAP[NUM_MAPPED_BUTTONS] = {
  3, 4, 13, 14, 8, 18,
  0, 1, 2, 5,
  6, 7, 10, 11, 12, 15, 16, 17
};

// initialize encoders ////////////////////////////////////////////////////////
RotaryEncoder encoderOne(3, A4);
RotaryEncoder encoderTwo(2, A4);
RotaryEncoder encoderThree(0, A5);
RotaryEncoder encoderFour(1, A5);
const uint8_t NUM_ENCODERS = 4;
RotaryEncoder* encoders[NUM_ENCODERS] = {
  &encoderOne, &encoderTwo, &encoderThree, &encoderFour
};
// encoder delay is the duration of one emulated button press in number of
// cycles of the main loop
uint8_t ENC_DELAY = 20;
// the counters keep track of the elapsed cycles for the delay (see above)
uint8_t countersCW[NUM_ENCODERS] = {0, 0, 0, 0};
uint8_t countersCCW[NUM_ENCODERS] = {0, 0, 0, 0};


void setup() {
  pinMode(5, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}



void loop() {

  
  
  radio.write(&text, sizeof(text));
  delay(10);
}
