#include "Application.h"





namespace lk
{

Application::~Application()
{
    Logger::Destroy();
    ApplicationConfig::Destroy();
    glfwTerminate();
}

bool Application::Initialize(int argc, char **argv)
{
    std::string ConfigPath;
    bool CustomConfig = GetProgramArgumentValue( argc, argv, "config", ConfigPath );
    if ( !CustomConfig )
    {
        ConfigPath = DEFAULT_CONFIG_PATH;
    }

    if (!ApplicationConfig::Get() ->LoadConfigFromFile( ConfigPath ) )
    {
        Logger::Get() -> Log( {"Application", LogMessageType::Error, "Application::Init() Can't load config from given path: " + ConfigPath } );
        return false;
    }

    if ( !InitializeWindow () )
    {
        Logger::Get() -> Log ( {"Application", LogMessageType::Error, "Application::Init() Can't initialize window"});
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

    bool Application::InitializeWindow() {

        if (!glfwInit())
        {
            Logger::Get() -> Log ( {"Application", LogMessageType::Error, "Application::InitializeWindow(): Can't initialize GLFW" } );
            return false;
        }

        std::string AppName;
        if ( !ApplicationConfig::Get() -> GetVariableByName ( "ApplicationName", AppName ) )
        {
            Logger::Get() -> Log ( { "Application", LogMessageType::Warning, "Application::InitializeWindow(): Config doesn't contain application name" } );
            AppName = DEFAULT_APPLICATION_NAME;
        }

        int WindowWidth;
        int WindowHeight;

        if ( !ApplicationConfig::Get() -> GetVariableByName ( "WindowWidth", WindowWidth )
            || !ApplicationConfig::Get() -> GetVariableByName ( "WindowHeight", WindowHeight )
            || WindowHeight <= 0 || WindowWidth <= 0 )
        {
            Logger::Get() -> Log ( { "Application", LogMessageType::Warning ,
                                     "Application::InitializeWindow(): Config doesn't contain WindowWidth, WindowHeight or they are invalid" } );
            WindowWidth = DEFAULT_WINDOW_WIDTH;
            WindowHeight = DEFAULT_WINDOW_HEIGHT;
        }
        m_MainWindow  = glfwCreateWindow(WindowWidth, WindowHeight, AppName.c_str(), NULL, NULL);
        if (!m_MainWindow){
            Logger::Get() -> Log ( { "Application", LogMessageType::Error, "Application::InitializeWindow(): Can't create main window" } );
            return false;
        }
        glfwMakeContextCurrent(m_MainWindow);
        return true;
    }

} // end namespace lk