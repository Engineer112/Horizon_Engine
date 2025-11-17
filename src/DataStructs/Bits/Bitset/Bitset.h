//
// Created by Hosea on 11/15/2025.
//

#pragma once
#include <cstdint>

namespace Horizon::Bits {
    struct Bitset
    {
        size_t numBits;     // number of bits in the set
        uint64_t* blocks;   // 64-bit blocks
    };

    inline size_t BitsToBlocks(const size_t bits) { return (bits + 63) >> 6; }
    inline size_t IndexToBlock(const size_t index) { return index >> 6; }
    inline uint64_t BitMask(const size_t index) { return uint64_t{1} << (index & 63); }


    bool Bitset_Init(Bitset& bitset, size_t bitCount);
    void Bitset_Free(Bitset& bitset);
    void Bitset_ClearBitsTo(const Bitset& bitset, bool value);

    bool Bitset_Set(const Bitset& bitset, size_t index, bool value);
    bool Bitset_Get(const Bitset& bitset, size_t index, bool& out);
    bool Bitset_Flip(const Bitset& bitset, size_t index);
}