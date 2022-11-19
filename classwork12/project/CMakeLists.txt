cmake_minimum_required(VERSION 3.10)

project(rational_framework)
set(CMAKE_CXX_STANDARD 17)

set(PROGRAM_SRCS
    tests/test_complex.cpp
    include/src/Rational.cpp
    include/src/Complex.cpp
)

include_directories(
    include/

)

add_executable(amogus ${PROGRAM_SRCS})
