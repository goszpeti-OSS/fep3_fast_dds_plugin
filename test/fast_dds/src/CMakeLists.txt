
# TODO: Get rid of this hack as soon as possible   ##
set(CMAKE_BUILD_TYPE ${CONAN_SETTINGS_BUILD_TYPE})  #
#####################################################

fep3_participant_create_copy_target(fast_dds)
set_target_properties(fep_participant_file_copy_fast_dds PROPERTIES FOLDER "test/private/plugins")
include_directories(${CMAKE_SOURCE_DIR}/test/)
include_directories(${CMAKE_SOURCE_DIR}/src/)

find_package(dev_essential REQUIRED COMPONENTS memory)
find_package(Boost REQUIRED)

add_executable(test_fast_dds_simulation_bus
    tester_dds_simbus.cpp
    tester_dds_simbus_version.cpp
    helper/platform_dep_name.cpp
    C:/Repos/fep3/fep3_fast_dds_plugin/src/fast_dds/types/stream_types.cxx
    C:/Repos/fep3/fep3_fast_dds_plugin/src/fast_dds/types/stream_typesPubSubTypes.cxx
    )
target_compile_options(test_fast_dds_simulation_bus PRIVATE "/Od")

target_include_directories(test_fast_dds_simulation_bus PRIVATE
    "${CMAKE_SOURCE_DIR}/src/plugins/fast_dds"
    "${CONAN_INCLUDE_DIRS_GTEST}"
    )

add_test(NAME test_fast_dds_simulation_bus
    COMMAND test_fast_dds_simulation_bus
    TIMEOUT 80
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
)
target_link_libraries(test_fast_dds_simulation_bus PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    dev_essential::memory
    dev_essential::system
    dev_essential::pkg_rpc

    fep_components_plugin
    fep3_participant_cpp_plugin
    fep3_participant
    fep3_fast_dds_plugin
    fastcdr
    fastrtps
    fast-dds::fast-dds
    )
include(${CMAKE_SOURCE_DIR}/src/fast_dds/fep3-fast-plugin-macros.cmake)
add_custom_command(TARGET test_fast_dds_simulation_bus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/src/fast_dds/USER_QOS_PROFILES.xml
    $<TARGET_FILE_DIR:test_fast_dds_simulation_bus>
)
add_custom_command(TARGET test_fast_dds_simulation_bus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:fep3_fast_dds_plugin>
    $<TARGET_FILE_DIR:test_fast_dds_simulation_bus>
)
fep3_participant_deploy(test_fast_dds_simulation_bus $<TARGET_FILE_DIR:test_fast_dds_simulation_bus>)


set_target_properties(test_fast_dds_simulation_bus PROPERTIES FOLDER "test/private/plugins")
target_compile_definitions(test_fast_dds_simulation_bus PRIVATE FEP3_DDS_BUS_SHARED_LIB="$<TARGET_FILE:fep3_fast_dds_plugin>")

add_dependencies(test_fast_dds_simulation_bus fep_participant_file_copy_fast_dds)
set_target_properties(test_fast_dds_simulation_bus PROPERTIES INSTALL_RPATH "$ORIGIN")

