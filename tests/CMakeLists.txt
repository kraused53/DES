###############################################################################
### Define Mapper Testing
###############################################################################
add_executable(
        test_mapper
        test_mapper.cpp
)

target_link_libraries(
        test_mapper
        PRIVATE
            des_lib
            GTest::gtest_main
)

include( GoogleTest )
gtest_discover_tests( test_mapper )