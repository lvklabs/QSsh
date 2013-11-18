#include <QtCore/QCoreApplication>
#include "botanAES256.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BotanAES256 cWrapper;

   // QString cPlain = "/home/rootshell/Source/Wraper/test.txt";
   // QString cEncrypted = "/home/rootshell/Source/Wraper/encrypted.txt";
   // QString cDecrypted = "/home/rootshell/Source/Wraper/decrypted.txt";

   // cWrapper.EncryptFile(cPlain,cEncrypted);
   // cWrapper.DecryptFile(cEncrypted,cDecrypted);
    QString str("Hello Chinese! 95328 <你好中国>");
    QString cEnc = cWrapper.Encrypt(str);

    qDebug() << str;
    qDebug() << cEnc;
    QString str2(cWrapper.Decrypt(cEnc));
    qDebug() << str2;
    if( str == str2)
    {
        qDebug() << "ture";
    }
    else
    {
        qDebug()<< "false";
    }
    


    return a.exec();
}
