#pragma once
#include <cstdint>
#include "../Bitset/Bitset.h"

namespace Horizon::Bits {
    struct BitVector
    {
        size_t size;     // logical size
        size_t capacity; // allocated capacity
        Bitset bitset;   // storage
    };

    // ---------- API ----------
    bool BitVector_Init(BitVector& bv, size_t capacityBits);
    void BitVector_Free(BitVector& bv);
    void BitVector_Clear(BitVector& bv);
    bool BitVector_Reserve(BitVector& bv, size_t newCapacityBits);

    bool BitVector_AppendBit(BitVector& bv, bool value, bool& out);
    bool BitVector_SetBit(const BitVector& bv, size_t idx, bool value);
    bool BitVector_GetBit(const BitVector& bv, size_t idx, bool& out);
    bool BitVector_FlipBit(BitVector& bv, size_t idx);
}
