include(MakeTest)
#include_directories(${PROJECT_SOURCE_DIR}/src)
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(testing OBJECT testing.cpp)

# NOTE:
#  Use -DGBOPT_ENABLE_TEST_CATEGORIES="val1;val2" to control the
#  ENABLE_IF flags

make_test(
    NAME cmdline_tests
    SOURCES cmdline_tests.cpp
    LINK_LIBRARIES GBopt::gbopt
)
