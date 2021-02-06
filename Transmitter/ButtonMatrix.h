#ifndef ButtonMatrix_h
#define ButtonMatrix_h
/*
This is deliberately a very high level class. But for most applications it will still be fast enough. Tested on an Arduino Leonardo @ 16MHZ and scanning a 4x5 matrix takes approximately 200 us.

*/
#include <Arduino.h>

class ButtonMatrix {
public:
  ButtonMatrix(
      const uint8_t* rowPins, uint8_t numRowPins,
      const uint8_t* colPins, uint8_t numColPins
  );
  void      scan(void);
  uint8_t   getButtonState(uint8_t index);
  uint8_t   getButtonState(uint8_t row, uint8_t col);
  uint8_t   getState(uint8_t index);
  const uint8_t*  ROW_PINS;
  const uint8_t*  COL_PINS;
  const uint8_t   NUM_ROWS;
  const uint8_t   NUM_COLS;
  const uint8_t   NUM_BUTTONS;
  const uint8_t   NUM_BYTES;
private:
  uint8_t*        _buttonStates;
};

#endif


uint8_t   rowCol2Byte(uint8_t row, uint8_t col, uint8_t numCols);
uint8_t   rowCol2Bit(uint8_t row, uint8_t col, uint8_t numCols);
uint8_t   rowCol2Index(uint8_t row, uint8_t col, uint8_t numCols);
uint8_t   index2Byte(uint8_t index);
uint8_t   index2Bit(uint8_t index);
