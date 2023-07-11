#pragma once

#include "Core.h"
#include "Application.h"

#include "KeyCodes.h"
#include "MouseCodes.h"

#include "glm/include/glm.hpp"
#include "glfw/include/glfw3.h"


namespace lk {
enum class KeyState {
    Pressed,
    Released,
    Hold
};

class LANIAKEA_API Input {

public:
    static bool GetIsKeyPressed ( const KeyCode keycode );

    static bool GetIsMouseButtonPressed ( const MouseCode mouseCode );

    static glm::vec2 GetMouseLocation ();

    static float GetMouseX();

    static float GetMouseY();

    static bool Initialize();

    static const EventDispatcher & GetInputEventDispatcher ();

private:

    static bool OnEvent ( Event & e );


    static EventDispatcher m_InputEventDispatcher;
};
} // end namespace lk

