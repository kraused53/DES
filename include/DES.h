#pragma once

#include <cstdint>

class DES {
 public:
  static uint64_t encrypt(uint64_t block, uint64_t key);
  static uint64_t decrypt(uint64_t block, uint64_t key);
};