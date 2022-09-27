cmake_minimum_required(VERSION 2.8.12)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
  project(kiran-log VERSION 2.1.0)
else()
  project(kiran-log)
  set(PROJECT_VERSION 2.1.0)
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(KL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core)

find_library(ZLOG_LIBRARY zlog REQUIRED)

pkg_search_module(GLIBMM REQUIRED glibmm-2.4)

configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(data)
add_subdirectory(lib)
add_subdirectory(src)

if(ENABLE_TEST)
  pkg_search_module(GTEST REQUIRED gtest)
  add_subdirectory(test)
endif()

install(FILES ${PROJECT_SOURCE_DIR}/include/qt5-log-i.h
              ${PROJECT_SOURCE_DIR}/include/gtk3-log-i.h
        DESTINATION ${KLOG_INCLUDEDIR})
