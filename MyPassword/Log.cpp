#include "Log.h"

#include<QDebug>

void Log::LOG_DEBUG(const std::string& iMsg){
    writeLog("DEBUG",iMsg);
}

void Log::LOG_INFO(const std::string& iMsg){
    writeLog("INFO",iMsg);
}

void Log::LOG_WARNING(const std::string& iMsg){
    writeLog("WARNING",iMsg);
}

void Log::LOG_CRITICAL(const std::string& iMsg){
    writeLog("CRITICAL",iMsg);
}

void Log::writeLog(const std::string& iLogType,const std::string& iMsg){
    _file.open("./Log.txt",std::ios::app);

    if(_file.is_open()){
        _file << "[" << _dateTime.getDateTime() << "]";
        _file << " " << iLogType << " ";
        _file << iMsg << std::endl;
    }else{
        qDebug() << "Impossible to open the file";
    }

    _file.close();
}
