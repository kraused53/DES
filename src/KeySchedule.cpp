#include "KeySchedule.h"

#include "Mapper.h"
#include "spdlog/spdlog.h"

void KeySchedule::generate_schedule(uint64_t key, uint64_t* subkeys) {
  spdlog::info("Generating key schedule...");
  uint64_t permuted_key = Mapper::apply_map(key, PC1);
  spdlog::debug("Key after PC-1: 0x{:016X}", permuted_key);

  uint64_t C[17] = {0};  // The 17 left sub-keys
  uint64_t D[17] = {0};  // The 17 right sub-keys

  // Split the 56-Bit permuted key into two 28-Bit sub keys.
  C[0] = (permuted_key >> 28) & 0xFFFFFFF;
  D[0] = permuted_key & 0xFFFFFFF;

  spdlog::debug("C[ 0]: 0x{:016X}", C[0]);
  spdlog::debug("D[ 0]: 0x{:016X}", D[0]);
  // Generate 16 Sub keys
  for (int sKey = 1; sKey <= 16; sKey++) {
    // Current C and D are based off of previous C and D
    C[sKey] = C[sKey - 1];
    D[sKey] = D[sKey - 1];
    for (int sdist = 0; sdist < shift_distance[sKey - 1]; sdist++) {
      // Shift C and D left with wrap repeatedly according to the current value
      // of shift_distance
      C[sKey] = shift_left_with_wrap(C[sKey]);
      D[sKey] = shift_left_with_wrap(D[sKey]);

      spdlog::debug("C[{:2d}]: 0x{:016X}", sKey, C[sKey]);
      spdlog::debug("D[{:2d}]: 0x{:016X}", sKey, D[sKey]);
    }
  }

  // Generate 16 Final keys
  for (int fKey = 0; fKey < 16; fKey++) {
    // Combine this final-key's subkeys
    uint64_t CD = (C[fKey + 1] << 28) | D[fKey + 1];
    // Apply PC-2 to the subkey combo
    subkeys[fKey] = Mapper::apply_map(CD, PC2);
    // Limit Key to 56 bits
    subkeys[fKey] &= 0xFFFFFFFFFFFFFF;

    spdlog::debug("Subkey[{:2d}]: 0x{:016X}", fKey, subkeys[fKey]);
  }
}

uint64_t KeySchedule::shift_left_with_wrap(uint64_t val) {
  // Capture leftmost bit of val
  bool wrap = val & 0x8000000;
  // Shift val left one bit
  val <<= 1;
  // Apply wrap
  if (wrap) {
    val |= 1;
  }
  // Limit val to 28 Bits
  val &= 0xFFFFFFF;

  return val;
}