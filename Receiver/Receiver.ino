/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 10
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
boolean buttonState = 0;

void setup() {
  pinMode(led, OUTPUT);
 // Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
//  if (radio.available()) {
//    int text=0;
//    radio.read(&text, sizeof(text));
//    Serial.println(text);
//  }
  while (!radio.available());
  radio.read(&buttonState, sizeof(buttonState));
  if (buttonState == 1) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }

}
