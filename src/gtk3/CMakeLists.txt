

set(TARGET_NAME klog-gtk3)

file(GLOB GTK3_H_FILES ./*.h)
file(GLOB GTK3_CPP_FILES ./*.cpp)


add_library(${TARGET_NAME} SHARED
            ${GTK3_H_FILES}
            ${GTK3_CPP_FILES})

target_include_directories(${TARGET_NAME} PRIVATE
                           ${PROJECT_SOURCE_DIR}
                           ${PROJECT_SOURCE_DIR}/include
                           ${GLIBMM_INCLUDE_DIRS}
                           ${ZLOG_INCLUDE_DIRS})

target_link_libraries(${TARGET_NAME} PRIVATE
                      ${GLIBMM_LIBRARIES}
                      ${ZLOG_LIBRARIES})

set_target_properties(${TARGET_NAME} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION 1)

install(TARGETS ${TARGET_NAME} DESTINATION ${KLOG_LIBDIR})