cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME klog-qt5)

set(KIRAN_LOG_QT5_API_VERSION 1)

file (GLOB QT5_H_FILES ./*.h)
file (GLOB QT5_CPP_FILES ./*.cpp)

add_library(${TARGET_NAME} SHARED 
            ${QT5_H_FILES}
            ${QT5_CPP_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES
        VERSION   ${PROJECT_VERSION}
        SOVERSION ${KIRAN_LOG_QT5_API_VERSION})

target_link_libraries(${TARGET_NAME} PRIVATE
        Qt5::Core)

target_include_directories(${TARGET_NAME} PRIVATE
                           ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_SOURCE_DIR}/)

if (ENABLE_ZLOG_EX)
        target_link_libraries(${TARGET_NAME} PRIVATE
                              ${ZLOG_LIBRARIES})

        target_include_directories(${TARGET_NAME} PRIVATE
                                   ${ZLOG_INCLUDE_DIRS})
else()
        target_link_libraries(${TARGET_NAME} PRIVATE
                              ${ZLOG_LIBRARY})
endif()

install(TARGETS ${TARGET_NAME} DESTINATION ${KLOG_LIBDIR})