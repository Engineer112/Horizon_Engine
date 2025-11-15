//
// BitVector — 64-bit block optimized version
//

#include "bitVector.h"
#include <cstdlib>
#include <cstring>
#include <cstdint>

namespace Horizon::Bits {
    bool BitVector_Init(BitVector& bitVector, const size_t capacityBits)
    {
        bitVector.size = 0;
        bitVector.capacity = capacityBits;
        return Bitset_Init(bitVector.bitset, capacityBits);
    }

    void BitVector_Free(BitVector& bitVector)
    {
        Bitset_Free(bitVector.bitset);
        bitVector.size = 0;
        bitVector.capacity = 0;
    }

    void BitVector_Clear(BitVector& bitVector)
    {
        bitVector.size = 0;
    }

    bool BitVector_Reserve(BitVector& bitVector, const size_t newCapacity)
    {
        if (newCapacity <= bitVector.capacity) return true;

        size_t oldBlocks = BitsToBlocks(bitVector.capacity);
        size_t newBlocks = BitsToBlocks(newCapacity);

        void* mem = realloc(bitVector.bitset.blocks, newBlocks * sizeof(uint64_t));
        if (!mem) return false;

        bitVector.bitset.blocks = static_cast<uint64_t*>(mem);
        memset(bitVector.bitset.blocks + oldBlocks, 0, (newBlocks - oldBlocks) * sizeof(uint64_t));

        bitVector.capacity = newCapacity;
        bitVector.bitset.numBits = newCapacity;
        return true;
    }

    bool BitVector_AppendBit(BitVector& bitVector, const bool value, bool& out)
    {
        const size_t index = bitVector.size;
        if (index >= bitVector.capacity)
        {
            const size_t newCap = (bitVector.capacity == 0) ? 64 : bitVector.capacity * 2;
            if (!BitVector_Reserve(bitVector, newCap)) return false;
        }

        bitVector.size++;
        Bitset_Set(bitVector.bitset, index, value);
        out = value;
        return true;
    }

    bool BitVector_SetBit(const BitVector& bitVector, const size_t index, const bool value) { return Bitset_Set(bitVector.bitset, index, value); }
    bool BitVector_GetBit(const BitVector& bitVector, const size_t index, bool& out) {
        if (index >= bitVector.size) return false;
        return Bitset_Get(bitVector.bitset, index, out);
    }
    bool BitVector_FlipBit(BitVector& bitVector, const size_t index) { return Bitset_Flip(bitVector.bitset, index); }

}