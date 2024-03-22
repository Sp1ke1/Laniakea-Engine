#pragma once

#include "Core.h"
#include "ApplicationEvent.h"
#include "EventDispatcher.h"
#include "Window.h"
#include "ApplicationConfig.h"
#include <memory>



namespace lk {
class LANIAKEA_CORE_API Application {
public:

    Application();
    virtual ~Application();

    /**
     * @brief Initializes the application.
     *
     * @param argc The number of command line arguments.
     * @param argv The command line arguments.
     * @return True if initialization was successful, false otherwise.
     */
    bool Initialize(int argc, char **argv);

    /**
     * @brief Starts the main loop of the application.
     *
     * @return True if the main loop was started successfully, false otherwise.
     */
    bool StartMainLoop();

    const Window & GetWindow () const;

    static Application * Get();

    EventDispatcher & GetApplicationEventDispatcher ();


private:
    static bool GetProgramArgumentValue ( int argc, char ** argv, const std::string & ArgumentName, std::string & value);
    void Update();
    bool InitializeWindow();
    bool OnEvent ( Event & E );


    static Application * s_Instance;
    std::unique_ptr <Window> m_Window = nullptr;
    bool m_IsInitialized = false;
    bool m_Running = false;

    EventDispatcher m_ApplicationEventDispatcher;
};
    // To be defined in client
    Application * CreateApplication();
} // end namespace lk