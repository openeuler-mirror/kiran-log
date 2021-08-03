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
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 */

#ifndef KIRAN_LOG_QT5_INCLUDE_LOG_I_H_
#define KIRAN_LOG_QT5_INCLUDE_LOG_I_H_

#ifdef ENABLE_ZLOG_EX
#include <zlog_ex.h>
#else
#include <zlog.h>
#endif

#include <QDebug>
#include <QtGlobal>

///NOTE:可见qlogging.h，未定义"QT_MESSAGELOGCONTEXT"将导致QDebug上下文没文件、行号、函数等信息,为了不影响Qt流程，直接使用QMessageLogger,将上下文信息塞入
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define KLOG_FATAL QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).fatal
#define KLOG_ERROR QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).critical
#define KLOG_WARNING QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).warning
#define KLOG_INFO QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).info
#define KLOG_DEBUG QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).debug

#ifdef ENABLE_ZLOG_EX
#define KLOG_COUT(format, ...)             \
    do                                     \
    {                                      \
        dzlog_cout(format, ##__VA_ARGS__); \
    } while (0);

#define KLOG_CSYS(format, ...)             \
    do                                     \
    {                                      \
        dzlog_csys(format, ##__VA_ARGS__); \
    } while (0);

#define KLOG_CERR(format, ...)             \
    do                                     \
    {                                      \
        dzlog_cerr(format, ##__VA_ARGS__); \
    } while (0);

#else
#define KLOG_COUT(format, ...)
#define KLOG_CSYS(format, ...)
#define KLOG_CERR(format, ...)
#endif
/**
 * @brief 初始化日志库，安装Qt日志输出回调
 * @param config        zlog配置文件
 * @param cname         zlog分类名
 * @param project_name  项目名称
 * @param program_name  二进制程序名
 * @return 是否初始化成功，当返回值为0表示成功
 */
int klog_qt5_init(const QString& config,
                  const QString& cname,
                  const QString& project_name,
                  const QString& program_name);

#endif  //KIRAN_LOG_QT5_INCLUDE_LOG_I_H_
