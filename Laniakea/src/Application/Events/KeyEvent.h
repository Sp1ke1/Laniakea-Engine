#pragma once
#include "Event.h"
#include "Application/KeyCodes.h"

// from https://github.com/TheCherno/Hazel
namespace lk
{
    class LANIAKEA_API KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(const KeyCode keycode)
                : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class LANIAKEA_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
                : KeyEvent(keycode), m_IsRepeat(isRepeat) {}

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            return std::string ( "KeyPressedEvent " ) + std::to_string ( m_KeyCode );
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_IsRepeat;
    };

    class LANIAKEA_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode keycode)
                : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            return std::string ( "KeyReleasedEvent " ) + std::to_string ( m_KeyCode );
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class LANIAKEA_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const KeyCode keycode)
                : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            return std::string ( "KeyTypedEvent " ) + std::to_string ( m_KeyCode );
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
} // end namespace lk
