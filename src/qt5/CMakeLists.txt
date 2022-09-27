cmake_minimum_required(VERSION 2.8.12)

set(TARGET_NAME klog-qt5)

set(KIRAN_LOG_QT5_API_VERSION 2)

file(GLOB QT5_H_FILES ./*.h)
file(GLOB QT5_CPP_FILES ./*.cpp)

add_library(${TARGET_NAME} SHARED ${QT5_H_FILES} ${QT5_CPP_FILES})

set_target_properties(
  ${TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
                            SOVERSION ${KIRAN_LOG_QT5_API_VERSION})

target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core lib-zlog-ex)

target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                                                  ${PROJECT_SOURCE_DIR}/)

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
