/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/
#include "directtunnel.h"

#include <ssh/sshconnection.h>
#include <ssh/sshdirecttcpiptunnel.h>

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include <cstdlib>
#include <iostream>

const QByteArray ServerDataPrefix("Received the following data: ");
const QByteArray TestData("Urgsblubb?");

using namespace QSsh;

DirectTunnel::DirectTunnel(const SshConnectionParameters &parameters, QObject *parent)
    : QObject(parent),
      m_connection(new SshConnection(parameters, this)),
      m_targetServer(new QTcpServer(this)),
      m_expectingChannelClose(false)
{
    connect(m_connection, SIGNAL(connected()), SLOT(handleConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(handleConnectionError()));
}

DirectTunnel::~DirectTunnel()
{
}

void DirectTunnel::run()
{
    std::cout << "Connecting to SSH server..." << std::endl;
    m_connection->connectToHost();
}

void DirectTunnel::handleConnectionError()
{
    std::cerr << "SSH connection error: " << qPrintable(m_connection->errorString()) << std::endl;
    emit finished(EXIT_FAILURE);
}

void DirectTunnel::handleConnected()
{
    std::cout << "Opening server side..." << std::endl;
    if (!m_targetServer->listen(QHostAddress::LocalHost)) {
        std::cerr << "Error opening port: "
                << m_targetServer->errorString().toLocal8Bit().constData() << std::endl;
        emit finished(EXIT_FAILURE);
        return;
    }
    m_targetPort = m_targetServer->serverPort();
    connect(m_targetServer, SIGNAL(newConnection()), SLOT(handleNewConnection()));

    m_tunnel = m_connection->createDirectTunnel(QLatin1String("localhost"), 1024, // made-up values
                                                QLatin1String("localhost"), m_targetPort);
    connect(m_tunnel.data(), SIGNAL(initialized()), SLOT(handleInitialized()));
    connect(m_tunnel.data(), SIGNAL(error(QString)), SLOT(handleTunnelError(QString)));
    connect(m_tunnel.data(), SIGNAL(readyRead()), SLOT(handleServerData()));
    connect(m_tunnel.data(), SIGNAL(aboutToClose()), SLOT(handleTunnelClosed()));

    std::cout << "Initializing tunnel..." << std::endl;
    m_tunnel->initialize();
}

void DirectTunnel::handleInitialized()
{
    std::cout << "Writing data into the tunnel..." << std::endl;
    m_tunnel->write(TestData);
    QTimer * const timeoutTimer = new QTimer(this);
    connect(timeoutTimer, SIGNAL(timeout()), SLOT(handleTimeout()));
    timeoutTimer->start(10000);
}

void DirectTunnel::handleServerData()
{
    m_dataReceivedFromServer += m_tunnel->readAll();
    if (m_dataReceivedFromServer == ServerDataPrefix + TestData) {
        std::cout << "Data exchange successful. Closing server socket..." << std::endl;
        m_expectingChannelClose = true;
        m_targetSocket->close();
    }
}

void DirectTunnel::handleTunnelError(const QString &reason)
{
    std::cerr << "Tunnel error: " << reason.toLocal8Bit().constData() << std::endl;
    emit finished(EXIT_FAILURE);
}

void DirectTunnel::handleTunnelClosed()
{
    if (m_expectingChannelClose) {
        std::cout << "Successfully detected channel close." << std::endl;
        std::cout << "Test finished successfully." << std::endl;
        emit finished(EXIT_SUCCESS);
    } else {
        std::cerr << "Error: Remote host closed channel." << std::endl;
        emit finished(EXIT_FAILURE);
    }
}

void DirectTunnel::handleNewConnection()
{
    m_targetSocket = m_targetServer->nextPendingConnection();
    m_targetServer->close();
    connect(m_targetSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(handleSocketError()));
    connect(m_targetSocket, SIGNAL(readyRead()), SLOT(handleClientData()));
    handleClientData();
}

void DirectTunnel::handleSocketError()
{
    std::cerr << "Socket error: " << m_targetSocket->errorString().toLocal8Bit().constData()
            << std::endl;
    emit finished(EXIT_FAILURE);
}

void DirectTunnel::handleClientData()
{
    m_dataReceivedFromClient += m_targetSocket->readAll();
    if (m_dataReceivedFromClient == TestData) {
        std::cout << "Client data successfully received by server, now sending data to client..."
                << std::endl;
        m_targetSocket->write(ServerDataPrefix + m_dataReceivedFromClient);
    }
}

void DirectTunnel::handleTimeout()
{
    std::cerr << "Error: Timeout waiting for test completion." << std::endl;
    emit finished(EXIT_FAILURE);
}
