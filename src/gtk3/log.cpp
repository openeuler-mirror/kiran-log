/**
 * @file          /kiran-log/src/gtk3/log.cpp
 * @brief         
 * @author        tangjie02 <tangjie02@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved. 
 */

#include "src/gtk3/log.h"

#include <zlog_ex.h>

int klog_gtk3_init(const std::string &config,
                   const std::string &cname,
                   const std::string &project_name,
                   const std::string &program_name)
{
    static bool is_init = false;

    if (!is_init)
    {
        is_init = true;

        auto result = dzlog_init_ex(config.empty() ? NULL : config.c_str(),
                                    cname.c_str(),
                                    project_name.c_str(),
                                    program_name.c_str());

        Kiran::Log::global_init();

        return result;
    }
    return 0;
}

void klog_gtk3_append(GLogLevelFlags log_level,
                      const std::string &file_name,
                      const std::string &function_name,
                      int32_t line_number,
                      const char *format, ...)
{
    static const int kMessageSize = 10240;
    char message[kMessageSize];
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsnprintf(message, kMessageSize, format, arg_ptr);
    va_end(arg_ptr);

    Kiran::Log::get_instance()->try_append(log_level,
                                           file_name.c_str(),
                                           function_name.c_str(),
                                           line_number,
                                           message);
}

namespace Kiran
{
Log::Log()
{
}

Log *Log::instance_ = nullptr;
void Log::global_init()
{
    instance_ = new Log();
    instance_->init();
}

void Log::global_deinit()
{
    delete instance_;
    instance_ = nullptr;
}

void Log::try_append(GLogLevelFlags log_level,
                     const std::string &file_name,
                     const std::string &function_name,
                     int32_t line_number,
                     const char *message)
{
    int32_t priority;

    switch (log_level & G_LOG_LEVEL_MASK)
    {
    case G_LOG_FLAG_FATAL:
        priority = ZLOG_LEVEL_FATAL;
        break;
    case G_LOG_LEVEL_ERROR:
        priority = ZLOG_LEVEL_ERROR;
        break;
    case G_LOG_LEVEL_CRITICAL:
        priority = ZLOG_LEVEL_ERROR;
        break;
    case G_LOG_LEVEL_WARNING:
        priority = ZLOG_LEVEL_WARN;
        break;
    case G_LOG_LEVEL_MESSAGE:
        priority = ZLOG_LEVEL_NOTICE;
        break;
    case G_LOG_LEVEL_INFO:
        priority = ZLOG_LEVEL_INFO;
        break;
    case G_LOG_LEVEL_DEBUG:
        priority = ZLOG_LEVEL_DEBUG;
        break;
    default:
        priority = ZLOG_LEVEL_DEBUG;
        break;
    }

    dzlog(file_name.c_str(),
          file_name.length(),
          function_name.c_str(),
          function_name.length(),
          line_number,
          priority,
          "%s",
          message);
}

void Log::init()
{
    g_log_set_default_handler(log_handler, this);
}

void Log::log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
    Log *log = (Log *)user_data;
    if (!log)
    {
        return;
    }

    log->try_append(log_level, "gtk-file", "gtk-function", 0, message);
}

}  // namespace Kiran