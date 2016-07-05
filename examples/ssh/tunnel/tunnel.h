/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#ifndef TUNNEL_H
#define TUNNEL_H

#include <QObject>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

namespace QSsh {
class SshConnection;
class SshConnectionParameters;
class SshDirectTcpIpTunnel;
}

class Tunnel : public QObject
{
    Q_OBJECT
public:
    Tunnel(const QSsh::SshConnectionParameters &parameters, QObject *parent = 0);
    ~Tunnel();

    void run();

private slots:
    void handleConnected();
    void handleConnectionError();
    void handleServerData();
    void handleInitialized();
    void handleTunnelError(const QString &reason);
    void handleTunnelClosed();
    void handleNewConnection();
    void handleSocketError();
    void handleClientData();
    void handleTimeout();

private:
    QSsh::SshConnection * const m_connection;
    QSharedPointer<QSsh::SshDirectTcpIpTunnel> m_tunnel;
    QTcpServer * const m_targetServer;
    QTcpSocket *m_targetSocket;
    quint16 m_targetPort;
    QByteArray m_dataReceivedFromServer;
    QByteArray m_dataReceivedFromClient;
    bool m_expectingChannelClose;
};

#endif // TUNNEL_H
