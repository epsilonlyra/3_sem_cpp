cmake_minimum_required(VERSION 3.10)

project(testing_numbers)
set(CMAKE_CXX_STANDARD 17)

set(PROGRAM_SRCS
    main.cpp
    include/src/Rational.cpp
    include/src/Complex.cpp
    include/src/Tester.cpp
    tests/test_rational.cpp
    tests/test_complex.cpp
)

include_directories(
    include/

)

add_executable(amogus ${PROGRAM_SRCS})
