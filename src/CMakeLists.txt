set(SRC_FILES
        DataStructs/Bits/BitVector/BitVector.cpp
        DataStructs/Bits/BitSet/Bitset.cpp
)

add_library(Horizon_Engine ${SRC_FILES})

# ------------------ Precompiled headers ------------------
target_precompile_headers(Horizon_Engine
        PRIVATE
        pch.h
)