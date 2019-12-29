//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#include <sstream>

namespace util{

    enum LogLevel{
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4,
        OFF = 5
    };

    void log(LogLevel level, const std::string &msg);
    void logSetLevel(LogLevel level);
    void logSetTime(bool enable);
    void logSetDate(bool enable);
    void logSetColor(bool enable);
    void logSetFileLevel(LogLevel level);
    void logSetFile(const std::string &file = "");

    namespace impl {
        template<typename T>
        void buildString(std::stringstream &stream, T t) {
            stream << t;
        }

        template<typename T, typename... TS>
        void buildString(std::stringstream &stream, T t, TS... ts) {
            stream << t;
            buildString(stream, ts...);
        }
    }

    template<typename... T>
    void log(LogLevel level, T... t){
        std::stringstream stream;
        impl::buildString(stream, t...);
        log(level, stream.str());
    }

    template<typename... T>
    void logDebug(T... t){
        log(LogLevel::DEBUG, t...);
    }

    template<typename... T>
    void logInfo(T... t){
        log(LogLevel::INFO, t...);
    }

    template<typename... T>
    void logWarning(T... t){
        log(LogLevel::WARNING, t...);
    }

    template<typename... T>
    void logError(T... t){
        log(LogLevel::ERROR, t...);
    }

    template<typename... T>
    void logCritical(T... t){
        log(LogLevel::CRITICAL, t...);
    }

}

#endif //UTIL_LOG_H
