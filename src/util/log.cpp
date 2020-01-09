//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include <fstream>
#include "log.h"

namespace util{

    LogLevel currentLogLevel = LogLevel::INFO;
    LogLevel currentFileLogLevel = LogLevel::INFO;
    bool logTimeEnabled = true;
    bool logDateEnabled = true;
    bool logColorEnabled = true;
    std::ofstream logFileStream;

    const char* logGetLevelName(LogLevel level){
        switch (level){
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            default:
                return "NONE";
        }
    }

    const char* logGetLevelColor(LogLevel level){
        switch (level){
            case LogLevel::DEBUG:
                return "0";
            case LogLevel::INFO:
                return "1;37";
            case LogLevel::WARNING:
                return "1;33";
            case LogLevel::ERROR:
                return "1;31";
            case LogLevel::CRITICAL:
                return "1;35";
            default:
                return "0";
        }
    }

    std::string logTime(){
        std::stringstream stream;

        time_t rawtime;
        time(&rawtime);
        struct tm *timeinfo;
        timeinfo = localtime(&rawtime);

        if (timeinfo->tm_hour < 10) {
            stream << "0";
        }
        stream << timeinfo->tm_hour << ":";

        if (timeinfo->tm_min < 10) {
            stream << "0";
        }
        stream << timeinfo->tm_min << ":";

        if (timeinfo->tm_sec < 10) {
            stream << "0";
        }
        stream << timeinfo->tm_sec;

        return stream.str();
    }

    std::string logDate(){
        std::stringstream stream;

        time_t rawtime;
        time(&rawtime);
        struct tm *timeinfo;
        timeinfo = localtime(&rawtime);

        if (timeinfo->tm_mday < 10) {
            stream << "0";
        }
        stream << timeinfo->tm_mday << ".";

        if (timeinfo->tm_mon + 1 < 10) {
            stream << "0";
        }
        stream << timeinfo->tm_mon + 1 << ".";

        int year = timeinfo->tm_year + 1900;
        stream << year;

        return stream.str();
    }

    void log(LogLevel  level, const std::string &msg) {
        bool logConsole = level >= currentLogLevel;
        bool logFile = false;
        if(logFileStream.is_open()){
            logFile = level >= currentFileLogLevel;
        }

        if(logConsole || logFile){
            std::stringstream stream;
            std::stringstream colorStream;

            const std::string &levelName = logGetLevelName(level);
            int maxLevelNameLength = 8;
            int newLineIntend = maxLevelNameLength + 3;

            if(logDateEnabled){
                std::string date = logDate();
                colorStream << "[" << date << "] ";
                stream << "[" << date << "] ";
                newLineIntend += 13;
            }

            if(logTimeEnabled){
                std::string time = logTime();
                colorStream << "[" << time << "] ";
                stream << "[" << time << "] ";
                newLineIntend += 11;
            }

            colorStream << "[\033[" << logGetLevelColor(level) << "m" << levelName << "\033[0m] ";
            stream << "[" << levelName << "] ";

            for(int i = 0; i < maxLevelNameLength - (int)levelName.size();i++){
                colorStream << " ";
                stream << " ";
            }

            for(char c : msg){
                if(c == '\n'){
                    colorStream << "\n";
                    stream << "\n";
                    for(int i = 0; i < newLineIntend;i++){
                        colorStream << " ";
                        stream << " ";
                    }
                }else{
                    colorStream << c;
                    stream << c;
                }
            }
            colorStream << "\n";
            stream << "\n";

            if(logConsole){
                if(logColorEnabled){
                    printf("%s", colorStream.str().c_str());
                }else{
                    printf("%s", stream.str().c_str());
                }
            }
            if(logFile) {
                if (logFileStream.is_open()) {
                    logFileStream << stream.str();
                    logFileStream.flush();
                }
            }
        }
    }

    void logSetLevel(LogLevel level) {
        currentLogLevel = level;
    }

    void logSetTime(bool enable) {
        logTimeEnabled = enable;
    }

    void logSetDate(bool enable) {
        logDateEnabled = enable;
    }

    void logSetColor(bool enable) {
        logColorEnabled = enable;
    }

    void logSetFileLevel(LogLevel level) {
        currentFileLogLevel = level;
    }

    void logSetFile(const std::string &file) {
        if(file.empty()){
            logFileStream.close();
            return;
        }
        if(logFileStream.is_open()){
            logFileStream.close();
        }
        logFileStream.open(file, std::ofstream::app);
    }

}
