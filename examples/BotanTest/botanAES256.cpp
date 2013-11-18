#include "BotanAES256.h"

BotanAES256::BotanAES256(QString password, QString salt, QObject *parent) :
    QObject(parent)
{
    //Set the default salt size
    mSalt.resize(48);

    QByteArray cBytes = salt.toLatin1();
    int i = 0,t = cBytes.size();
    for(unsigned int j = 0;j < mSalt.size(); j++,i++)
    {
        if( i >= t)
        {
            i = 0;
        }
        mSalt[j] = cBytes[i];
    }

    mPassword = Hash(password);
}

QString BotanAES256::Hash(QString Data)
{
    try
    {
        Pipe pipe(new Hash_Filter("SHA-1"));
        pipe.process_msg(Data.toStdString());
        QString Value = QString::fromStdString(pipe.read_all_as_string(0));
        return Value;
    }
    catch(...)
    {
        return "";
    }
}

QString BotanAES256::HexHash(QString Data)
{
    try
    {
        Pipe pipe(new Hash_Filter("SHA-1"), new Hex_Encoder);
        pipe.process_msg(Data.toStdString());
        QString Value = QString::fromStdString(pipe.read_all_as_string(0));
        return Value;
    }
    catch(...)
    {
        return "";
    }
}

QString BotanAES256::Encode(QString Data)
{
    try
    {
        Pipe pipe(new Base64_Encoder);
        pipe.process_msg(Data.toStdString());
        QString Value = QString::fromStdString(pipe.read_all_as_string(0));
        return Value;
    }
    catch(...)
    {
        return "";
    }
}

QString BotanAES256::Decode(QString Data)
{
    try
    {
        Pipe pipe(new Base64_Decoder);
        pipe.process_msg(Data.toStdString());
        QString Value = QString::fromStdString(pipe.read_all_as_string(0));
        return Value;
    }
    catch(...)
    {
        return "";
    }
}

QString BotanAES256::Encrypt(QString Data)
{
    try
    {
        //Setup the key derive functions
        PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
        const u32bit PBKDF2_ITERATIONS = 8192;

        //Create the KEY and IV
        KDF* kdf = get_kdf("KDF2(SHA-1)");

        //Create the master key
        SecureVector<byte> mMaster = pbkdf2.derive_key(48, mPassword.toStdString(), &mSalt[0], mSalt.size(),PBKDF2_ITERATIONS).bits_of();
        SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
        InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV,ENCRYPTION),new Base64_Encoder);
        pipe.process_msg(Data.toStdString());
        QString Value = QString::fromStdString(pipe.read_all_as_string(0));
        return Value;
    }
    catch(...)
    {
        return "";
    }
}

QString BotanAES256::Decrypt(QString Data)
{
    try
    {
        //Setup the key derive functions
        PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
        const u32bit PBKDF2_ITERATIONS = 8192;

        //Create the KEY and IV
        KDF* kdf = get_kdf("KDF2(SHA-1)");

        //Create the master key
        SecureVector<byte> mMaster = pbkdf2.derive_key(48, mPassword.toStdString(), &mSalt[0], mSalt.size(),PBKDF2_ITERATIONS).bits_of();
        SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
        InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        Pipe pipe(new Base64_Decoder,get_cipher("AES-256/CBC/PKCS7", mKey, mIV,DECRYPTION));
        pipe.process_msg(Data.toStdString());
        QString Value = QString::fromStdString(pipe.read_all_as_string(0));
        return Value;
    }
    catch(...)
    {
        return "";
    }
}

bool BotanAES256::EncryptFile(QString Source, QString Destination)
{
    try
    {
        //Setup the key derive functions
        PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
        const u32bit PBKDF2_ITERATIONS = 8192;

        //Create the KEY and IV
        KDF* kdf = get_kdf("KDF2(SHA-1)");

        //Create the master key
        SecureVector<byte> mMaster = pbkdf2.derive_key(48, mPassword.toStdString(), &mSalt[0], mSalt.size(),PBKDF2_ITERATIONS).bits_of();
        SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
        InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        string inFilename = Source.toStdString();
        string outFilename = Destination.toStdString();
        std::ifstream in(inFilename.c_str(),std::ios::binary);
        std::ofstream out(outFilename.c_str(),std::ios::binary);

        Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV,ENCRYPTION),new DataSink_Stream(out));
        pipe.start_msg();
        in >> pipe;
        pipe.end_msg();

        out.flush();
        out.close();
        in.close();

        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool BotanAES256::DecryptFile(QString Source, QString Destination)
{
    try
    {
        //Setup the key derive functions
        PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
        const u32bit PBKDF2_ITERATIONS = 8192;

        //Create the KEY and IV
        KDF* kdf = get_kdf("KDF2(SHA-1)");

        //Create the master key
        SecureVector<byte> mMaster = pbkdf2.derive_key(48, mPassword.toStdString(), &mSalt[0], mSalt.size(),PBKDF2_ITERATIONS).bits_of();
        SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
        InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        string inFilename = Source.toStdString();
        string outFilename = Destination.toStdString();
        std::ifstream in(inFilename.c_str(),std::ios::binary);
        std::ofstream out(outFilename.c_str(),std::ios::binary);

        Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV,DECRYPTION),new DataSink_Stream(out));
        pipe.start_msg();
        in >> pipe;
        pipe.end_msg();

        out.flush();
        out.close();
        in.close();

        return true;
    }
    catch(...)
    {
        return false;
    }
}



