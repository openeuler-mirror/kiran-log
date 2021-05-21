cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME klog-qt5)

#VERSION　 so版本
#影响生成的二进制共享库文件名 eg:libxxxx.so.${VERSION}
#格式:     主版本号-次版本号-发行版本号
#主版本:   不同主版本不兼容，主版本升级应需同时升级SOVERSION
#次版本:   增量升级，向后兼容
#发行版本: 对次版本的升级，不影响兼容

#SOVERSION API版本  影响安装做的软链接的名 eg:libxxx.so.${SOVERSION} -> libxxx.so.{VERSION}
#就是主版本号,程序链接的就是该符号

set(KIRAN_LOG_QT5_API_VERSION 1)

file (GLOB QT5_H_FILES ./*.h)
file (GLOB QT5_CPP_FILES ./*.cpp)

add_library(${TARGET_NAME} SHARED 
            ${QT5_H_FILES}
            ${QT5_CPP_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES
        VERSION   ${PROJECT_VERSION}
        SOVERSION ${KIRAN_LOG_QT5_API_VERSION})

target_link_libraries(${TARGET_NAME}
        Qt5::Core
        ${ZLOG_LIBRARIES})

target_include_directories(${TARGET_NAME} PRIVATE
                           ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_SOURCE_DIR}/
                           ${ZLOG_INCLUDE_DIRS})


install(TARGETS ${TARGET_NAME} DESTINATION ${KLOG_LIBDIR})