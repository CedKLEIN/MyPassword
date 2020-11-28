#include <QtTest>

#include "../../Src/Encryption.h"

class TestEncryption : public QObject
{
    Q_OBJECT

private slots:
    void encrypt_password_in_Md5();
private:
    Encryption _encryption;
};

void TestEncryption::encrypt_password_in_Md5(){
    QString pwdToEncrypt{"TEST_IN_MD5"};
    QCOMPARE(_encryption.encrypt(pwdToEncrypt),"e173e6aa7891a06fa4bf7946f82f456f");
}

QTEST_MAIN(TestEncryption)

#include "TestEncryption.moc"
