#include "Input.h"

namespace lk {

    EventDispatcher Input::m_InputEventDispatcher = {};

bool Input::GetIsKeyPressed(const KeyCode keycode)
{
    auto Window = Application::Get() -> GetWindow() . GetGLFWWindow();
    LK_ASSERT ( Window );
    auto State = glfwGetKey( Window, static_cast <int32_t> ( keycode ) );
    return State == GLFW_PRESS;
}

bool Input::GetIsMouseButtonPressed(const MouseCode mouseCode)
{
    auto Window = Application::Get() -> GetWindow() . GetGLFWWindow();
    LK_ASSERT( Window );
    auto State = glfwGetMouseButton ( Window, static_cast <int32_t> ( mouseCode  ) );
    return State == GLFW_PRESS;
}

glm::vec2 Input::GetMouseLocation()
{
    auto Window = Application::Get() -> GetWindow() . GetGLFWWindow();
    LK_ASSERT ( Window );
    double xpos, ypos;
    glfwGetCursorPos( Window, &xpos, &ypos );
    return { xpos, ypos };
}

float Input::GetMouseX()
{
    return GetMouseLocation().x;
}

float Input::GetMouseY()
{
    return GetMouseLocation().y;
}

    bool Input::Initialize() {
        auto app = Application::Get();
        LK_ASSERT ( app );
        if ( !app )
            return false;

        app -> GetApplicationEventDispatcher().Bind ( &Input::OnEvent );
        return true;
    }

    const EventDispatcher & Input::GetInputEventDispatcher() {
        return m_InputEventDispatcher;
    }

    bool Input::OnEvent(Event &e) {
        if ( !e.GetCategoryFlags() && EventCategory::EventCategoryInput )
            return false;
        std::cout << e;
    }
} // end namespace lk