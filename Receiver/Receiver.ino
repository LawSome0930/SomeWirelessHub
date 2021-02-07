
/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <Joystick.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 10
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int text = 0;

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  26, false,                 // Button Count, Hat Switch Count
  false, false, false,   // no X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false    // No accelerator, brake, or steering
);


void setup() {
  digitalWrite(led, LOW);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Joystick.begin(false);
}

void loop() {

  while (!radio.available());
  
  radio.read(&text, sizeof(text));
  int button = text/10;
  int buttonstate = text%10;

  Joystick.setButton(button, buttonstate);

  Joystick.sendState();
  

}
