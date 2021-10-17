cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)

project(fty_srr_rest
  VERSION "1.0.0"
  DESCRIPTION "Save, restore and reset REST API for 42ity project"
  LANGUAGES CXX)

##############################################################################################################
find_package(fty-cmake PATHS ${CMAKE_BINARY_DIR}/fty-cmake)
find_package(fty-cmake-rest PATHS ${CMAKE_BINARY_DIR}/fty-cmake-rest)
resolve_lib(tntnet)
##############################################################################################################

# Define the servlet
etn_target(shared ${PROJECT_NAME}
    SOURCES
        src/fty_srr_helpers.cc
        src/fty_srr_helpers.h
    USES
        czmq
        fty-cmake-rest
        cxxtools
        tntnet
        tntdb
        fty_common
        fty_common_logging
        fty_common_rest
        fty_common_messagebus
        fty_common_dto
)

# Get the ecpp
file(GLOB ECPP_FILES
  ecpp/*.ecpp
)

# Transform ecpp files
fty_ecppbuilder(
  TARGET ${PROJECT_NAME}
  WORKDIR src
  ECPP
    ${ECPP_FILES}
)

# Install tntnet mapping file in etc/tntnet/bios.d/
install(FILES ${PROJECT_SOURCE_DIR}/resources/40_srr-rest.xml DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/tntnet/bios.d/)

etn_test_target(${PROJECT_NAME}
    SOURCES
        tests/*.cc
    PREPROCESSOR -DCATCH_CONFIG_FAST_COMPILE
    USES
        stdc++fs
)
