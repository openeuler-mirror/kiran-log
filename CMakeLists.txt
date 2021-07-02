cmake_minimum_required(VERSION 3.5)

project(kiran-log VERSION 1.0.0)

list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(KL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core)

if (ENABLE_ZLOG_EX)
      pkg_search_module(ZLOG REQUIRED zlog)
else()
      find_library(ZLOG_LIBRARY zlog)
endif()

pkg_search_module(GLIBMM REQUIRED glibmm-2.4)
pkg_search_module(GTEST REQUIRED gtest)

configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(data)
add_subdirectory(src)
add_subdirectory(test)

install(FILES ${PROJECT_SOURCE_DIR}/include/qt5-log-i.h
              ${PROJECT_SOURCE_DIR}/include/gtk3-log-i.h
        DESTINATION ${KLOG_INCLUDEDIR})
