#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t pinA, uint8_t pinB) :
  stepsCW(0),
  stepsCCW(0),
  PIN_A(pinA),
  PIN_B(pinB),
  STATE_TABLE{
    // R_START
    {ENC_START,    ENC_CW_BEGIN,  ENC_CCW_BEGIN, ENC_START},
    // R_CW_FINAL
    {ENC_CW_NEXT,  ENC_START,     ENC_CW_FINAL,  ENC_START | ENC_DIR_CW},
    // R_CW_BEGIN
    {ENC_CW_NEXT,  ENC_CW_BEGIN,  ENC_START,     ENC_START},
    // R_CW_NEXT
    {ENC_CW_NEXT,  ENC_CW_BEGIN,  ENC_CW_FINAL,  ENC_START},
    // R_CCW_BEGIN
    {ENC_CCW_NEXT, ENC_START,     ENC_CCW_BEGIN, ENC_START},
    // R_CCW_FINAL
    {ENC_CCW_NEXT, ENC_CCW_FINAL, ENC_START,     ENC_START | ENC_DIR_CCW},
    // R_CCW_NEXT
    {ENC_CCW_NEXT, ENC_CCW_FINAL, ENC_CCW_BEGIN, ENC_START},
  }
{
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  _state = ENC_START;
}

uint8_t   RotaryEncoder::scan(void) {
  uint8_t pinState = (digitalRead(PIN_A) << 1) | digitalRead(PIN_B);

  _state = STATE_TABLE[_state & 0xF][pinState];

  if ((_state & 0x30) == ENC_DIR_CW) {
    stepsCW++;
  } else if ((_state & 0x30) == ENC_DIR_CCW) {
    stepsCCW++;
  }
  return _state & 0x30;
}


EncoderArray::EncoderArray(RotaryEncoder* encoders, uint8_t numEncoders) :
  encoders(encoders),
  NUM_ENCODERS(numEncoders)
{

}

void EncoderArray::scan(void) {
  for (uint8_t i=0; i < NUM_ENCODERS; i++) {
    encoders[i].scan();
  }
}

uint8_t EncoderArray::getEncoderState(uint8_t index, EncoderDir dir) {

}
