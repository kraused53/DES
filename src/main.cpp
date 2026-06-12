#include <spdlog/spdlog.h>

#include <cstdint>

#include "Mapper.h"

int main() {
  uint64_t value = 0x0123456789ABCDEF;
  uint64_t key = 0x133457799BBCDFF1;
  spdlog::info("########################################");
  spdlog::info("### ----- Initial  Permutation ----- ###");
  spdlog::info("########################################");
  spdlog::info("Data: 0x{:016X}", value);
  spdlog::info("  IP: 0x{:016X}", Mapper::apply_map(value, IP));

  spdlog::info("########################################");
  spdlog::info("### --------- Key Schedule --------- ###");
  spdlog::info("########################################");
  spdlog::info("  Initial Key Value: 0x{:016X}", key);
  spdlog::info("Key Value After PC1: 0x{:016X}", Mapper::apply_map(key, PC1));

  return 0;
}
