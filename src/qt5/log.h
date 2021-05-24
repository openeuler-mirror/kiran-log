#ifndef __KIRAN_LOG_QT5_H__
#define __KIRAN_LOG_QT5_H__

#include <QDebug>
#include <QString>
#include <QtGlobal>
class Log
{
    friend void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

public:
    /**
     * @brief: 获取Log类单例
     * @return Log类单例
     */
    static Log *instance();
    ~Log();

    /**
     * @brief: 初始化zlog日志库,注册Qt日志消息回调方法
     * \param config       zlog配置文件 @see zlog_ex.h dzlog_init_ex
     * \param cname        zlog分类名 @see zlog_ex.h dzlog_init_ex
     * \param projectName  项目名称 @see zlog_ex.h dzlog_init_ex
     * \param programName  二进制程序名 @see zlog_ex.h dzlog_init_ex
     * \return 是否初始化成功，当返回值为0表示成功
     */
    int init(const QString &config,
             const QString &cname,
             const QString &projectName,
             const QString &programName);

    /**
     * @brief: 获取是否初始化完成
     * \return 是否初始化完成
     */
    bool isInited();

private:
    Log();
    void appendLog(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    bool m_isInited;
};

#endif  //__KIRAN_LOG_QT5_H__
