//
// Created by NB01 on 6/5/2023.
//

#include "ApplicationConfig.h"
namespace lk {

    ApplicationConfig * ApplicationConfig::m_Instance = nullptr;

bool ApplicationConfig::LoadConfigFromFile(const std::string &filename) {
    std::ifstream f(filename);
    if (!f) {
        std::string ErrMessage = std::string ( "ApplicationConfig::LoadConfigFromFile() : Can't open config file with given name: " ) + filename;
        Logger::Get() -> Log( { "ApplicationConfig", LoggerMessageType::Error, ErrMessage } );
        return false; // TOOD: fallback to default config
    }
    m_ConfigJson = nlohmann::json::parse ( f, nullptr, false );
    if ( m_ConfigJson.is_discarded() ) {
        Logger::Get()->Log({"ApplicationConfig", LoggerMessageType::Error,
                            "ApplicationConfig::LoadConfigFromFile() Error parsing config as json"});
        return false; // TODO: fallback to default config
    }
    return true;
}

    ApplicationConfig *ApplicationConfig::Get() {
        if ( m_Instance )
            return m_Instance;
        m_Instance = new ApplicationConfig();
        return m_Instance;
    }

    void ApplicationConfig::Destroy()
    {
        if ( m_Instance ) {
            delete m_Instance;
            m_Instance = nullptr;
            return;
        }
    }


} // end namespace lk
