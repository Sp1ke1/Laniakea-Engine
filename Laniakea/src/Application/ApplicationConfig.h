#pragma once
#include "json/include/json.hpp"
#include "Core.h"
#include <fstream>


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

    bool LoadConfigFromFile ( const std::string & filename );



protected:
    auto static GetDefaultConfig ();
    ApplicationConfig() = default;

private:
    static ApplicationConfig * m_Instance;
    nlohmann::json m_ConfigJson;
};

} // end namespace lk