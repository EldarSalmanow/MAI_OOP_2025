function(setup_project)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.17.0
    )
    FetchContent_MakeAvailable(googletest)

    add_library(GTest::GTest INTERFACE IMPORTED)

    target_link_libraries(GTest::GTest INTERFACE gtest_main)

    add_compile_options(
            -Wall
            -Werror
            -Wextra
            -Wpedantic
    )

    enable_testing()
endfunction()

function(add_task TASK_NUM)
    # Parsing arguments

    cmake_parse_arguments(ARG "" "" "CLI_SOURCES;LIB_SOURCES;TEST_SOURCES" ${ARGN})

    set(TASK${TASK_NUM}_CLI_SOURCES)
    foreach(SOURCE ${ARG_CLI_SOURCES})
        list(APPEND
                TASK${TASK_NUM}_CLI_SOURCES
                ${CLI_DIR}/${SOURCE}
        )
    endforeach()

    set(TASK${TASK_NUM}_LIB_SOURCES)
    foreach(SOURCE ${ARG_LIB_SOURCES})
        list(APPEND
                TASK${TASK_NUM}_LIB_SOURCES
                ${SOURCE_DIR}/task${TASK_NUM}/${SOURCE}
        )
    endforeach()

    set(TASK${TASK_NUM}_TEST_SOURCES)
    foreach(SOURCE ${ARG_TEST_SOURCES})
        list(APPEND
                TASK${TASK_NUM}_TEST_SOURCES
                ${TESTS_DIR}/${SOURCE}
        )
    endforeach()

    # Adding library

    add_library(task${TASK_NUM}_lib
            ${TASK${TASK_NUM}_LIB_SOURCES}
    )

    target_include_directories(task${TASK_NUM}_lib
            PRIVATE
            ${INCLUDE_DIR}
    )

    # Adding CLI app

    add_executable(task${TASK_NUM}
            ${TASK${TASK_NUM}_CLI_SOURCES}
    )

    target_include_directories(task${TASK_NUM}
            PRIVATE
            ${INCLUDE_DIR}
    )

    target_link_libraries(task${TASK_NUM}
            PRIVATE
            task${TASK_NUM}_lib
    )

    # Adding tests

    add_executable(task${TASK_NUM}_test
            ${TASK${TASK_NUM}_TEST_SOURCES}
    )

    target_include_directories(task${TASK_NUM}_test
            PRIVATE
            GTest::GTest
            ${INCLUDE_DIR}
    )

    target_link_libraries(task${TASK_NUM}_test
            PRIVATE
            GTest::GTest
            task${TASK_NUM}_lib
    )

    add_test(
            NAME task${TASK_NUM}_tests
            COMMAND task${TASK_NUM}_test
    )
endfunction()
