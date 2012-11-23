#include "securefileuploader.h"

#include <QtDebug>

SecureFileUploader::SecureFileUploader(QObject *parent) :
    QObject(parent), m_connection(0)
{
}

void SecureFileUploader::upload(const QString &localFile, const QString &dest, const QString &host,
                                const QString &username, const QString &passwd)
{
    qDebug() << localFile << dest << host << username << passwd;

    m_localFilename = localFile;
    m_remoteFilename = dest + "/" + localFile;

    QSsh::SshConnectionParameters params;
    params.host = host;
    params.userName = username;
    params.password = passwd;
    params.authenticationType = QSsh::SshConnectionParameters::AuthenticationByPassword;
    params.timeout = 30;
    params.port = 22;

    m_connection = new QSsh::SshConnection(params, this); // TODO free this pointer!

    connect(m_connection, SIGNAL(connected()), SLOT(onConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(onConnectionError(QSsh::SshError)));

    qDebug() << " SecureUploader: Connecting to host" << host;

    m_connection->connectToHost();
}

void SecureFileUploader::onConnected()
{
    qDebug() << " SecureUploader: Connected";
    qDebug() << " SecureUploader: Creating SFTP channel...";

    m_channel = m_connection->createSftpChannel();

    if (m_channel) {
        connect(m_channel.data(), SIGNAL(initialized()),
                SLOT(onChannelInitialized()));
        connect(m_channel.data(), SIGNAL(initializationFailed(QString)),
                SLOT(onChannelError(QString)));
        connect(m_channel.data(), SIGNAL(finished(QSsh::SftpJobId, QString)),
                SLOT(onOpfinished(QSsh::SftpJobId, QString)));

        m_channel->initialize();

    } else {
        qDebug() << " SecureUploader: Error null channel";
    }
}

void SecureFileUploader::onConnectionError(QSsh::SshError err)
{
    qDebug() << " SecureUploader: Connection error" << err;
}

void SecureFileUploader::onChannelInitialized()
{
    qDebug() << " SecureUploader: Channel Initialized";

    // TODO Choose the overwrite mode: SftpOverwriteExisting, SftpAppendToExisting, SftpSkipExisting
    QSsh::SftpJobId job = m_channel->uploadFile(m_localFilename, m_remoteFilename,
                                                QSsh::SftpOverwriteExisting);

    if (job != QSsh::SftpInvalidJob) {
        qDebug() << " SecureUploader: Starting job #" << job;
    } else {
        qDebug() << " SecureUploader: Invalid Job";
    }
}

void SecureFileUploader::onChannelError(const QString &err)
{
    qDebug() << " SecureUploader: Error: " << err;
}

void SecureFileUploader::onOpfinished(QSsh::SftpJobId job, const QString &err)
{
    qDebug() << " SecureUploader: Finished job #" << job << ":" << (err.isEmpty() ? "OK" : err);
}





