#include "Feistel.h"

#include "KeySchedule.h"
#include "Mapper.h"
#include "SBox.h"
#include "spdlog/spdlog.h"

uint64_t Feistel::apply_sixteen_feistel_rounds(uint64_t block, uint64_t* keys,
                                               bool decrypt) {
  spdlog::info("Applying 16 rounds of feistel process...");
  uint32_t swap = 0;  // Used to swap left and right sides after each round
  // Split block into halves
  uint32_t left_hand_side = (block >> 32) & 0xFFFFFFFF;
  uint32_t right_hand_side = block & 0xFFFFFFFF;

  // Apply 16 feistel rounds
  for (int f_round = 0; f_round < 16; f_round++) {
    uint64_t expanded_block = Mapper::apply_map(right_hand_side, E);
    uint32_t feistel_output = 0;

    if (decrypt) {
      feistel_output = feistel_round(expanded_block, keys[15 - f_round]);
    } else {
      feistel_output = feistel_round(expanded_block, keys[f_round]);
    }

    spdlog::debug("Round {:2d}/16 feistel block: 0x{:016X}", f_round,
                  feistel_output);

    swap = right_hand_side;
    right_hand_side = left_hand_side ^ feistel_output;
    left_hand_side = swap;
  }

  spdlog::debug("Feistel result: 0x{:016X}",
                (((uint64_t)right_hand_side) << 32) | (uint64_t)left_hand_side);

  // Swap righthand subblock and lefthand subblock before returning
  return (((uint64_t)right_hand_side) << 32) | (uint64_t)left_hand_side;
}

uint8_t Feistel::extract_subblock(uint64_t block, int sbox_round) {
  return (uint8_t)(block >> (42 - (6 * sbox_round))) & 0x3F;
}

uint32_t Feistel::feistel_round(uint64_t block, uint64_t key) {
  uint32_t sbox_output = 0;  // Used to store SBox maps

  // Apply Key
  block ^= key;

  // Apply SBoxes
  for (int sbox_round = 0; sbox_round < 8; sbox_round++) {
    // Extract sub-block
    uint8_t sub_block = extract_subblock(block, sbox_round);

    // Shift previous sbox_putput out of th way
    sbox_output <<= 4;
    sbox_output |= SBox::apply(sub_block, sbox_round);
  }

  return (uint32_t)Mapper::apply_map(sbox_output, P);
}