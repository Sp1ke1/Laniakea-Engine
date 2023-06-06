//
// Created by NB01 on 6/4/2023.
//

#include "Logger.h"

namespace lk {
    Logger * Logger::m_Instance = nullptr;


    Logger *Logger::Get() {
        if (m_Instance) {
            return m_Instance;
        }
        m_Instance = new Logger();
        return m_Instance;
    }

    void Logger::Destroy() {
        if ( m_Instance )
        {
            delete m_Instance;
            m_Instance = nullptr;
            return;
        }

    }

    void Logger::Log(const std::string &Message) {
        Log(LoggerMessage{"Tag_None", LogMessageType::Log, Message});
    }

    void Logger::Log(const LoggerMessage &Message) {
        if (m_PrintToCerr && Message.MessageType >= m_Verbosity)
            PrintToCerr(Message);
        m_Log.push_back(Message);
    }

    void Logger::PrintToCerr(const LoggerMessage &Message) const {

        std::cerr << "[" << Message.Tag << "]" << " : " << LoggerMessageTypeToString(Message.MessageType) << " : "
                  << Message.Message << std::endl;
    }

    std::string LoggerMessageTypeToString(LogMessageType type) {
        switch (type) {
            case LogMessageType::Log:
                return "Log";
            case LogMessageType::Warning:
                return "Warning";
            case LogMessageType::Error:
                return "Error";
            case LogMessageType::Undefined:
                return "Undefined";
            default:
                break;
        }
        return "UndefinedMessageType";
    }

    std::vector<LoggerMessage> Logger::GetLogByTag(const std::string &Tag) const {
        std::vector<LoggerMessage> Out; // TODO: there must be built-in std::views::filter
        for (auto &Message: m_Log) {
            if (Message.Tag == Tag)
                Out.push_back(Message);
        }
        return Out;
    }

    std::vector<LoggerMessage> Logger::GetLogByMessageType(LogMessageType MessageType) const {
        std::vector<LoggerMessage> Out; // TODO: there must be built-in std::views::filter
        for (auto &Message: m_Log) {
            if (Message.MessageType == MessageType)
                Out.push_back(Message);
        }
        return Out;
    }

    std::vector<LoggerMessage> Logger::GetLog() const {
        return m_Log;
    }


    void Logger::SetPrintToCerr(bool PrintToCerr) {

        m_PrintToCerr = PrintToCerr;
    }

    Logger::Logger() {

    }

    void Logger::SetVerbosity(LogMessageType verbosity) {
        m_Verbosity = verbosity;
    }



} // end namespace laniakea
