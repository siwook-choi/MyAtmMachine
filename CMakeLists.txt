cmake_minimum_required(VERSION 3.10)
project(my_atm_machine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
    extern/tinyfsm/include
)

set(SOURCES
    src/account-info.cpp
    src/atm-machine.cpp
    src/atm-state.cpp
    src/cash-card.cpp
    src/operation-result.cpp
    src/pin-number.cpp
)

add_library(
    ${PROJECT_NAME}_lib
    ${SOURCES}
)

enable_testing()

if(CMAKE_TESTING_ENABLED)
    add_subdirectory(extern/googletest)

    set(TEST_SOURCES
        test/main.cpp
        test/test-atm-state.cpp
    )

    add_executable(${PROJECT_NAME}_test
        ${TEST_SOURCES})

    target_link_libraries(
        ${PROJECT_NAME}_test
        PRIVATE
        ${PROJECT_NAME}_lib
        GTest::gmock
        GTest::gtest
        GTest::gmock_main
        GTest::gtest_main)
endif()
