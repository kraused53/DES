#include "Mapper.h"

#include <spdlog/spdlog.h>

uint64_t Mapper::apply_map(uint64_t initial_value, MAP map) {
  uint64_t result = 0;

  switch (map) {
    case IP:
      result = apply_map_helper(initial_value, iIP, 64, 64);
      break;
    case FP:
      result = apply_map_helper(initial_value, iFP, 64, 64);
      break;
    case E:
      result = apply_map_helper(initial_value, iE, 32, 48);
      break;
    case P:
      result = apply_map_helper(initial_value, iP, 32, 32);
      break;
    case PC1:
      result = apply_map_helper(initial_value, iPC1, 64, 56);
      break;
    case PC2:
      result = apply_map_helper(initial_value, iPC2, 56, 48);
      break;
    default:
      spdlog::error("This map has not been implemented yet...");
      break;
  }

  return result;
}

uint64_t Mapper::apply_map_helper(uint64_t ival, const uint8_t* map,
                                  size_t isize, size_t osize) {
  uint64_t result = 0;
  for (int i = 0; i < osize; i++) {
    result = (result << 1) | get_bit(ival, map[i] - 1, isize);
  }
  return result;
}

uint64_t Mapper::get_bit(uint64_t val, size_t pos, size_t size) {
  uint64_t mask = 1ULL << (size - 1 - pos);
  return (val & mask) != 0;
}
