#include "Application.h"
#include "Input.h"

namespace lk
{

Application * Application::s_Instance = nullptr;

Application::Application() {
    LK_ASSERT (!s_Instance);
    s_Instance = this;
}

Application *Application::Get() {
    LK_ASSERT ( s_Instance );
    return s_Instance;
}

Application::~Application()
{
    Logger::Destroy();
    ApplicationConfig::Destroy();
    glfwTerminate();

    if ( s_Instance ) {
        delete s_Instance;
        s_Instance = nullptr;
    }
}

bool Application::Initialize(int argc, char **argv)
{
    if ( m_IsInitialized )
    {
        LK_LOG ( "Application" , LogMessageType::Warning, "Application()::Init() Application was already initialized" );
        return false;
    }
    std::string ConfigPath;
    bool CustomConfig = GetProgramArgumentValue( argc, argv, "config", ConfigPath );
    if ( !CustomConfig )
    {
        ConfigPath = DEFAULT_CONFIG_PATH;
    }

    if (!ApplicationConfig::Get() ->LoadConfigFromFile( ConfigPath ) )
    {
        LK_LOG ( "Application" , LogMessageType::Error, "Application::Init() Can't load config from given path: " + ConfigPath );
        return false;
    }

    if ( ! InitializeWindow () ) {
        LK_LOG ( "Application" , LogMessageType::Error, "Application::Init() Can't initialize window" );
        return false;
    }

    if ( !Input::Initialize() )
    {
        LK_LOG ( "Application", LogMessageType::Error, "Application::Init() Can't initialize input" );
        return false;
    }

    m_IsInitialized = true;
    return true;
}


bool Application::StartMainLoop() {

    if ( m_Running )
    {
        LK_LOG("Application", LogMessageType::Warning, "Application::StartMainLoop() called when application is already running.");
        return false;
    }
    m_Running = true;
    while ( m_Running )
    {
        Update();
    }
    return true;

}


void Application::Update()
{
    LK_ASSERT ( m_Window );
    m_Window -> Update();
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

        // Get window name and windows sizes variables from application config
        std::string AppName;

        auto AppNameCheckFn = []( const std::string & AppName ) { return !AppName.empty(); };
        if ( !ApplicationConfig :: Get() ->GetVariableByNameChecked( "ApplicationName", AppName,AppNameCheckFn ) )
        {
            AppName = DEFAULT_APPLICATION_NAME;
        }

        int WindowWidth;
        int WindowHeight;

        auto WindowSizeCheckFn = [] ( int Value ) { return Value > 0; };
        if ( !ApplicationConfig::Get() ->GetVariableByNameChecked( "WindowWidth", WindowWidth, WindowSizeCheckFn )
            || !ApplicationConfig::Get() ->GetVariableByNameChecked( "WindowHeight", WindowHeight, WindowSizeCheckFn ) )
        {
            WindowWidth = DEFAULT_WINDOW_WIDTH;
            WindowHeight = DEFAULT_WINDOW_HEIGHT;
        }

        WindowProperties Properties ( AppName, WindowWidth, WindowHeight, false );
        m_Window = std::make_unique<Window> ( Properties );
        if ( !m_Window )
        {
            LK_LOG ( "Application", LogMessageType::Error, "Application::InitializeWindow() Can't create main window"  );
            return false;
        }

        // Note: We can use m_Window->SetEventCallback( [this](auto && PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); } );
        // Or std::bind ( &Application::OnEvent, this, std::placeholders::_X )
/*
        m_Window->SetEventCallback( [this] ( Event & e ) { OnEvent ( e ); } );
*/

        m_Window -> GetWindowEventDispatcher().Bind ( [this] ( Event & e ) -> bool  { return OnEvent ( e ); } );

        return true;
    }

    bool Application::OnEvent(Event &E)
    {
//        return GetApplicationEventDispatcher().Dispatch( E );

        switch ( E.GetEventType() )
        {
            case EventType::WindowClose:
            {
                LK_LOG ( "Application", LogMessageType::Log, "Received window close event" );
                m_Running = false;
                break;
            }
            case EventType::WindowResize:
            {
                LK_LOG ( "Application", LogMessageType::Log, "Received window resize event: " + E.ToString() );
                break;
            }
            case EventType::WindowMoved:
            {
                LK_LOG ( "Application", LogMessageType::Log, "Received window moved event: " + E.ToString() );
                break;
            }
            case EventType::WindowFocus:
            {
                LK_LOG ( "Application", LogMessageType::Log, "Received window focus event: " + E.ToString() );
                break;
            }
            case EventType::WindowLostFocus:
            {
                LK_LOG ( "Application", LogMessageType::Log, "Received window last focus event: " + E.ToString() );
                break;
            }

            case EventType::KeyPressed:
            {
                LK_LOG ( "Application", LogMessageType::Log, "Received: " + E.ToString() );
            }
            default:
            {
                // LK_LOG ( "Application", LogMessageType::Warning, "Received event with no implementation: " + E.ToString() );
                break;
            }
        }
        return true;
    }

    const Window &Application::GetWindow() const
    {
        return * m_Window;
    }

    EventDispatcher & Application::GetApplicationEventDispatcher() {
        return m_ApplicationEventDispatcher;
    }
} // end namespace lk