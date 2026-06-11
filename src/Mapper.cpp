#include <spdlog/spdlog.h>

#include "Mapper.h"


uint64_t Mapper::apply_map(uint64_t initial_value, MAP map) {
    uint64_t result = 0;

    switch ( map ) {
        case IP:
            result = apply_map_helper( initial_value, iIP, 64, 64 );
            break;
        case FP:
            result = apply_map_helper( initial_value, iFP, 64, 64 );
            break;
        case E:
        case P:
        case PC1:
        case PC2:
        case S1:
        case S2:
        case S3:
        case S4:
        case S5:
        case S6:
        case S7:
        case S8:
        default:
            spdlog::error( "This map has not been implemented yet..." );
            break;
    }

    return result;
}

uint64_t Mapper::apply_map_helper(uint64_t ival, const uint8_t *map, uint8_t isize, uint8_t msize) {
    uint64_t result = 0;
    for (int i = 0; i < msize; i++) {
        result <<= 1;
        result |= (ival >> (isize-map[i])) & 1;
    }
    return result;
}
