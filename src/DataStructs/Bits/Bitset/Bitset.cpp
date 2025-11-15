#include <cstdlib>
#include <cstring>
#include "Bitset.h"

namespace Horizon::Bits {
    bool Bitset_Init(Bitset& bitset, const size_t bitCount)
    {
        if (bitset.blocks != nullptr) Bitset_Free(bitset);
        bitset.numBits = bitCount;
        const size_t blocks = BitsToBlocks(bitCount);

        if (blocks == 0)
        {
            bitset.blocks = nullptr;
            return true;
        }

        bitset.blocks = static_cast<uint64_t*>(malloc(blocks * sizeof(uint64_t)));
        if (!bitset.blocks) return false;

        memset(bitset.blocks, 0, blocks * sizeof(uint64_t));
        return true;
    }

    void Bitset_Free(Bitset& bitset)
    {
        if (bitset.blocks != nullptr) {
            free(bitset.blocks);
            bitset.blocks = nullptr;
            bitset.numBits = 0;
        }
    }

    void Bitset_ClearBitsTo(const Bitset& bitset, const bool value)
    {
        if (!bitset.blocks) return;

        const size_t numBytes = (bitset.numBits + 7) / 8; // round up to full bytes
        memset(bitset.blocks, value ? 0xFF : 0x00, numBytes);
    }

    bool Bitset_Set(const Bitset& bitset, const size_t index, const bool value)
    {
        if (!bitset.blocks || index >= bitset.numBits) return false;

        const size_t block = IndexToBlock(index);
        const uint64_t mask = BitMask(index);

        if (value) bitset.blocks[block] |= mask;
        else bitset.blocks[block] &= ~mask;

        return true;
    }

    bool Bitset_Get(const Bitset& bitset, const size_t index, bool& out)
    {
        if (!bitset.blocks || index >= bitset.numBits) return false;

        const size_t block = IndexToBlock(index);
        out = (bitset.blocks[block] & BitMask(index)) != 0;

        return true;
    }

    bool Bitset_Flip(Bitset& bitset, const size_t index)
    {
        if (!bitset.blocks || index >= bitset.numBits) return false;

        const size_t block = IndexToBlock(index);
        bitset.blocks[block] ^= BitMask(index);

        return true;
    }
} // namespace Horizon::Bits
