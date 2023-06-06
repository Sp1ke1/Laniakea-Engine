//
// Created by NB01 on 6/6/2023.
//

#include "InputHandler.h"
namespace lk {
bool InputHandler::GetIsKeyDown(int Key) const {
    return false;
}

InputHandler::InputHandler(GLFWwindow *Window) {
    SetupInputCallbacks(Window);
}


void InputHandler::SetIsKeyDown(int Key, bool IsDown) {

}


void InputHandler::KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    KeyState state;
    if (action == GLFW_PRESS)
        state = KeyState::Pressed;
    else if (action == GLFW_RELEASE)
        state = KeyState::Released;
    else if (action == GLFW_REPEAT)
        state = KeyState::Hold;
    else {
        Logger::Get() -> Log ( { "Input", LogMessageType::Warning, "InputHandler::KeyboardCallback() Unknown action type" } );
        return;
    }

    m_KeyboardButtons [ key ] = state;
}

void InputHandler::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

}

void InputHandler::SetupInputCallbacks(GLFWwindow *Window) {
    glfwSetKeyCallback(Window, InputHandler::KeyboardCallback);
    glfwSetMouseButtonCallback(Window, InputHandler::MouseButtonCallback);
}
} // end namespace lk