#pragma once
#include "json.hpp"
#include <fstream>
#include "Logger.h" // TODO: move core includes to separate .h file


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
    ApplicationConfig() = default;

private:
    static ApplicationConfig * m_Instance;
    nlohmann::json m_ConfigJson;
};

} // end namespace lk