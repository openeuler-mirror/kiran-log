/**
 * @file          /kiran-log/test/test-gtk3.cpp
 * @brief         
 * @author        tangjie02 <tangjie02@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved. 
 */

#include <gtest/gtest.h>
#include "config.h"
#include "gtk3-log-i.h"

#define DEBUG_MESSAGE "This is a debug."
#define INFO_MESSAGE "This is a info."
#define WARNING_MESSAGE "This is a warning."

TEST(GTK3Test, GTK3LogTest)
{
    KLOG_PROFILE("");

    auto filename = Glib::build_filename(Glib::get_home_dir(), "/.cache/kylinsec/" PROJECT_NAME "/klog-gtk3-tests.log");

    KLOG_DEBUG(DEBUG_MESSAGE);
    KLOG_INFO(INFO_MESSAGE);
    KLOG_WARNING(WARNING_MESSAGE);

    ASSERT_TRUE(Glib::file_test(filename, Glib::FILE_TEST_IS_REGULAR));

    auto content = Glib::file_get_contents(filename);
    auto regex = Glib::Regex::create("\n");
    std::vector<std::string> lines = regex->split(content, Glib::REGEX_MATCH_NEWLINE_ANY);
    auto lines_size = lines.size();
    // 三行消息加一个空行
    ASSERT_TRUE(lines_size >= 4);
    ASSERT_TRUE(Glib::str_has_suffix(lines[lines_size - 4], DEBUG_MESSAGE));
    ASSERT_TRUE(Glib::str_has_suffix(lines[lines_size - 3], INFO_MESSAGE));
    ASSERT_TRUE(Glib::str_has_suffix(lines[lines_size - 2], WARNING_MESSAGE));
}

int main(int argc, char **argv)
{
    if (klog_gtk3_init(std::string(), "kylinsec-session", PROJECT_NAME, "klog-gtk3-tests") != 0)
    {
        std::cerr << "klog init failed." << std::endl;
    }

    Glib::init();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
