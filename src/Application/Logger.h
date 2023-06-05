#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace lk {
enum class LoggerMessageType {
    Undefined,
    Log,
    Warning,
    Error,
};

std::string LoggerMessageTypeToString(LoggerMessageType type);

struct LoggerMessage {
    std::string Tag;
    LoggerMessageType MessageType;
    std::string Message;

};

class Logger {


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

    std::vector<LoggerMessage> GetLogByMessageType(LoggerMessageType MessageType) const;

    void SetPrintToCerr(bool PrintToCerr);

    void SetVerbosity(LoggerMessageType verbosity);

protected:
    Logger();

    void PrintToCerr(const LoggerMessage &Message) const;

protected:
    static Logger *m_Instance;
    std::vector<LoggerMessage> m_Log;
    bool m_PrintToCerr = true;
    LoggerMessageType m_Verbosity = LoggerMessageType::Log;

};
} // end namespace laniakea