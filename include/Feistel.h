#pragma once

#include <cstdint>

class Feistel {
 public:
  static uint64_t apply_sixteen_feistel_rounds(uint64_t block, uint64_t* keys,
                                               bool decrypt);

 private:
  static uint8_t extract_subblock(uint64_t block, int sbox_round);
  static uint32_t feistel_round(uint64_t block, uint64_t key);
};