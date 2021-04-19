cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)

if (BUILD_TESTING)

    etn_test(${PROJECT_NAME}-test
        INCLUDE_DIRS
            ../include
        SOURCES
            ../src/*.cc
            src/*.cc
        PREPROCESSOR -DCATCH_CONFIG_FAST_COMPILE
        USES
            cxxtools
            fty_common
            fty_common_logging
            fty_common_messagebus
            fty_common_dto
            Catch2::Catch2
            stdc++fs
            log4cplus
    )

    #enable coverage
    etn_coverage(${PROJECT_NAME}-test)

endif()
