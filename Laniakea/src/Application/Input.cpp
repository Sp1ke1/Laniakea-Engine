//
// Created by NB01 on 6/6/2023.
//

#include "Input.h"
namespace lk {
    std::map<int, KeyState> m_KeyboardButtons;
bool Input::GetIsKeyDown(int Key) const {
    return false;
}

Input::Input(GLFWwindow *Window) {
    SetupInputCallbacks(Window);
}


void Input::SetIsKeyDown(int Key, bool IsDown) {

}


void Input::KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    KeyState state;
    if (action == GLFW_PRESS)
        state = KeyState::Pressed;
    else if (action == GLFW_RELEASE)
        state = KeyState::Released;
    else if (action == GLFW_REPEAT)
        state = KeyState::Hold;
    else {
        Logger::Get() -> Log ( { "Input", LogMessageType::Warning, "Input::KeyboardCallback() Unknown action type" } );
        return;
    }

    // m_KeyboardButtons [ key ] = state;
}

void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

}

void Input::SetupInputCallbacks(GLFWwindow *Window) {
    glfwSetKeyCallback(Window, Input::KeyboardCallback);
    glfwSetMouseButtonCallback(Window, Input::MouseButtonCallback);
}
} // end namespace lk