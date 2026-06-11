#include <spdlog/spdlog.h>
#include <cstdint>
#include "Mapper.h"


int main() {
    uint64_t value = 0x8000000000000000 >> ( 7 - 1 );
    uint64_t permutation = Mapper::apply_map( value, IP );
    spdlog::info( "Input:  {:064b}", value );
    spdlog::info( "Output: {:064b}", permutation );




    return 0;
}
