#include <QtTest>

#include "../../Src/DateTime.h"

#include <regex>

class TestDateTime : public QObject
{
    Q_OBJECT

private slots:
    void get_current_date_time();
    void get_current_date();
    void get_current_time();
private:
    DateTime _dateTime;
};

void TestDateTime::get_current_date_time(){
    std::regex dateTimeFormat{"[0-9]+/[0-9]+/[0-9]+ [0-9]+:[0-9]+:[0-9]+"};
    QVERIFY(std::regex_match(_dateTime.getDateTime(),dateTimeFormat));
}

void TestDateTime::get_current_date(){
    std::regex dateFormat{"[0-9]+/[0-9]+/[0-9]+"};
    QVERIFY(std::regex_match(_dateTime.getDate(),dateFormat));
}

void TestDateTime::get_current_time(){
    std::regex dateFormat{"[0-9]+:[0-9]+:[0-9]+"};
    QVERIFY(std::regex_match(_dateTime.getTime(),dateFormat));
}

QTEST_MAIN(TestDateTime)

#include "TestDateTime.moc"
