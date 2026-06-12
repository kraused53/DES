#include <gtest/gtest.h>

#include <cstdint>

#include "Feistel.h"
#include "KeySchedule.h"
#include "Mapper.h"

TEST(FeistelTest, Test_Feistel) {
  uint64_t plaintext = 0x0123456789ABCDEFULL;
  uint64_t key = 0x133457799BBCDFF1ULL;

  uint64_t keys[16] = {0};
  KeySchedule::generate_schedule(key, keys);

  uint64_t ip_block = Mapper::apply_map(plaintext, IP);

  uint64_t result =
      Feistel::apply_sixteen_feistel_rounds(ip_block, keys, false);

  EXPECT_EQ(result, 0x0A4CD99543423234ULL);
}

TEST(FeistelTest, SixteenRoundsFromKnownL0R0) {
  uint64_t block = 0xCC00CCFFF0AAF0AAULL;
  uint64_t key = 0x133457799BBCDFF1ULL;

  uint64_t keys[16] = {0};
  KeySchedule::generate_schedule(key, keys);

  uint64_t result = Feistel::apply_sixteen_feistel_rounds(block, keys, false);

  EXPECT_EQ(result, 0x0A4CD99543423234ULL);
}