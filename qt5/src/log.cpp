#include "log.h"

#include <zlog_ex.h>
#include <QMutex>
#include <iostream>

/**
 * @brief qInstallMessageHandler回调函数
 * @param type     Qt日志消息类型
 * @param context  Qt日志消息上下文(暂时不用,直接将相关信息拼凑到消息主体中)
 * @param msg      Qt日志消息主体
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
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

bool Log::init(const QString& config, const QString& cname, const QString& projectName, const QString& programName)
{
    if(!isInited())
    {
        return true;
    }

    if (dzlog_init_ex(config.toLatin1().data(),
                      cname.toLatin1().data(),
                      programName.toLatin1().data(),
                      programName.toLatin1().data()) != 0)
    {
        std::cerr << "zlog init failed!" << std::endl;
        return false;
    }

    qInstallMessageHandler(messageHandler);
    m_isInited = true;
    return true;
}

void Log::appendLog(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    static QMap<QtMsgType, zlog_level> msgDescMap = {
        {QtDebugMsg, ZLOG_LEVEL_DEBUG},
        {QtWarningMsg, ZLOG_LEVEL_WARN},
        {QtCriticalMsg, ZLOG_LEVEL_ERROR},
        {QtFatalMsg, ZLOG_LEVEL_FATAL},
        {QtInfoMsg, ZLOG_LEVEL_INFO},
    };

    if (!isInited())
    {
        std::cerr << "not initialized,call Log::init" << std::endl;
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
