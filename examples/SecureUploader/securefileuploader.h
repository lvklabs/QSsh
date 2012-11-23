/**************************************************************************
**
** This file is part of QSsh
**
** Copyright (c) 2012 LVK
**
** Contact: andres.pagliano@lvklabs.com
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
**************************************************************************/

#ifndef SECUREFILEUPLOADER_H
#define SECUREFILEUPLOADER_H

#include <QObject>

#include "sftpchannel.h"
#include "sshconnection.h"

/// Very simple example to upload a file using FTPS
class SecureFileUploader : public QObject
{
    Q_OBJECT
public:

    explicit SecureFileUploader(QObject *parent = 0);

    /// Uploads \a localFile to \a username@host:/dest using password \a passwd
    void upload(const QString &localFile, const QString &dest, const QString &host,
                const QString &username, const QString &passwd);

signals:

private slots:
    void onConnected();
    void onConnectionError(QSsh::SshError);
    void onChannelInitialized();
    void onChannelError(const QString &err);
    void onOpfinished(QSsh::SftpJobId job, const QString & error = QString());

private:
    QString m_localFilename;
    QString m_remoteFilename;
    QSsh::SftpChannel::Ptr m_channel;
    QSsh::SshConnection *m_connection;

    void parseDestination(const QString &dest);
};

#endif // SECUREFILEUPLOADER_H
