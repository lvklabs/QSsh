#include <QCoreApplication>

#include "securefileuploader.h"
#include <iostream>
#include <QStringList>

void showUsage();
QString getPassword();
void upload(const QString &orig, const QString &dest, const QString passwd);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        showUsage();
        return 1;
    }

    QString orig = argv[1];
    QString dest = argv[2];
    QString passwd = getPassword();

    upload(orig, dest, passwd);

    return a.exec();
}


void showUsage()
{
    std::cerr << "Usage:   SecureUploader localfile username@host:/destination" << std::endl;
}


QString getPassword()
{
    std::cout << "Password: (Warning password will be echoed)" << std::endl;
    std::string passwd;
    std::cin >> passwd;

    return QString::fromStdString(passwd).trimmed();
}


void upload(const QString &orig, const QString &dest, const QString passwd)
{
    // Parse destination with format "username@host:/destination"

    QStringList l1 = dest.split("@");

    if (l1.size() == 2) {
        QStringList l2 = l1[1].split(":");

        if (l2.size() == 2) {
            static SecureFileUploader uploader;
            uploader.upload(orig, l1[0], l2[0], l2[1], passwd);
        } else {
            std::cerr << " SecureUploader:  Error invalid destination " << dest.toStdString() << std::endl;
            showUsage();
        }
    } else {
        std::cerr << " SecureUploader:  Error invalid destination " << dest.toStdString() << std::endl;
        showUsage();
    }
}
