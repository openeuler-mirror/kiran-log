/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiran-log is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     tangjie02 <tangjie02@kylinos.com.cn>
 */

#include <gtest/gtest.h>
#include "config.h"
#include "qt5-log-i.h"

#define DEBUG_MESSAGE "This is a debug."
#define INFO_MESSAGE "This is a info."
#define WARNING_MESSAGE "This is a warning."
#define ERROR_MESSAGE "This is a error."

TEST(Qt5Test, Qt5LogTest)
{
    KLOG_DEBUG(DEBUG_MESSAGE);
    KLOG_DEBUG() << DEBUG_MESSAGE;

    KLOG_INFO(INFO_MESSAGE);
    KLOG_INFO() << INFO_MESSAGE;

    KLOG_WARNING(WARNING_MESSAGE);
    KLOG_WARNING() << WARNING_MESSAGE;

    KLOG_ERROR(ERROR_MESSAGE);
    KLOG_ERROR() << ERROR_MESSAGE;
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
