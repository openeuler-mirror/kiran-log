/**
 * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd. 
 *
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
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
