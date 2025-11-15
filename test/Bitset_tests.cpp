//
// Created by Hosea on 11/15/2025.
//

#include "../src/DataStructs/Bits/BitSet/Bitset.h"
#include <gtest/gtest.h>
using namespace Horizon::Bits;


TEST(Bitset, Init_ZeroCapacity) {
    Bitset bitset{};

    Bitset_Init(bitset, 0);

    EXPECT_EQ(bitset.blocks, nullptr);
    EXPECT_EQ(bitset.numBits, 0);

    Bitset_Free(bitset);
}

TEST(Bitset, Init_WithCapacity) {
    Bitset bitset{};

    Bitset_Init(bitset, 64);

    EXPECT_TRUE(bitset.blocks != nullptr);
    EXPECT_EQ(bitset.numBits, 64);

    Bitset_Free(bitset);
}

TEST(Bitset, Init_ReInitFreesAndReInits) {
    Bitset bitset{};

    // First init
    EXPECT_TRUE(Bitset_Init(bitset, 64));
    EXPECT_TRUE(bitset.blocks != nullptr);
    EXPECT_EQ(bitset.numBits, 64);

    // Reinit: should free old memory and reallocate
    EXPECT_TRUE(Bitset_Init(bitset, 128));
    EXPECT_TRUE(bitset.blocks != nullptr);
    EXPECT_EQ(bitset.numBits, 128);

    Bitset_Free(bitset);
}

TEST(Bitset, Free_DoubleCallDoesNothing) {
    Bitset bitset{};
    Bitset_Init(bitset, 64);

    // First free
    Bitset_Free(bitset);
    EXPECT_EQ(bitset.blocks, nullptr);
    EXPECT_EQ(bitset.numBits, 0);

    // Second free should not crash
    EXPECT_NO_THROW(Bitset_Free(bitset));
    EXPECT_EQ(bitset.blocks, nullptr);
    EXPECT_EQ(bitset.numBits, 0);
}

TEST(Bitset, GetAndSet_Works) {
    Bitset bitset{};
    Bitset_Init(bitset, 64);
    bool result = false;

    Bitset_Set(bitset, 7, true);
    Bitset_Get(bitset, 7, result);
    EXPECT_TRUE(result);

    Bitset_Set(bitset, 7, false);
    Bitset_Get(bitset, 7, result);
    EXPECT_FALSE(result);

    Bitset_Free(bitset);
}

TEST(Bitset, Flip_Works) {
    Bitset bitset{};
    Bitset_Init(bitset, 64);
    bool result;

    Bitset_Set(bitset, 9, true);
    Bitset_Flip(bitset, 9);

    Bitset_Get(bitset, 9, result);
    EXPECT_FALSE(result);

    Bitset_Free(bitset);
}

TEST(Bitset, ClearBitsTo_WorksWithTrue) {
    Bitset bitset{};
    Bitset_Init(bitset, 64);
    bool result;

    Bitset_ClearBitsTo(bitset, true);

    for (size_t i = 0; i < 64; ++i) {
        Bitset_Get(bitset, i, result);
        EXPECT_TRUE(result);
    }

    Bitset_Free(bitset);
}

TEST(Bitset, ClearBitsTo_WorksWithFalse) {
    Bitset bitset{};
    Bitset_Init(bitset, 64);
    bool result;

    Bitset_Set(bitset, 7, true);
    Bitset_Set(bitset, 9, true);
    Bitset_ClearBitsTo(bitset, false);

    for (size_t i = 0; i < 64; ++i) {
        Bitset_Get(bitset, i, result);
        EXPECT_FALSE(result);
    }
    Bitset_Free(bitset);
}

TEST(Bitset, GetSet_BoundaryIndices) {
    Bitset bitset{};
    Bitset_Init(bitset, 64);
    bool result = false;

    // First and last valid bits
    Bitset_Set(bitset, 0, true);
    Bitset_Set(bitset, 63, true);

    Bitset_Get(bitset, 0, result);
    EXPECT_TRUE(result);
    Bitset_Get(bitset, 63, result);
    EXPECT_TRUE(result);

    // Out-of-bounds: should not crash
    result = false;
    EXPECT_FALSE(Bitset_Get(bitset, 64, result));
    EXPECT_FALSE(Bitset_Get(bitset, 100, result));

    // Out-of-bounds set should do nothing
    Bitset_Set(bitset, 64, true);
    Bitset_Set(bitset, 100, true);

    Bitset_Get(bitset, 0, result);
    EXPECT_TRUE(result);
    Bitset_Get(bitset, 63, result);
    EXPECT_TRUE(result);

    Bitset_Free(bitset);
}

TEST(Bitset, MultiBit_SetClearFlipAcrossBlocksStillWorks) {
    Bitset bitset{};
    Bitset_Init(bitset, 130); // spans multiple uint64_t blocks
    bool result;

    // Set bits in different blocks
    Bitset_Set(bitset, 0, true);
    Bitset_Set(bitset, 63, true);
    Bitset_Set(bitset, 64, true);
    Bitset_Set(bitset, 129, true);

    Bitset_Get(bitset, 0, result); EXPECT_TRUE(result);
    Bitset_Get(bitset, 63, result); EXPECT_TRUE(result);
    Bitset_Get(bitset, 64, result); EXPECT_TRUE(result);
    Bitset_Get(bitset, 129, result); EXPECT_TRUE(result);

    // Flip some bits
    Bitset_Flip(bitset, 0);
    Bitset_Flip(bitset, 64);
    Bitset_Flip(bitset, 129);

    Bitset_Get(bitset, 0, result); EXPECT_FALSE(result);
    Bitset_Get(bitset, 63, result); EXPECT_TRUE(result);
    Bitset_Get(bitset, 64, result); EXPECT_FALSE(result);
    Bitset_Get(bitset, 129, result); EXPECT_FALSE(result);

    // Clear all bits to true
    Bitset_ClearBitsTo(bitset, true);
    for (size_t i = 0; i < 130; ++i) {
        Bitset_Get(bitset, i, result);
        EXPECT_TRUE(result);
    }

    Bitset_Free(bitset);
}

TEST(Bitset, Access_OutofBoundsIncludesSameBlock) {
    Bitset bitset{};
    Bitset_Init(bitset, 60);

    Bitset_Set(bitset, 63, true);

    bool result;
    EXPECT_FALSE(Bitset_Get(bitset, 63, result));

    Bitset_Free(bitset);
}