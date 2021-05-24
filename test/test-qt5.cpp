/**
 * @file          /kiran-log/test/test-qt5.cpp
 * @brief         
 * @author        tangjie02 <tangjie02@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved. 
 */
#include <gtest/gtest.h>
#include "config.h"
#include "qt5-log-i.h"

#define DEBUG_MESSAGE "This is a debug."
#define INFO_MESSAGE "This is a info."
#define WARNING_MESSAGE "This is a warning."

TEST(Qt5Test, Qt5LogTest)
{
    KLOG_DEBUG(DEBUG_MESSAGE);
    KLOG_INFO(INFO_MESSAGE);
    KLOG_WARNING(WARNING_MESSAGE);
}

int main(int argc, char **argv)
{
    if (klog_qt5_init("", "kylinsec-session", PROJECT_NAME, "klog-qt5-tests") != 0)
    {
        std::cerr << "klog init failed." << std::endl;
    }

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
