
macro(fep_fast_dds_plugin_install NAME DESTINATION)
    fep3_participant_install(${NAME} ${DESTINATION})
    install(FILES
            $<TARGET_FILE:fep3_fast_dds_plugin>
        DESTINATION ${DESTINATION}/fast_dds
    )
     # overwrite fep_components file
    install(FILES
            $<TARGET_FILE_DIR:fep3_fast_dds_plugin>/../fep3_participant.fep_components
        DESTINATION ${DESTINATION}
    )
    # user qos file is mandatory
    install(FILES
            $<TARGET_FILE_DIR:fep3_fast_dds_plugin>/USER_QOS_PROFILES.xml
        DESTINATION ${DESTINATION}/fast_dds
    )
endmacro(fep_fast_dds_install DESTINATION)

macro(fep_fast_dds_plugin_deploy NAME)
    fep3_participant_deploy(${NAME})
    add_custom_command(TARGET ${NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                $<TARGET_FILE_DIR:${NAME}>/fast_dds
    )
    # no need to copy in build directory on linux since linker rpath takes care of that
    if (WIN32)
        add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:fep3_fast_dds_plugin>
            $<TARGET_FILE_DIR:${NAME}>/fast_dds)
    endif()

    # always need a fep_components file for the native components plugin
    add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:fep3_fast_dds_plugin>/fep3_participant.fep_components
            $<TARGET_FILE_DIR:${NAME}>
    )
    # always need a fep_components file for the native components plugin
    add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:fep3_fast_dds_plugin>/USER_QOS_PROFILES.xml
            $<TARGET_FILE_DIR:${NAME}>/fast_dds
    )

endmacro(fep_fast_dds_plugin_deploy NAME)

