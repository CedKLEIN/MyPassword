#include <QtTest>

#include "../Src/PasswordSecurity.h"
#include "../Src/Settings.h"
#include "../Src/Utility.h"

class TestPasswordSecurity : public QObject
{
    Q_OBJECT

private slots:
    void get_icons_name_from_theme1_in_settings();
    void get_icons_name_from_theme1_in_settings_data();
    void get_icons_name_from_theme2_in_settings();
    void get_icons_name_from_theme2_in_settings_data();
    void get_icons_name_from_theme3_in_settings();
    void get_icons_name_from_theme3_in_settings_data();
    void security_level_very_low_when_less_than_nine_digits();
    void security_level_very_low_when_less_than_nine_digits_data();
    void security_level_very_high_when_more_than_nineteen_digits();
    void security_level_very_high_when_more_than_nineteen_digits_data();
    void security_level_when_only_numbers();
    void security_level_when_only_numbers_data();
    void security_level_when_only_lower();
    void security_level_when_only_lower_data();
    void security_level_when_only_upper();
    void security_level_when_only_upper_data();
    void security_level_when_only_others();
    void security_level_when_only_others_data();
    void security_level_when_only_number_and_lower();
    void security_level_when_only_number_and_lower_data();
    void security_level_when_only_number_and_upper();
    void security_level_when_only_number_and_upper_data();
    void security_level_when_only_number_and_others();
    void security_level_when_only_number_and_others_data();
    void security_level_when_only_lower_and_upper();
    void security_level_when_only_lower_and_upper_data();
    void security_level_when_only_lower_and_others();
    void security_level_when_only_lower_and_others_data();
    void security_level_when_only_upper_and_others();
    void security_level_when_only_upper_and_others_data();
    void security_level_when_only_number_lower_and_upper();
    void security_level_when_only_number_lower_and_upper_data();
    void security_level_when_only_number_lower_and_others();
    void security_level_when_only_number_lower_and_others_data();
    void security_level_when_only_number_upper_and_others();
    void security_level_when_only_number_upper_and_others_data();
    void security_level_when_only_number_lower_upper_and_others();
    void security_level_when_only_number_lower_upper_and_others_data();

private:
    void COMPARE_DATA_ICON_NAME();
    void COMPARE_DATA_SEVERITY_LEVEL();
    Testable::Settings _settings;
    PasswordSecurity _passwordSecurity{_settings};

};

void TestPasswordSecurity::COMPARE_DATA_ICON_NAME(){
    QFETCH(int, securityLevel);
    QFETCH(QString, iconName);

    QCOMPARE(_passwordSecurity.getIconSeverityLvl(securityLevel), iconName);
}

void TestPasswordSecurity::get_icons_name_from_theme1_in_settings_data(){
    QTest::addColumn<int>("securityLevel");
    QTest::addColumn<QString>("iconName");

    QTest::newRow("Very Low") << 1 << ":/very_low";
    QTest::newRow("Low") << 2 << ":/low";
    QTest::newRow("Medium") << 3 << ":/medium";
    QTest::newRow("High") << 4 << ":/high";
    QTest::newRow("Very High") << 5 << ":/very_high";
}

void TestPasswordSecurity::get_icons_name_from_theme1_in_settings(){
    _settings.setSecurityIconThemes(SecurityIconThemes1);
    COMPARE_DATA_ICON_NAME();
}

void TestPasswordSecurity::get_icons_name_from_theme2_in_settings_data(){
    QTest::addColumn<int>("securityLevel");
    QTest::addColumn<QString>("iconName");

    QTest::newRow("Very Low") << 1 << ":/very_low_theme2";
    QTest::newRow("Low") << 2 << ":/low_theme2";
    QTest::newRow("Medium") << 3 << ":/medium_theme2";
    QTest::newRow("High") << 4 << ":/high_theme2";
    QTest::newRow("Very High") << 5 << ":/very_high_theme2";
}

void TestPasswordSecurity::get_icons_name_from_theme2_in_settings(){
    _settings.setSecurityIconThemes(SecurityIconThemes2);
    COMPARE_DATA_ICON_NAME();
}

void TestPasswordSecurity::get_icons_name_from_theme3_in_settings_data(){
    QTest::addColumn<int>("securityLevel");
    QTest::addColumn<QString>("iconName");

    QTest::newRow("Very Low") << 1 << ":/very_low_theme3";
    QTest::newRow("Low") << 2 << ":/low_theme3";
    QTest::newRow("Medium") << 3 << ":/medium_theme3";
    QTest::newRow("High") << 4 << ":/high_theme3";
    QTest::newRow("Very High") << 5 << ":/very_high_theme3";
}

void TestPasswordSecurity::get_icons_name_from_theme3_in_settings(){
    _settings.setSecurityIconThemes(SecurityIconThemes3);
    COMPARE_DATA_ICON_NAME();
}

void TestPasswordSecurity::COMPARE_DATA_SEVERITY_LEVEL(){
    QFETCH(QString, password);
    QFETCH(int, securityLevel);

    QCOMPARE(_passwordSecurity.getSecurityLevel(password), securityLevel);
}

void TestPasswordSecurity::security_level_very_low_when_less_than_nine_digits_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("1 digit") << "1" << 1;
    QTest::newRow("2 digits") << "aa" << 1;
    QTest::newRow("3 digits") << "???" << 1;
    QTest::newRow("4 digits") << "AAAA" << 1;
    QTest::newRow("5 digits") << "11111" << 1;
    QTest::newRow("6 digits") << "aaaaaa" << 1;
    QTest::newRow("7 digits") << "???????" << 1;
    QTest::newRow("8 digits") << "AAAAAAAA" << 1;
}

void TestPasswordSecurity::security_level_very_low_when_less_than_nine_digits(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_very_high_when_more_than_nineteen_digits_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("20 digits") << "11111111111111111111" << 5;
    QTest::newRow("21 digits") << "aaaaaaaaaaaaaaaaaaaaa" << 5;
    QTest::newRow("30 digits") << "??????????????????????????????" << 5;
    QTest::newRow("50 digits") << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << 5;
}

void TestPasswordSecurity::security_level_very_high_when_more_than_nineteen_digits(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_numbers_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "111111111" << 1;
    QTest::newRow("10") << "1111111111" << 1;
    QTest::newRow("11") << "11111111111" << 1;
    QTest::newRow("12") << "111111111111" << 1;
    QTest::newRow("13") << "1111111111111" << 1;
    QTest::newRow("14") << "11111111111111" << 1;
    QTest::newRow("15") << "111111111111111" << 1;
    QTest::newRow("16") << "1111111111111111" << 1;
    QTest::newRow("17") << "11111111111111111" << 1;
    QTest::newRow("18") << "111111111111111111" << 2;
    QTest::newRow("19") << "1111111111111111111" << 3;
}

void TestPasswordSecurity::security_level_when_only_numbers(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_lower_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "aaaaaaaaa" << 1;
    QTest::newRow("10") << "aaaaaaaaaa" << 1;
    QTest::newRow("11") << "aaaaaaaaaaa" << 1;
    QTest::newRow("12") << "aaaaaaaaaaaa" << 1;
    QTest::newRow("13") << "aaaaaaaaaaaaa" << 2;
    QTest::newRow("14") << "aaaaaaaaaaaaaa" << 5;
    QTest::newRow("15") << "aaaaaaaaaaaaaaa" << 5;
    QTest::newRow("16") << "aaaaaaaaaaaaaaaa" << 5;
    QTest::newRow("17") << "aaaaaaaaaaaaaaaaa" << 5;
    QTest::newRow("18") << "aaaaaaaaaaaaaaaaaa" << 5;
    QTest::newRow("19") << "aaaaaaaaaaaaaaaaaaa" << 5;
}

void TestPasswordSecurity::security_level_when_only_lower(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_upper_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "AAAAAAAAA" << 1;
    QTest::newRow("10") << "AAAAAAAAAA" << 1;
    QTest::newRow("11") << "AAAAAAAAAAA" << 1;
    QTest::newRow("12") << "AAAAAAAAAAAA" << 1;
    QTest::newRow("13") << "AAAAAAAAAAAAA" << 2;
    QTest::newRow("14") << "AAAAAAAAAAAAAA" << 5;
    QTest::newRow("15") << "AAAAAAAAAAAAAAA" << 5;
    QTest::newRow("16") << "AAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("17") << "AAAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("18") << "AAAAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("19") << "AAAAAAAAAAAAAAAAAAA" << 5;
}

void TestPasswordSecurity::security_level_when_only_upper(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "?????????" << 1;
    QTest::newRow("10") << "??????????" << 1;
    QTest::newRow("11") << "???????????" << 1;
    QTest::newRow("12") << "????????????" << 1;
    QTest::newRow("13") << "?????????????" << 1;
    QTest::newRow("14") << "??????????????" << 2;
    QTest::newRow("15") << "???????????????" << 4;
    QTest::newRow("16") << "????????????????" << 5;
    QTest::newRow("17") << "?????????????????" << 5;
    QTest::newRow("18") << "??????????????????" << 5;
    QTest::newRow("19") << "???????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_and_lower_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1aaaaaaaa" << 1;
    QTest::newRow("10") << "1aaaaaaaaa" << 1;
    QTest::newRow("11") << "1aaaaaaaaaa" << 1;
    QTest::newRow("12") << "1aaaaaaaaaaa" << 2;
    QTest::newRow("13") << "1aaaaaaaaaaaa" << 5;
    QTest::newRow("14") << "1aaaaaaaaaaaaa" << 5;
    QTest::newRow("15") << "1aaaaaaaaaaaaaa" << 5;
    QTest::newRow("16") << "1aaaaaaaaaaaaaaa" << 5;
    QTest::newRow("17") << "1aaaaaaaaaaaaaaaa" << 5;
    QTest::newRow("18") << "1aaaaaaaaaaaaaaaaa" << 5;
    QTest::newRow("19") << "1aaaaaaaaaaaaaaaaaa" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_and_lower(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_and_upper_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1AAAAAAAA" << 1;
    QTest::newRow("10") << "1AAAAAAAAA" << 1;
    QTest::newRow("11") << "1AAAAAAAAAA" << 1;
    QTest::newRow("12") << "1AAAAAAAAAAA" << 2;
    QTest::newRow("13") << "1AAAAAAAAAAAA" << 5;
    QTest::newRow("14") << "1AAAAAAAAAAAAA" << 5;
    QTest::newRow("15") << "1AAAAAAAAAAAAAA" << 5;
    QTest::newRow("16") << "1AAAAAAAAAAAAAAA" << 5;
    QTest::newRow("17") << "1AAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("18") << "1AAAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("19") << "1AAAAAAAAAAAAAAAAAA" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_and_upper(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_and_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1????????" << 1;
    QTest::newRow("10") << "1?????????" << 1;
    QTest::newRow("11") << "1??????????" << 1;
    QTest::newRow("12") << "1???????????" << 2;
    QTest::newRow("13") << "1????????????" << 3;
    QTest::newRow("14") << "1?????????????" << 5;
    QTest::newRow("15") << "1??????????????" << 5;
    QTest::newRow("16") << "1???????????????" << 5;
    QTest::newRow("17") << "1????????????????" << 5;
    QTest::newRow("18") << "1?????????????????" << 5;
    QTest::newRow("19") << "1??????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_and_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_lower_and_upper_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "aAAAAAAAA" << 1;
    QTest::newRow("10") << "aAAAAAAAAA" << 1;
    QTest::newRow("11") << "aAAAAAAAAAA" << 2;
    QTest::newRow("12") << "aAAAAAAAAAAA" << 5;
    QTest::newRow("13") << "aAAAAAAAAAAAA" << 5;
    QTest::newRow("14") << "aAAAAAAAAAAAAA" << 5;
    QTest::newRow("15") << "aAAAAAAAAAAAAAA" << 5;
    QTest::newRow("16") << "aAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("17") << "aAAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("18") << "aAAAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("19") << "aAAAAAAAAAAAAAAAAAA" << 5;
}

void TestPasswordSecurity::security_level_when_only_lower_and_upper(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_lower_and_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "a????????" << 1;
    QTest::newRow("10") << "A?????????" << 1;
    QTest::newRow("11") << "A??????????" << 2;
    QTest::newRow("12") << "A???????????" << 5;
    QTest::newRow("13") << "A????????????" << 5;
    QTest::newRow("14") << "A?????????????" << 5;
    QTest::newRow("15") << "A??????????????" << 5;
    QTest::newRow("16") << "A???????????????" << 5;
    QTest::newRow("17") << "A????????????????" << 5;
    QTest::newRow("18") << "A?????????????????" << 5;
    QTest::newRow("19") << "A??????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_lower_and_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_upper_and_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "A????????" << 1;
    QTest::newRow("10") << "a?????????" << 1;
    QTest::newRow("11") << "a??????????" << 2;
    QTest::newRow("12") << "a???????????" << 5;
    QTest::newRow("13") << "a????????????" << 5;
    QTest::newRow("14") << "a?????????????" << 5;
    QTest::newRow("15") << "a??????????????" << 5;
    QTest::newRow("16") << "a???????????????" << 5;
    QTest::newRow("17") << "a????????????????" << 5;
    QTest::newRow("18") << "a?????????????????" << 5;
    QTest::newRow("19") << "a??????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_upper_and_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_lower_and_upper_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1aAAAAAAA" << 1;
    QTest::newRow("10") << "1aAAAAAAAA" << 2;
    QTest::newRow("11") << "1aAAAAAAAAA" << 4;
    QTest::newRow("12") << "1aAAAAAAAAAA" << 5;
    QTest::newRow("13") << "1aAAAAAAAAAAA" << 5;
    QTest::newRow("14") << "1aAAAAAAAAAAAA" << 5;
    QTest::newRow("15") << "1aAAAAAAAAAAAAA" << 5;
    QTest::newRow("16") << "1aAAAAAAAAAAAAAA" << 5;
    QTest::newRow("17") << "1aAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("18") << "1aAAAAAAAAAAAAAAAA" << 5;
    QTest::newRow("19") << "1aAAAAAAAAAAAAAAAAA" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_lower_and_upper(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_lower_and_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1a???????" << 1;
    QTest::newRow("10") << "1a????????" << 2;
    QTest::newRow("11") << "1a?????????" << 4;
    QTest::newRow("12") << "1a??????????" << 5;
    QTest::newRow("13") << "1a???????????" << 5;
    QTest::newRow("14") << "1a????????????" << 5;
    QTest::newRow("15") << "1a?????????????" << 5;
    QTest::newRow("16") << "1a??????????????" << 5;
    QTest::newRow("17") << "1a???????????????" << 5;
    QTest::newRow("18") << "1a????????????????" << 5;
    QTest::newRow("19") << "1a?????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_lower_and_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_upper_and_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1A???????" << 1;
    QTest::newRow("10") << "1A????????" << 2;
    QTest::newRow("11") << "1A?????????" << 4;
    QTest::newRow("12") << "1A??????????" << 5;
    QTest::newRow("13") << "1A???????????" << 5;
    QTest::newRow("14") << "1A????????????" << 5;
    QTest::newRow("15") << "1A?????????????" << 5;
    QTest::newRow("16") << "1A??????????????" << 5;
    QTest::newRow("17") << "1A???????????????" << 5;
    QTest::newRow("18") << "1A????????????????" << 5;
    QTest::newRow("19") << "1A?????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_upper_and_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

void TestPasswordSecurity::security_level_when_only_number_lower_upper_and_others_data(){
    QTest::addColumn<QString>("password");
    QTest::addColumn<int>("securityLevel");

    QTest::newRow("9") << "1aA??????" << 1;
    QTest::newRow("10") << "1aA???????" << 3;
    QTest::newRow("11") << "1aA????????" << 5;
    QTest::newRow("12") << "1aA?????????" << 5;
    QTest::newRow("13") << "1aA??????????" << 5;
    QTest::newRow("14") << "1aA???????????" << 5;
    QTest::newRow("15") << "1aA????????????" << 5;
    QTest::newRow("16") << "1aA?????????????" << 5;
    QTest::newRow("17") << "1aA??????????????" << 5;
    QTest::newRow("18") << "1aA???????????????" << 5;
    QTest::newRow("19") << "1aA????????????????" << 5;
}

void TestPasswordSecurity::security_level_when_only_number_lower_upper_and_others(){
    COMPARE_DATA_SEVERITY_LEVEL();
}

QTEST_MAIN(TestPasswordSecurity)

#include "tst_testpasswordsecurity.moc"
