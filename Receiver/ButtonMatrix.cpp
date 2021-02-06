#include "ButtonMatrix.h"


ButtonMatrix::ButtonMatrix(
  const uint8_t* rowPins, uint8_t numRowPins,
  const uint8_t* colPins, uint8_t numColPins
) :
  ROW_PINS(rowPins),
  COL_PINS(colPins),
  NUM_ROWS(numRowPins),
  NUM_COLS(numColPins),
  NUM_BUTTONS(numRowPins * numColPins),
  NUM_BYTES((numRowPins * numColPins + 8 - 1) / 8),
  _buttonStates(new uint8_t[NUM_BYTES])
{
  // set row pins to input and pull-up
  for (uint8_t i=0; i < NUM_ROWS; i++) {
    pinMode(ROW_PINS[i], INPUT_PULLUP);
  }
};

void    ButtonMatrix::scan(void) {

  // clear button states
  memset(_buttonStates, 0, NUM_BYTES);

  for(uint8_t col=0; col < NUM_COLS; col++) {
    // Begin column pulse
    pinMode(COL_PINS[col], OUTPUT);
    digitalWrite(COL_PINS[col], LOW);
    for (uint8_t row=0; row < NUM_ROWS; row++) {
      // read button state and set bit if active low
      if (!digitalRead(ROW_PINS[row])) {
        bitSet(
            _buttonStates[rowCol2Byte(row, col, NUM_COLS)],
            rowCol2Bit(row, col, NUM_COLS)
        );
      }
    }

    // End column pulse - Set pin to high impedance input.
    digitalWrite(COL_PINS[col], HIGH);
    pinMode(COL_PINS[col], INPUT);
  }
}

uint8_t ButtonMatrix::getButtonState(uint8_t index) {
  return bitRead(_buttonStates[index2Byte(index)], index2Bit(index));
}

uint8_t ButtonMatrix::getButtonState(uint8_t row, uint8_t col) {
  return bitRead(
      _buttonStates[rowCol2Byte(row, col, NUM_COLS)],
      rowCol2Bit(row, col, NUM_COLS)
  );
}

uint8_t ButtonMatrix::getState(uint8_t index) {
  return _buttonStates[index];
};

uint8_t  rowCol2Byte(uint8_t row, uint8_t col, uint8_t numCols) {
  return (row * numCols + col) / 8;
}

uint8_t  rowCol2Bit(uint8_t row, uint8_t col, uint8_t numCols) {
  return (row * numCols + col) % 8;
}

uint8_t   rowCol2Index(uint8_t row, uint8_t col, uint8_t numCols) {
  return row * numCols + col;
};

uint8_t   index2Byte(uint8_t index) {
  return index / 8;
};

uint8_t   index2Bit(uint8_t index) {
  return index % 8;
};
