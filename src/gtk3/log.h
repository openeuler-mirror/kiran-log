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
