#include <spdlog/spdlog.h>

#include <cstdint>

#include "DES.h"

int main(int argc, char** argv) {
  uint64_t value = 0;
  uint64_t key = 0;

  value = 0x0123456789ABCDEF;
  key = 0x133457799BBCDFF1;

  spdlog::set_level(spdlog::level::debug);
  spdlog::info("Starting DES tool");
  spdlog::info("Mode: Encryption");

  spdlog::debug("Plaintext block: 0x{:016X}", value);
  spdlog::debug("Plaintext key: 0x{:016X}", key);

  uint64_t ciphertext = DES::encrypt(value, key);

  spdlog::debug("Final Output...");
  spdlog::debug("Plaintext block: 0x{:016X}", value);
  spdlog::debug("Plaintext key: 0x{:016X}", key);
  spdlog::debug("Ciphertext key: 0x{:016X}", ciphertext);
  return 0;
}
