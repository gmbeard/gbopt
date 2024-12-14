add_library(gbopt

    cmdline.cpp
    delimiter.cpp
)

add_library(GBopt::gbopt ALIAS gbopt)

target_include_directories(gbopt
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
