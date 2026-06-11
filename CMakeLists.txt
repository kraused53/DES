###############################################################################
### Setup
###############################################################################
cmake_minimum_required( VERSION 4.2 )
project( DES CXX )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )

set( CMAKE_CXX_STANDARD 20 )

###############################################################################
### Options
###############################################################################
if(PROJECT_IS_TOP_LEVEL)
    option(DES_BUILD_TESTS "Build unit tests" ON)
else()
    option(DES_BUILD_TESTS "Build unit tests" OFF)
endif()

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

if(DES_BUILD_TESTS)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.15.2
    )
    # Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable( googletest )
endif()

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
if(PROJECT_IS_TOP_LEVEL)
    if(MSVC)
        target_compile_options(des_lib PRIVATE /W4)
    else()
        target_compile_options(des_lib PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

###############################################################################
### Define Main Executable
###############################################################################
add_executable( DES src/main.cpp )
target_link_libraries( DES PRIVATE des_lib )

###############################################################################
### Define Testing Location
###############################################################################
if(DES_BUILD_TESTS)
    enable_testing()
    add_subdirectory( tests )
endif()