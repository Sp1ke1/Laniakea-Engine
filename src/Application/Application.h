#pragma once

#include "Logger.h"
#include "glfw3.h"
#include "ApplicationConfig.h"
#include "InputHandler.h"



namespace lk {
class Application {
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


    GLFWwindow * m_MainWindow = nullptr;
    bool m_IsInitialized = false;
    InputHandler * m_InputHandler = nullptr;


};
} // end namespace lk