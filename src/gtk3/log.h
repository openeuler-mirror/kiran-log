/**
 * @file          /kiran-log/src/gtk3/gtk3-log.h
 * @brief         
 * @author        tangjie02 <tangjie02@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved. 
 */

#pragma once

#include <glibmm.h>

namespace Kiran
{
class Log
{
public:
    Log();
    Log(const Log &) = delete;
    virtual ~Log(){};

    static Log *get_instance() { return instance_; };

    static void global_init();

    static void global_deinit();

    void try_append(GLogLevelFlags log_level,
                    const std::string &file_name,
                    const std::string &function_name,
                    int32_t line_number,
                    const char *message);

private:
    void init();

    static void log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);

private:
    static Log *instance_;
};
}  // namespace Kiran
