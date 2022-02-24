
# pc file
file(GLOB PC_IN_FILES ./*.pc.in)

foreach(PC_IN_FILE IN LISTS PC_IN_FILES)
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" PC_FILE ${PC_IN_FILE})
    configure_file(${PC_IN_FILE} ${PROJECT_BINARY_DIR}/data/${PC_FILE})

    install(FILES ${PROJECT_BINARY_DIR}/data/${PC_FILE}
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig)
endforeach()
