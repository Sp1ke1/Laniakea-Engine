#pragma once
#include "Event.h"
#include "MouseCodes.h"

// from https://github.com/TheCherno/Hazel

namespace lk {

    class LANIAKEA_CORE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y)
                : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            return std::string ( "MouseMovedEvent: ") + std::to_string ( m_MouseX ) + ", " + std::to_string ( m_MouseY );
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
    private:
        float m_MouseX, m_MouseY;
    };

    class LANIAKEA_CORE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
                : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            return std::string ( "MouseScrolledEvent: ") + std::to_string ( m_XOffset ) + ", " + std::to_string ( m_YOffset );
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
    private:
        float m_XOffset, m_YOffset;
    };

    class LANIAKEA_CORE_API MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput | EventCategory::EventCategoryMouseButton)
    protected:
        MouseButtonEvent(const MouseCode button)
                : m_Button(button) {}

        MouseCode m_Button;
    };

    class LANIAKEA_CORE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const MouseCode button)
                : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            return std::string ("MouseButtonPressedEvent: ") + std::to_string ( m_Button );
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class LANIAKEA_CORE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
                : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            return std::string ("MouseButtonReleasedEvent: ") + std::to_string ( m_Button );
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

} // end namespace lk