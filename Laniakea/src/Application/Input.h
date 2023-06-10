#pragma once

#include <map>
#include <vector>
#include "glfw/include/glfw3.h"
#include "Core.h"

// TODO: Consider making event based input
// TODO: http://www.grandmaster.nu/blog/?page_id=191
// TODO: https://stackoverflow.com/questions/55573238/how-do-i-do-a-proper-input-class-in-glfw-for-a-game-engine

namespace lk {
enum class KeyState {
    Pressed,
    Released,
    Hold
};

class LANIAKEA_API Input {

public:
    Input(GLFWwindow *window);

    ~Input() = default;

    bool GetIsKeyDown(int Key) const;

private:
    void SetIsKeyDown(int Key, bool IsDown);

    void SetupInputCallbacks(GLFWwindow *window);

    static void KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);


   /* std::map<int, KeyState> m_KeyboardButtons;
    std::map<int, KeyState> m_MouseButtons;*/

};
} // end namespace lk

