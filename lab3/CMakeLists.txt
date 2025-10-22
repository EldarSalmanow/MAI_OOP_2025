project(lab3
        LANGUAGES CXX)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_lab(3
        LIB_SOURCES point.cpp figure.cpp rhomb.cpp pentagon.cpp hexagon.cpp
        TEST_SOURCES figure_test.cpp
)
