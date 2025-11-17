//
// Created by Hosea on 11/14/2025.
//

// bitvector_tests.cpp
#include "../src/DataStructs/Bits/BitVector/BitVector.h"
#include <gtest/gtest.h>
using namespace Horizon::Bits;

// Utility
static bool GetBitValue(const BitVector& bitVector, size_t idx)
{
    bool val = false;
    bool ok = BitVector_GetBit(bitVector, idx, val);
    EXPECT_TRUE(ok) << "GetBit failed at index " << idx;
    return val;
}

TEST(BitVector, Init_ZeroCapacity)
{
    // Arrange
    BitVector bitVector{};

    // Act
    BitVector_Init(bitVector, 0);

    // Assert
    EXPECT_EQ(bitVector.size, 0);
    EXPECT_EQ(bitVector.capacity, 0);
    EXPECT_EQ(bitVector.bitset.blocks, nullptr);

    BitVector_Free(bitVector);
}

TEST(BitVector, Init_WithCapacity)
{
    // Arrange
    BitVector bitVector{};

    // Act
    BitVector_Init(bitVector, 64);

    // Assert
    EXPECT_EQ(bitVector.size, 0);
    EXPECT_EQ(bitVector.capacity, 64);
    EXPECT_NE(bitVector.bitset.blocks, nullptr);

    BitVector_Free(bitVector);
}

TEST(BitVector, Reserve_IncreaseCapacity)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 64);

    // Act
    bool ok = BitVector_Reserve(bitVector, 256);

    // Assert
    EXPECT_TRUE(ok);
    EXPECT_EQ(bitVector.capacity, 256);
    EXPECT_NE(bitVector.bitset.blocks, nullptr);

    BitVector_Free(bitVector);
}

TEST(BitVector, Reserve_DoesNotShrink)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 256);

    // Act
    bool ok = BitVector_Reserve(bitVector, 64);

    // Assert
    EXPECT_TRUE(ok);                 // logically successful call
    EXPECT_EQ(bitVector.capacity, 256);     // capacity must not shrink

    BitVector_Free(bitVector);
}

TEST(BitVector, SetAndGetBit)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 128);
    bitVector.size = 128;

    // Act
    EXPECT_TRUE(BitVector_SetBit(bitVector, 10, true));
    EXPECT_TRUE(BitVector_SetBit(bitVector, 64, true));
    EXPECT_TRUE(BitVector_SetBit(bitVector, 10, false));

    // Assert
    EXPECT_FALSE(GetBitValue(bitVector, 10));
    EXPECT_TRUE(GetBitValue(bitVector, 64));

    BitVector_Free(bitVector);
}

TEST(BitVector, FlipBit_Works)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 64);
    bitVector.size = 64;

    EXPECT_TRUE(BitVector_SetBit(bitVector, 7, false));

    // Act
    EXPECT_TRUE(BitVector_FlipBit(bitVector, 7)); // 0 -> 1
    EXPECT_TRUE(BitVector_FlipBit(bitVector, 7)); // 1 -> 0

    // Assert
    EXPECT_FALSE(GetBitValue(bitVector, 7));

    BitVector_Free(bitVector);
}

TEST(BitVector, AppendBit_ExpandsCapacity)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 1);

    bool out = false;

    // Act
    EXPECT_TRUE(BitVector_PushBack(bitVector, true, out));
    EXPECT_TRUE(out);

    EXPECT_TRUE(BitVector_PushBack(bitVector, false, out));
    EXPECT_FALSE(out);

    // Assert
    EXPECT_GE(bitVector.capacity, 2);
    EXPECT_EQ(bitVector.size, 2);
    EXPECT_TRUE(GetBitValue(bitVector, 0));
    EXPECT_FALSE(GetBitValue(bitVector, 1));

    BitVector_Free(bitVector);
}

TEST(BitVector, AppendBit_MultipleGrowthCycles)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 0);

    bool out = false;

    // Act — append many bits
    for (int i = 0; i < 1000; ++i)
    {
        bool val = (i % 2 == 0);
        EXPECT_TRUE(BitVector_PushBack(bitVector, val, out));
        EXPECT_EQ(out, val);
    }

    // Assert
    EXPECT_GE(bitVector.capacity, 1000);
    EXPECT_EQ(bitVector.size, 1000);

    for (int i = 0; i < 1000; ++i)
    {
        bool expected = (i % 2 == 0);
        EXPECT_EQ(GetBitValue(bitVector, i), expected);
    }

    BitVector_Free(bitVector);
}

TEST(BitVector, Clear_ResetsSizeAndBits)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 128);
    bitVector.size = 128;

    BitVector_SetBit(bitVector, 20, true);
    BitVector_SetBit(bitVector, 70, true);

    // Act
    BitVector_Clear(bitVector);

    // Assert
    EXPECT_EQ(bitVector.size, 0);

    bool val = true;
    EXPECT_FALSE(BitVector_GetBit(bitVector, 20, val)); // out of range
    EXPECT_FALSE(BitVector_GetBit(bitVector, 70, val)); // out of range

    BitVector_Free(bitVector);
}

TEST(BitVector, Delete_FreesMemory)
{
    // Arrange
    BitVector bitVector{};
    BitVector_Init(bitVector, 64);

    // Act
    BitVector_Free(bitVector);

    // Assert
    EXPECT_EQ(bitVector.bitset.blocks, nullptr);
    EXPECT_EQ(bitVector.size, 0);
    EXPECT_EQ(bitVector.capacity, 0);
}