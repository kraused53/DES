#pragma once

#include <cstdint>

class KeySchedule {
 public:
  static void generate_schedule(uint64_t key, uint64_t* subkeys);

 private:
  inline static const uint8_t shift_distance[16] = {1, 1, 2, 2, 2, 2, 2, 2,
                                                    1, 2, 2, 2, 2, 2, 2, 1};

  static uint64_t shift_left_with_wrap(uint64_t val);
};