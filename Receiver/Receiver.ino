
#include <Joystick.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define NUM_BUTTONS 18 //num of button 
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
long button = 0x00000;
int buttonstate = 0; //record button state

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  26, false,                 // Button Count, Hat Switch Count
  false, false, false,   // no X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false    // No accelerator, brake, or steering
);


void setup() {
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Joystick.begin(false);
}

void loop() 
{
  while (!radio.available())
  {   digitalWrite(10,HIGH);
      delay(100);
      digitalWrite(10,LOW);
  }
  
  radio.read(&button, sizeof(button));
  //int button = text/10;
  //int buttonstate = text%10;
  if(189 < button && button < 262)
  {
    int Encoder_button = button/10;
    int Encoder_buttonstate = button%10;
    Joystick.setButton(Encoder_button, Encoder_buttonstate);
  }
  
  else{
  for(uint8_t i=1; i < NUM_BUTTONS+1; i++)
  {
    buttonstate = bitRead(button,i);
    Joystick.setButton(i, buttonstate);  
  }
  }
  Joystick.sendState();
  

}
