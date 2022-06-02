
include(GNUInstallDirs)

set(KLOG_INCLUDEDIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/${PROJECT_NAME})

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
  set (CMAKE_CXX_FLAGS "-std=c++0x")
else ()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED on)
endif()

option (ENABLE_ZLOG_EX "Enable zlog extension" ON)
option (ENABLE_TEST "Enable test" OFF)
