#include "Encryption.h"

#include <QByteArray>
#include <QCryptographicHash>

QString Encryption::encrypt(const QString& iPassword) const
{
    QByteArray passwordInByte(iPassword.toLocal8Bit());
    QByteArray passwordInMD5{QCryptographicHash::hash(passwordInByte, QCryptographicHash::Md5)};
    return passwordInMD5.toHex();
}
