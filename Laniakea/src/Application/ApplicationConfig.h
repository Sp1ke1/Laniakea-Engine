#pragma once

#include "Core.h"
#include "Logger.h"
#include "json/include/json.hpp"



#pragma region CongigDefaults
#define DEFAULT_CONFIG_PATH "config/ApplicationConfig.json"
#define DEFAULT_APPLICATION_NAME "Laniakea"
#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080
#pragma endregion



namespace lk {
class ApplicationConfig {


public:

    ApplicationConfig ( const ApplicationConfig & ) = delete;
    ApplicationConfig & operator = ( const ApplicationConfig & ) = delete;

    static ApplicationConfig * Get();

    static void Destroy();

    template <typename ValueType>
    bool GetVariableByName ( const std::string & VarName, ValueType & value ) const
    {
        if ( !m_ConfigJson.contains( VarName ) )
            return false;
        value = m_ConfigJson[VarName].get<ValueType> ();
        return true;
    }

    template <typename ValueType, typename Predicate>
    bool GetVariableByNameChecked ( const std::string & VarName, ValueType & value, Predicate p  ) const
    {
        if ( !m_ConfigJson.contains ( VarName ) )
        {
            LK_LOG("Config", LogMessageType::Error, "Config doesn't contain variable with name: " + VarName );
            return false;
        }
        value = m_ConfigJson[VarName].get<ValueType> ();
        if ( !p ( value ) )
        {
            LK_LOG("Config", LogMessageType::Error, "Config variable: " + VarName + " doesn't matches predicate filter " );
            return false;
        }
        return true;
    }

    bool LoadConfigFromFile ( const std::string & filename );



protected:
    ApplicationConfig() = default;

private:
    static ApplicationConfig * m_Instance;
    nlohmann::json m_ConfigJson;
};

} // end namespace lk