//
// Created by Danny on 6/11/2026.
//

#include <gtest/gtest.h>
#include <cstdint>
#include "Mapper.h"

static const uint8_t IPMAP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

static const uint8_t FPMAP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

static const uint8_t EMAP[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

static const uint8_t PMAP[32] = {
    16,  7, 20, 21, 
    29, 12, 28, 17, 
     1, 15, 23, 26, 
     5, 18, 31, 10, 
     2,  8, 24, 14, 
    32, 27,  3,  9, 
    19, 13, 30,  6, 
    22, 11,  4, 25
};

static const uint8_t PC1MAP[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

static const uint8_t PC2MAP[48] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

/*
    Initial Permutation Testing
*/
TEST(MapperTest, IP_Exhaustive) {
    for (int i = 0; i < 64; i++) {
        uint64_t test_value = 1ULL << (64 - IPMAP[i]);
        uint64_t result = Mapper::apply_map(test_value, IP);

        EXPECT_EQ(result, (1ULL << (63 - i)));
    }
}

TEST( MapperTest, IP_PermutationTest ) {
    uint64_t input_value  = 0b0000000100100011010001010110011110001001101010111100110111101111;
    uint64_t output_value = 0b1100110000000000110011001111111111110000101010101111000010101010;
    EXPECT_EQ( Mapper::apply_map(input_value, IP), output_value );
}

/*
    Final Permutation Testing
*/
TEST(MapperTest, FP_Exhaustive) {
    for (int i = 0; i < 64; i++) {
        uint64_t test_value = 1ULL << (64 - FPMAP[i]);
        uint64_t result = Mapper::apply_map(test_value, FP);

        EXPECT_EQ(result, (1ULL << (63 - i)));
    }
}

TEST( MapperTest, FP_PermutationTest ) {
    uint64_t input_value  = 0b1100110000000000110011001111111111110000101010101111000010101010;
    uint64_t output_value = 0b0000000100100011010001010110011110001001101010111100110111101111;
    EXPECT_EQ( Mapper::apply_map(input_value, FP), output_value );
}

/*
    Expansion Map Testing
*/
TEST(MapperTest, E_Exhaustive) {
    for (int i = 0; i < 48; i++) {
        uint64_t input = 1ULL << (32 - EMAP[i]);

        uint64_t result = Mapper::apply_map(input, E);

        EXPECT_TRUE(result & (1ULL << (47 - i)));
    }
}

TEST( MapperTest, E_PermutationTest ) {
    uint64_t input_value  = 0b11110000101010101111000010101010;
    uint64_t output_value = 0b011110100001010101010101011110100001010101010101;
    EXPECT_EQ( Mapper::apply_map(input_value, E), output_value );
}

/*
    Permutation Testing
*/
TEST(MapperTest, P_Exhaustive) {
    for (int i = 0; i < 32; i++) {
        uint64_t test_value = 1ULL << (32 - PMAP[i]);

        uint64_t result = Mapper::apply_map(test_value, P);

        EXPECT_EQ(result, (1ULL << (31 - i)));
    }
}

TEST( MapperTest, P_PermutationTest ) {
    uint64_t input_value  = 0b01011100100000101011010110010111;
    uint64_t output_value = 0b00100011010010101010100110111011;
    EXPECT_EQ( Mapper::apply_map(input_value, P), output_value );
}

/*
    Permutation Choice 1 Testing
*/
TEST(MapperTest, PC1_Exhaustive) {
    for (int i = 0; i < 56; i++) {
        uint64_t input = 1ULL << (64 - PC1MAP[i]);

        uint64_t result = Mapper::apply_map(input, PC1);

        EXPECT_TRUE(result & (1ULL << (55 - i)));
    }
}

TEST( MapperTest, PC1_PermutationTest ) {
    uint64_t input_value  = 0b0001001100110100010101110111100110011011101111001101111111110001;
    uint64_t output_value = 0b11110000110011001010101011110101010101100110011110001111;
    EXPECT_EQ( Mapper::apply_map(input_value, PC1), output_value );
}

/*
    Permutation Choice 2 Testing
*/
TEST(MapperTest, PC2_Exhaustive) {
    for (int i = 0; i < 48; i++) {
        uint64_t input = 1ULL << (56 - PC2MAP[i]);

        uint64_t result = Mapper::apply_map(input, PC2);

        EXPECT_TRUE(result & (1ULL << (47 - i)));
    }
}

TEST( MapperTest, PC2_PermutationTest ) {
    uint64_t input_value  = 0b11100001100110010101010111111010101011001100111100011110;
    uint64_t output_value = 0b000110110000001011101111111111000111000001110010;
    EXPECT_EQ( Mapper::apply_map(input_value, PC2), output_value );
}