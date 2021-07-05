/**
 * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd. 
 *
 * Author:     tangjie02 <tangjie02@kylinos.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
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
