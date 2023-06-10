#pragma once
#include "Core.h"
#include <vector>
#include <string>
#include <iostream>

namespace lk {
enum class LogMessageType {
    Undefined,
    Log,
    Warning,
    Error,
};

std::string LoggerMessageTypeToString(LogMessageType type);

struct LoggerMessage {
    std::string Tag;
    LogMessageType MessageType;
    std::string Message;

};

class LANIAKEA_API Logger {


public:
    // Singleton
    Logger(const Logger &) = delete;

    void operator=(const Logger &) = delete;

    static Logger *Get();

    static void Destroy();


    void Log(const std::string &Message);

    void Log(const LoggerMessage &Message);

    std::vector<LoggerMessage> GetLog() const;

    std::vector<LoggerMessage> GetLogByTag(const std::string &Tag) const;

    std::vector<LoggerMessage> GetLogByMessageType(LogMessageType MessageType) const;

    void SetPrintToCerr(bool PrintToCerr);

    void SetVerbosity(LogMessageType verbosity);

protected:
    Logger();

    void PrintToCerr(const LoggerMessage &Message) const;

protected:
    static Logger *m_Instance;
    std::vector<LoggerMessage> m_Log;
    bool m_PrintToCerr = true;
    LogMessageType m_Verbosity = LogMessageType::Log;

};
} // end namespace laniakea