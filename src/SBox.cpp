#include "SBox.h"

#include <spdlog/spdlog.h>

uint8_t SBox::apply(uint8_t value, SBOX box) {
  uint8_t ret = 0;
  // value  =   0bABCDEFGH = 0b011011 = 27
  // row_selector =   0bCH =     0b01 =  1
  // col_selector = 0bDEFG =   0b1101 = 13
  uint8_t row_selector = value & 0x01;
  row_selector |= ((value >> 4) & 0x02);

  uint8_t col_selector = (value >> 1) & 0x0F;

  switch (box) {
    case S1:
      ret = iS1[row_selector][col_selector];
      break;
    case S2:
      ret = iS2[row_selector][col_selector];
      break;
    case S3:
      ret = iS3[row_selector][col_selector];
      break;
    case S4:
      ret = iS4[row_selector][col_selector];
      break;
    case S5:
      ret = iS5[row_selector][col_selector];
      break;
    case S6:
      ret = iS6[row_selector][col_selector];
      break;
    case S7:
      ret = iS7[row_selector][col_selector];
      break;
    case S8:
      ret = iS8[row_selector][col_selector];
      break;
    default:
      spdlog::error("Not a valid box...");
      break;
  }

  return ret;
}
