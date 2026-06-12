#include <gtest/gtest.h>

#include <cstdint>

#include "DES.h"

TEST(TestDES, Test_DESEncrypt) {
  uint64_t plaintext = 0x0123456789ABCDEF;
  uint64_t key = 0x133457799BBCDFF1;
  uint64_t ciphertext = DES::encrypt(plaintext, key);
  EXPECT_EQ(ciphertext, 0x85E813540F0AB405);
}

TEST(TestDES, Test_DESDecrypt) {
  uint64_t plaintext = 0x85E813540F0AB405;
  uint64_t key = 0x133457799BBCDFF1;
  uint64_t ciphertext = DES::decrypt(plaintext, key);
  EXPECT_EQ(ciphertext, 0x0123456789ABCDEF);
}