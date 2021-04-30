cmake_minimum_required(VERSION 3.5)
project(kiran-log-qt5)

set(CMAKE_CXX_STANDARD 11)

#VERSION　 so版本
#影响生成的二进制共享库文件名 eg:libxxxx.so.${VERSION}
#格式:     主版本号-次版本号-发行版本号
#主版本:   不同主版本不兼容，主版本升级应需同时升级SOVERSION
#次版本:   增量升级，向后兼容
#发行版本: 对次版本的升级，不影响兼容
set(KIRAN_LOG_QT5_VERSION     1.0.0)

#SOVERSION API版本  影响安装做的软链接的名 eg:libxxx.so.${SOVERSION} -> libxxx.so.{VERSION}
#就是主版本号,程序链接的就是该符号
set(KIRAN_LOG_QT5_API_VERSION 1)

find_package(Qt5 COMPONENTS Core)
find_package(PkgConfig REQUIRED)
pkg_search_module(ZLOG REQUIRED zlog)

add_library(${PROJECT_NAME} SHARED src/log.cpp src/log.h)
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION   ${KIRAN_LOG_QT5_VERSION}
        SOVERSION ${KIRAN_LOG_QT5_API_VERSION})
target_link_libraries(${PROJECT_NAME} Qt5::Core ${ZLOG_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${ZLOG_INCLUDE_DIRS})

include(GNUInstallDirs)
set(KIRAN_LOG_QT5_LIB_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${PROJECT_NAME} DESTINATION ${KIRAN_LOG_QT5_LIB_DIR})

set(DEVEL_HEADERS "src/log.h")
set(KIRAN_LOG_QT5_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/kiran-log/qt5)
install(FILES ${DEVEL_HEADERS} DESTINATION ${KIRAN_LOG_QT5_INCLUDE_DIR})

configure_file("./data/kiran-log-qt5.pc.in" ${CMAKE_BINARY_DIR}/kiran-log-qt5.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/kiran-log-qt5.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig)