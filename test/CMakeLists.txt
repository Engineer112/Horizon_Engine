# -------------------------------
# Fetch GoogleTest
# -------------------------------
include(FetchContent)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
    set(gtest_build_tests OFF CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# -------------------------------
# Find test files
# -------------------------------
file(GLOB TEST_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

if(TEST_FILES STREQUAL "")
    message(STATUS "No test files found. Creating dummy test.")
    set(DUMMY_TEST "${CMAKE_CURRENT_BINARY_DIR}/dummy_test.cpp")

    file(WRITE ${DUMMY_TEST} "
#include <gtest/gtest.h>
TEST(DummyTest, AlwaysPasses) { EXPECT_TRUE(true); }
")

    list(APPEND TEST_FILES ${DUMMY_TEST})
endif()

# -------------------------------
# Create test executable
# -------------------------------
add_executable(unit_tests ${TEST_FILES}
        BitVector_tests.cpp
        Bitset_tests.cpp)

target_link_libraries(unit_tests PRIVATE
        gtest_main
        Horizon_Engine
)

# -------------------------------
# Register tests
# -------------------------------
include(GoogleTest)
gtest_discover_tests(unit_tests)
