#include "Log.h"

#include <iostream>
#include <string>
#include <fstream>

const std::string LOG_FILENAME{"./Log.txt"};
const int LOG_LINETODELETE{5000};
Log::Log(){
    if(getNbrLines()>LOG_LINETODELETE*2){
        std::vector<std::string> logs;
        getLogsFromStartingLine(LOG_LINETODELETE,logs);
        clearLogFile();
        fillLogsFileFromVector(logs);
    }
}

unsigned int Log::getNbrLines()const{
    std::ifstream file{LOG_FILENAME,std::ios::app};

    int numberOfLines{0};
    if(file.is_open()){
        std::string line;

        while (std::getline(file, line))
            ++numberOfLines;
        file.close();
    }
    return numberOfLines;
}

void Log::getLogsFromStartingLine(int iStartLine, std::vector<std::string>& oLogs)const{
    std::ifstream file{LOG_FILENAME,std::ios::app};

    int numberOfLines{0};
    if(file.is_open()){
        std::string line;
        while (std::getline(file, line)){
            if(numberOfLines>iStartLine)
                oLogs.push_back(line);
            ++numberOfLines;
        }
        file.close();
    }
}

void Log::clearLogFile()const{
    std::ofstream file;
    file.open(LOG_FILENAME, std::ofstream::out | std::ofstream::trunc);
    file.close();
}

void Log::fillLogsFileFromVector(const std::vector<std::string>& iLogs)const{
    std::ofstream file{LOG_FILENAME,std::ios::app};

    if(file.is_open()){
        for(const auto& log: iLogs){
            file << log << std::endl;
        }
        file.close();
    }
}

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
    std::ofstream file{LOG_FILENAME,std::ios::app};

    if(file.is_open()){
        file << "[" << _dateTime.getDateTime() << "]";
        file << " " << iLogType << " ";
        file << iMsg << std::endl;
        file.close();
    }
}
