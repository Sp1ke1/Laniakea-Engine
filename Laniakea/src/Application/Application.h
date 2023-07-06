#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "ApplicationConfig.h"



namespace lk {
class LANIAKEA_API Application {
public:

    ~Application();

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

    /**
     * @brief Exits the application.
     */
    void Exit();


private:
    static bool GetProgramArgumentValue ( int argc, char ** argv, const std::string & ArgumentName, std::string & value);
    void Update();
    bool InitializeInput();
    bool InitializeWindow();
    void OnEvent ( Event & E );


    std::unique_ptr <Window> m_Window = nullptr;
    Input * m_InputHandler = nullptr;
    bool m_IsInitialized = false;
    bool m_Running = false;
};

    // To be defined in client
    Application * CreateApplication();
} // end namespace lk