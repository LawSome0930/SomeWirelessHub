#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

// No complete step yet.
#define ENC_DIR_NONE  0x0
// Clockwise step.
#define ENC_DIR_CW    0x10
// Counter-clockwise step.
#define ENC_DIR_CCW   0x20

#define ENC_START     0x0
// Full-step state table
#define ENC_CW_FINAL  0x1
#define ENC_CW_BEGIN  0x2
#define ENC_CW_NEXT   0x3
#define ENC_CCW_BEGIN 0x4
#define ENC_CCW_FINAL 0x5
#define ENC_CCW_NEXT  0x6

enum class EncoderDir {
  CW,
  CCW
};

class RotaryEncoder {
public:
  RotaryEncoder(uint8_t pinA, uint8_t pinB);
  uint8_t scan(void);
  uint8_t stepsCW;
  uint8_t stepsCCW;
  const uint8_t PIN_A;
  const uint8_t PIN_B;
  const uint8_t STATE_TABLE[7][4];
private:
  uint8_t _state;
};


class EncoderArray {
public:
  EncoderArray(RotaryEncoder* encoders, uint8_t numEncoders);
  void      scan(void);
  uint8_t   getEncoderState(uint8_t index, EncoderDir dir);
  RotaryEncoder* encoders;
  const uint8_t NUM_ENCODERS;
private:

};
#endif
