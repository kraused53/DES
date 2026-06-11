//
// Created by Danny on 6/11/2026.
//

#include <gtest/gtest.h>
#include "Mapper.h"

// NIST test vector: IP of a known value
TEST(MapperTest, IPKnownVector) {
    // Input bit 58 maps to output bit 1 per the IP table
    uint64_t input = 0x8000000000000000ULL >> (58 - 1);
    uint64_t result = Mapper::apply_map(input, IP);
    EXPECT_EQ(result, 0x8000000000000000ULL);
}