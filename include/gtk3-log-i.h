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

#pragma once

#include <glibmm.h>
#include <functional>
#include <string>

/**
 * @brief 初始化日志库，安装Qt日志输出回调
 * @param config        zlog配置文件
 * @param cname         zlog分类名
 * @param project_name  项目名称
 * @param program_name  二进制程序名
 * @return 是否初始化成功，当返回值为0表示成功
 */

int klog_gtk3_init(const std::string& config,
                   const std::string& cname,
                   const std::string& project_name,
                   const std::string& program_name);

void klog_gtk3_append(GLogLevelFlags log_level,
                      const std::string& file_name,
                      const std::string& function_name,
                      int32_t line_number,
                      const char* format, ...);

#define CONNECTION(text1, text2) text1##text2
#define CONNECT(text1, text2) CONNECTION(text1, text2)

#if __cplusplus > 201101L

class KLogDefer
{
public:
    KLogDefer(std::function<void(std::string)> func, std::string fun_name) : func_(func),
                                                                             fun_name_(fun_name) {}
    ~KLogDefer() { func_(fun_name_); }

private:
    std::function<void(std::string)> func_;
    std::string fun_name_;
};

// helper macro for Defer class
#define KLOG_SCOPE_EXIT(block) KLogDefer CONNECT(_defer_, __LINE__)([&](std::string _arg_function) block, __FUNCTION__)

#else
#define KLOG_SCOPE_EXIT(block)
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define KLOG_FATAL(format, ...)            \
    do                                     \
    {                                      \
        klog_gtk3_append(G_LOG_FLAG_FATAL, \
                         __FILENAME__,     \
                         __FUNCTION__,     \
                         __LINE__,         \
                         format,           \
                         ##__VA_ARGS__);   \
    } while (0)

#define KLOG_ERROR(format, ...)             \
    do                                      \
    {                                       \
        klog_gtk3_append(G_LOG_LEVEL_ERROR, \
                         __FILENAME__,      \
                         __FUNCTION__,      \
                         __LINE__,          \
                         format,            \
                         ##__VA_ARGS__);    \
    } while (0)

#define KLOG_WARNING(format, ...)             \
    do                                        \
    {                                         \
        klog_gtk3_append(G_LOG_LEVEL_WARNING, \
                         __FILENAME__,        \
                         __FUNCTION__,        \
                         __LINE__,            \
                         format,              \
                         ##__VA_ARGS__);      \
    } while (0)

#define KLOG_INFO(format, ...)             \
    do                                     \
    {                                      \
        klog_gtk3_append(G_LOG_LEVEL_INFO, \
                         __FILENAME__,     \
                         __FUNCTION__,     \
                         __LINE__,         \
                         format,           \
                         ##__VA_ARGS__);   \
    } while (0)

#define KLOG_DEBUG(format, ...)             \
    do                                      \
    {                                       \
        klog_gtk3_append(G_LOG_LEVEL_DEBUG, \
                         __FILENAME__,      \
                         __FUNCTION__,      \
                         __LINE__,          \
                         format,            \
                         ##__VA_ARGS__);    \
    } while (0)

#define KLOG_PROFILE_START(format, ...)     \
    do                                      \
    {                                       \
        klog_gtk3_append(G_LOG_LEVEL_DEBUG, \
                         __FILENAME__,      \
                         __FUNCTION__,      \
                         __LINE__,          \
                         "START " format,   \
                         ##__VA_ARGS__);    \
    } while (0)

#define KLOG_PROFILE_END(format, ...)       \
    do                                      \
    {                                       \
        klog_gtk3_append(G_LOG_LEVEL_DEBUG, \
                         __FILENAME__,      \
                         __FUNCTION__,      \
                         __LINE__,          \
                         "END " format,     \
                         ##__VA_ARGS__);    \
    } while (0)

#define KLOG_PROFILE(format, ...)                         \
    klog_gtk3_append(G_LOG_LEVEL_DEBUG,                   \
                     __FILENAME__,                        \
                     __FUNCTION__,                        \
                     __LINE__,                            \
                     "START " format,                     \
                     ##__VA_ARGS__);                      \
    KLOG_SCOPE_EXIT({ klog_gtk3_append(G_LOG_LEVEL_DEBUG, \
                                       __FILENAME__,      \
                                       _arg_function,     \
                                       __LINE__,          \
                                       "END " format,     \
                                       ##__VA_ARGS__); });
