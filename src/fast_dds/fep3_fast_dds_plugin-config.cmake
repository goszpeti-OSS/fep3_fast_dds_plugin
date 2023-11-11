if(fep3_fast_dds_plugin_FOUND)
    return()
endif()


# Add imported library target for the participant cpp interface
include(${CMAKE_CURRENT_LIST_DIR}/lib/cmake/fep3_fast_dds_plugin-macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/cmake/fep3_fast_dds_plugin_targets.cmake)

set(fep3_participant_core_FOUND true)
