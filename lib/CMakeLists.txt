cmake_minimum_required(VERSION 2.8.12)

set(TARGET_NAME lib-zlog-ex)

add_library(${TARGET_NAME} STATIC zlog-ex.h zlog-ex.cpp)

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}
                                                 ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${TARGET_NAME} PUBLIC ${ZLOG_LIBRARY})

target_compile_options(${TARGET_NAME} PRIVATE -fPIC)
