#include "Application.h"





namespace lk {
bool Application::Init(int argc, char** argv)
{

    std::string ConfigPath;
    bool CustomConfig = GetProgramArgumentValue( argc, argv, "config", ConfigPath );
    if ( !CustomConfig )
    {
        ConfigPath = DEFAULT_CONFIG_PATH;
    }

    if (!ApplicationConfig::Get() ->LoadConfigFromFile( ConfigPath ) )
    {
        Logger::Get() -> Log( { "Application", LoggerMessageType::Error, "Application::Init() Can't load config from given path: " + ConfigPath } );
        return false;
    }
    return true;
}


bool Application::StartMainLoop() {
    return false;
}

void Application::Update() {

}


void Application::Exit() {

}

Application::~Application()
{
    Logger::Destroy();
    ApplicationConfig::Destroy();
}



bool Application::GetProgramArgumentValue(int argc, char **argv, const std::string &ArgumentName, std::string &value)
{
    if ( argc < 1 )
        return false;
    for ( int i = 0; i < argc; i ++ )
    {
        if ( argv[i] == ArgumentName || argv[i] == '-' + ArgumentName )
        {
            if ( i + 1 >= argc )
                return false;
            value = argv[i+1];
            return true;
        }
    }
    return false;
}

} // end namespace lk