cmake_minimum_required(VERSION 4.00)
project(Horizon_Engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

# ------------------ Unit Tests Config ------------------
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()