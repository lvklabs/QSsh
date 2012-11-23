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
