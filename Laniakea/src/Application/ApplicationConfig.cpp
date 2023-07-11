#include "ApplicationConfig.h"

namespace lk {

    ApplicationConfig * ApplicationConfig::m_Instance = nullptr;

bool ApplicationConfig::LoadConfigFromFile(const std::string &filename) {
    std::ifstream f(filename);
    if (!f) {
        std::string ErrMessage = std::string ( "ApplicationConfig::LoadConfigFromFile() : Can't open config file with given name: " ) + filename;
        Logger::Get() -> Log( {"ApplicationConfig", LogMessageType::Error, ErrMessage } );
        return false;
    }
    m_ConfigJson = nlohmann::json::parse ( f, nullptr, false );
    if ( m_ConfigJson.is_discarded() ) {
        Logger::Get()->Log({"ApplicationConfig", LogMessageType::Error,
                            "ApplicationConfig::LoadConfigFromFile() Error parsing config as json"});
        return false;
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
