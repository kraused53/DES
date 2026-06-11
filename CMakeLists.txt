###############################################################################
### Setup
###############################################################################
cmake_minimum_required( VERSION 3.20 )
project( DES CXX )

set( CMAKE_CXX_STANDARD 20 )

###############################################################################
### Options
###############################################################################
option(DES_BUILD_TESTS "Build unit tests" ON)

enable_testing()

###############################################################################
### External Libraries
###############################################################################
include( FetchContent )

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable( spdlog )

###############################################################################
### DES Core Functions As A Static Library
###############################################################################
add_library( des_lib STATIC
        src/Mapper.cpp
        # src/KeySchedule.cpp   ← uncomment as you add components
        # src/Feistel.cpp
)

target_include_directories( des_lib PUBLIC include )
target_link_libraries( des_lib PUBLIC spdlog::spdlog )

###############################################################################
### Compilation Flags
###############################################################################
if(MSVC)
    target_compile_options(des_lib PRIVATE /W4)
else()
    target_compile_options(des_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()


###############################################################################
### Define Main Executable
###############################################################################
add_executable( DES src/main.cpp )
target_link_libraries( DES PRIVATE des_lib )

###############################################################################
### Unit Tests
###############################################################################
if(DES_BUILD_TESTS)
    include(CTest)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(
        des_tests
        tests/test_mapper.cpp
    )

    target_link_libraries(
        des_tests
        PRIVATE
        des_lib
        GTest::gtest_main
    )

        include(GoogleTest)
        gtest_discover_tests(des_tests)
endif()