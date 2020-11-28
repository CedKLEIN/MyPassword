#include "Log.h"

#include<QDebug>

#include <fstream>

void Log::LOG_DEBUG(const std::string& iMsg) const{
    writeLog("DEBUG",iMsg);
}

void Log::LOG_INFO(const std::string& iMsg) const{
    writeLog("INFO",iMsg);
}

void Log::LOG_WARNING(const std::string& iMsg) const{
    writeLog("WARNING",iMsg);
}

void Log::LOG_CRITICAL(const std::string& iMsg) const{
    writeLog("CRITICAL",iMsg);
}

void Log::writeLog(const std::string& iLogType,const std::string& iMsg) const{
    std::ofstream file{"./Log.txt",std::ios::app};

    if(file.is_open()){
        file << "[" << _dateTime.getDateTime() << "]";
        file << " " << iLogType << " ";
        file << iMsg << std::endl;
        file.close();
    }else{
        qDebug() << "Impossible to open the file";
    }
}
