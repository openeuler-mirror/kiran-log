/**
 * @file          /kiran-log/include/gtk3/log-i.h
 * @brief         
 * @author        tangjie02 <tangjie02@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved. 
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

class Defer
{
public:
    Defer(std::function<void(std::string)> func, std::string fun_name) : func_(func),
                                                                         fun_name_(fun_name) {}
    ~Defer() { func_(fun_name_); }

private:
    std::function<void(std::string)> func_;
    std::string fun_name_;
};

// helper macro for Defer class
#define SCOPE_EXIT(block) Defer CONNECT(_defer_, __LINE__)([&](std::string _arg_function) block, __FUNCTION__)
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

#define KLOG_PROFILE(format, ...)                    \
    klog_gtk3_append(G_LOG_LEVEL_DEBUG,              \
                     __FILENAME__,                   \
                     __FUNCTION__,                   \
                     __LINE__,                       \
                     "START " format,                \
                     ##__VA_ARGS__);                 \
    SCOPE_EXIT({ klog_gtk3_append(G_LOG_LEVEL_DEBUG, \
                                  __FILENAME__,      \
                                  _arg_function,     \
                                  __LINE__,          \
                                  "END " format,     \
                                  ##__VA_ARGS__); });
