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
