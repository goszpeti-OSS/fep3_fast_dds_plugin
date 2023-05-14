find_package(Threads)
find_package(GTest CONFIG REQUIRED COMPONENTS gtest gtest_main gmock gmock_main)

include(GoogleTest)

if (WIN32 AND CMAKE_CL_64)
    add_definitions(-DWIN64)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (UNIX AND CMAKE_BUILD_WITH_INSTALL_RPATH)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
endif()

add_subdirectory(fast_dds/src)
