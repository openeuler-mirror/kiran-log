cmake_minimum_required(VERSION 3.5)

project(kiran-log VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core)

pkg_search_module(ZLOG REQUIRED zlog)
pkg_search_module(GLIBMM REQUIRED glibmm-2.4)
pkg_search_module(GTEST REQUIRED gtest)

include(GNUInstallDirs)
set(KLOG_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
set(KLOG_LIBDIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(data)
add_subdirectory(src)
add_subdirectory(test)

install(FILES ${PROJECT_SOURCE_DIR}/include/qt5-log-i.h
              ${PROJECT_SOURCE_DIR}/include/gtk3-log-i.h
        DESTINATION ${KLOG_INCLUDEDIR})
