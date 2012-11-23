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

#include <QCoreApplication>
#include <QStringList>
#include <iostream>
#include "securefileuploader.h"

void showSyntax();
QString getPassword();
void upload(const QString &orig, const QString &dest, const QString passwd);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        showSyntax();
    }

    QString orig = argv[1];
    QString dest = argv[2];
    QString passwd = getPassword();

    upload(orig, dest, passwd);

    return a.exec();
}


void showSyntax()
{
    std::cerr << "Syntax: " << std::endl;
    std::cerr << "         SecureUploader local_file username@host:/destination_path" << std::endl;
    exit(1);
}


QString getPassword()
{
    std::cout << "Password (Warning password will be echoed): ";
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
            uploader.upload(orig, l2[1], l2[0], l1[0], passwd);
        } else {
            std::cerr << "SecureUploader:  Error invalid parameter " << dest.toStdString() << std::endl;
            showSyntax();
        }
    } else {
        std::cerr << "SecureUploader:  Error invalid parameter " << dest.toStdString() << std::endl;
        showSyntax();
    }
}
