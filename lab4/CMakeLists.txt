project(lab4
        LANGUAGES CXX)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_lab(4
        TEST_SOURCES figure_test.cpp
)
