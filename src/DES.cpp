#include "DES.h"

#include "Feistel.h"
#include "KeySchedule.h"
#include "Mapper.h"
#include "spdlog/spdlog.h"

uint64_t DES::encrypt(uint64_t block, uint64_t key) {
  // Permute the given block
  spdlog::info("Applying initial permutation...");
  uint64_t permuted_block = Mapper::apply_map(block, IP);
  spdlog::debug("Permuted Block: {:016X}", permuted_block);

  // Generate keys
  uint64_t keys[16] = {0};
  KeySchedule::generate_schedule(key, keys);

  uint64_t block_after_feistel_rounds =
      Feistel::apply_sixteen_feistel_rounds(permuted_block, keys, false);

  spdlog::info("Applying final permutation...");
  uint64_t final_block = Mapper::apply_map(block_after_feistel_rounds, FP);
  spdlog::debug("Final Block: 0x{:016X}", final_block);
  return final_block;
}

uint64_t DES::decrypt(uint64_t block, uint64_t key) {
  // Permute the given block
  spdlog::info("Applying initial permutation...");
  uint64_t permuted_block = Mapper::apply_map(block, IP);
  spdlog::debug("Permuted Block: 0x{:016X}", permuted_block);

  // Generate keys
  uint64_t keys[16] = {0};
  KeySchedule::generate_schedule(key, keys);

  uint64_t block_after_feistel_rounds =
      Feistel::apply_sixteen_feistel_rounds(permuted_block, keys, true);

  spdlog::info("Applying final permutation...");
  uint64_t final_block = Mapper::apply_map(block_after_feistel_rounds, FP);
  spdlog::debug("Final Block: 0x{:016X}", final_block);
  return final_block;
}