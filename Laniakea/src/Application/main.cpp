/*
#include "glfw3.h"
#include "Application.h"
#include "Logger.h"


int main(int argc, char ** argv)
{

    lk::Application * app = new lk::Application();

    if ( !app -> Initialize ( argc, argv ) )
    {
        lk::Logger::Get() -> Log ( {"Application", lk::LogMessageType::Error, "Can't initialize application"} );
        delete app;
        return EXIT_FAILURE;
    }

    if ( !app -> StartMainLoop() )
    {
        lk::Logger::Get() -> Log ( {"Application", lk::LogMessageType::Error, "Can't start main loop of the application" } );
        delete app;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

*/



/*


    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();*/

}