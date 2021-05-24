cmake_minimum_required(VERSION 3.2)

enable_testing()


# gtk3
set (GTK3_TARGET_NAME klog-gtk3-tests)
set (QT5_TARGET_NAME klog-qt5-tests)

add_executable(${GTK3_TARGET_NAME} test-gtk3.cpp)

target_include_directories(${GTK3_TARGET_NAME} PUBLIC
                           ${PROJECT_SOURCE_DIR}
                           ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_BINARY_DIR}
                           ${GLIBMM_INCLUDE_DIRS}
                           ${GTEST_INCLUDE_DIRS})           

target_link_libraries(${GTK3_TARGET_NAME} PRIVATE
                      ${GTEST_LIBRARIES}
                      ${GLIBMM_LIBRARIES}
                      klog-gtk3)

# qt5
add_executable(${QT5_TARGET_NAME} test-qt5.cpp)

find_package(Qt5 COMPONENTS Core)

target_include_directories(${QT5_TARGET_NAME} PUBLIC
                           ${PROJECT_SOURCE_DIR}
                           ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_BINARY_DIR}
                           ${GTEST_INCLUDE_DIRS})           

target_link_libraries(${QT5_TARGET_NAME} PRIVATE
                      Qt5::Core
                      ${GTEST_LIBRARIES}
                      klog-qt5)

# add_test(NAME test-gtk3 COMMAND ${GTK3_TARGET_NAME})
# add_test(NAME test-qt5 COMMAND ${QT5_TARGET_NAME})