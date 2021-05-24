/**
 * @file          /kiran-log/include/qt5/log-i.h
 * @brief         
 * @author        tangjie02 <tangjie02@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved. 
 */

#ifndef KIRAN_LOG_QT5_INCLUDE_LOG_I_H_
#define KIRAN_LOG_QT5_INCLUDE_LOG_I_H_

#include <zlog_ex.h>
#include <QDebug>
#include <QtGlobal>

///NOTE:可见qlogging.h，未定义"QT_MESSAGELOGCONTEXT"将导致QDebug上下文没文件、行号、函数等信息,为了不影响Qt流程，直接使用QMessageLogger,将上下文信息塞入

///NOTE:
/// LOG_XX()    以c语言类似传参数，不支持Qt内部相关类直接打印输出，和qDebug("%s","hello world")使用方法一样
/// LOG_XX_S()  以流的形式传递参数，支持Qt内部相关类直接打印输出，和qDeubg() << "hello world" << QString << QStringList使用方法一样

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define KLOG_FATAL(format, ...)                                                            \
    do                                                                                     \
    {                                                                                      \
        QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).fatal(format, ##__VA_ARGS__); \
    } while (0)
#define KLOG_FATAL_S QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).fatal

#define KLOG_ERROR(format, ...)                                                               \
    do                                                                                        \
    {                                                                                         \
        QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).critical(format, ##__VA_ARGS__); \
    } while (0)
#define KLOG_ERROR_S QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).critical

#define KLOG_WARNING(format, ...)                                                            \
    do                                                                                       \
    {                                                                                        \
        QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).warning(format, ##__VA_ARGS__); \
    } while (0)
#define KLOG_WARNING_S QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).warning

#define KLOG_INFO(format, ...)                                                            \
    do                                                                                    \
    {                                                                                     \
        QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).info(format, ##__VA_ARGS__); \
    } while (0)
#define KLOG_INFO_S QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).info

#define KLOG_DEBUG(format, ...)                                                            \
    do                                                                                     \
    {                                                                                      \
        QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).debug(format, ##__VA_ARGS__); \
    } while (0)
#define KLOG_DEBUG_S QMessageLogger(__FILENAME__, __LINE__, __FUNCTION__).debug

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
