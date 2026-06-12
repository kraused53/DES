#pragma once

#include <cstdint>

class KeySchedule {
 public:
  static const uint64_t get_key() { return key; }
  static const uint64_t get_permuted_key() { return permuted_key; }
  static const uint64_t get_C(int num) { return C[num]; }
  static const uint64_t get_D(int num) { return D[num]; }
  static const uint64_t get_K(int num) { return K[num]; }

  static void generate_schedule(uint64_t ikey);

 private:
  inline static const uint8_t shift_distance[16] = {1, 1, 2, 2, 2, 2, 2, 2,
                                                    1, 2, 2, 2, 2, 2, 2, 1};

  inline static uint64_t key = 0;           // Original key
  inline static uint64_t permuted_key = 0;  // Key after PC1
  inline static uint64_t C[17] = {0};       // The 17 left sub-keys
  inline static uint64_t D[17] = {0};       // The 17 right sub-keys
  inline static uint64_t K[16] = {0};       // Final 16 Keys

  static uint64_t shift_left_with_wrap(uint64_t val);
};