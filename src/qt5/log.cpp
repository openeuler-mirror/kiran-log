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

#include "src/qt5/log.h"

#ifdef ENABLE_ZLOG_EX
#include <zlog_ex.h>
#else
#include <zlog.h>
#endif
#include <QLoggingCategory>
#include <QMutex>
#include <iostream>

static QMap<QtMsgType, zlog_level> msgDescMap = {
    {QtDebugMsg, ZLOG_LEVEL_DEBUG},
    {QtWarningMsg, ZLOG_LEVEL_WARN},
    {QtCriticalMsg, ZLOG_LEVEL_ERROR},
    {QtFatalMsg, ZLOG_LEVEL_FATAL},
    {QtInfoMsg, ZLOG_LEVEL_INFO},
};

int klog_qt5_init(const QString& config,
                  const QString& cname,
                  const QString& project_name,
                  const QString& program_name)
{
    return Log::instance()->init(config, cname, project_name, program_name);
}

/**
 * @brief qInstallMessageHandler回调函数
 * @param type     Qt日志消息类型
 * @param context  Qt日志消息上下文(暂时不用,直接将相关信息拼凑到消息主体中)
 * @param msg      Qt日志消息主体
 */
void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    Log::instance()->appendLog(type, context, msg);
}

Log* Log::instance()
{
    static QMutex mutex;
    static QScopedPointer<Log> pInst;

    if (Q_UNLIKELY(!pInst))
    {
        QMutexLocker locker(&mutex);
        if (pInst.isNull())
        {
            pInst.reset(new Log);
        }
    }

    return pInst.data();
}

Log::~Log()
{
}

int Log::init(const QString& config, const QString& cname, const QString& projectName, const QString& programName)
{
    if (isInited())
    {
        std::cerr << "kiran-log-qt5 is already inited!" << std::endl;
        return 0;
    }

#ifdef ENABLE_ZLOG_EX
    auto result = dzlog_init_ex(config.isEmpty() ? nullptr : config.toLatin1().data(),
                                cname.toLatin1().data(),
                                projectName.toLatin1().data(),
                                programName.toLatin1().data());
#else
    auto result = dzlog_init(config.isEmpty() ? "/etc/zlog.conf" : config.toLatin1().data(), cname.toLatin1().data());
#endif

    if (result != 0)
    {
        std::cerr << "zlog init failed!" << std::endl;
        return -1;
    }

    qInstallMessageHandler(messageHandler);

    //输出所有的分类类别，Qt日志框架不做过滤，交由zlog的配置文件进行配置过滤
    QLoggingCategory* loggingCategory = QLoggingCategory::defaultCategory();
    for (auto iter = msgDescMap.begin(); iter != msgDescMap.end(); iter++)
    {
        if (!loggingCategory->isEnabled(iter.key()))
        {
            loggingCategory->setEnabled(iter.key(), true);
        }
    }

    m_isInited = true;
    return 0;
}

void Log::appendLog(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    if (!isInited())
    {
        std::cerr << "not initialized,call klog_qt5_init first" << std::endl;
        std::cerr << msg.toStdString() << std::endl;
        return;
    }

    std::string fileName = context.file ? context.file : "no-file";
    std::string function = context.function ? context.function : "no-func";
    int line = context.line;
    std::string strMsg = msg.toStdString();

    auto zlogLevelIter = msgDescMap.find(type);
    if (zlogLevelIter == msgDescMap.end())
    {
        std::cerr << "can't find zlog level." << std::endl;
        return;
    }

    dzlog(fileName.c_str(),
          fileName.size(),
          function.c_str(),
          function.size(),
          line,
          zlogLevelIter.value(),
          "%s",
          strMsg.c_str());
}

Log::Log()
    : m_isInited(false)
{
}

bool Log::isInited()
{
    return m_isInited;
}
