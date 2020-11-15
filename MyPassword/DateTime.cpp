#include "DateTime.h"

#include <ctime>

std::string DateTime::getDateTime()const{
    return getDate()+" "+getTime();
}

std::string DateTime::getDate()const{
    time_t now{time(0)};
    tm *ltm{localtime(&now)};

    int year{1900 + ltm->tm_year};
    int month{1 + ltm->tm_mon};
    int day{ltm->tm_mday};

    return std::to_string(day)+"/"+std::to_string(month)+"/"+std::to_string(year);
}

std::string DateTime::getTime()const{
    time_t now{time(0)};
    tm *ltm{localtime(&now)};

    int hour{ltm->tm_hour};
    int minutes{ltm->tm_min};
    int seconds{ltm->tm_sec};

    return std::to_string(hour)+":"+std::to_string(minutes)+":"+std::to_string(seconds);
}
