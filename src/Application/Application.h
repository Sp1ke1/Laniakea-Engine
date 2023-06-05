#pragma once

#include "Logger.h"
#include "ApplicationConfig.h"

#define DEFAULT_CONFIG_PATH "config/ApplicationConfig.json" // TODO: move to argc argv
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
    bool Init(int argc, char **argv);

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


    void Update();

    static bool GetProgramArgumentValue ( int argc, char ** argv, const std::string & ArgumentName, std::string & value);

private:


};
} // end namespace lk