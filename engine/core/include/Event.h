#pragma once
#include "Core.h"
#include <string>



// from https://github.com/TheCherno/Hazel
namespace lk {

    // events in Hazel are currently blocking, meaning when an event occurs it
    // immediately gets dispatched and must be dealt with right then an there.
    // For the future, a better strategy might be to buffer events in an event
    // bus and process them during the "event" part of the update stage.

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

	inline EventCategory operator | ( EventCategory a, EventCategory b )
	{
		return static_cast<EventCategory> ( static_cast<int> ( a ) | static_cast <int> ( b ) );
	}

	inline EventCategory operator & ( EventCategory a, EventCategory b )
	{
		return static_cast<EventCategory> ( static_cast<int> ( a ) & static_cast <int> ( b ) );
	}

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategoryFlags() const override { return category; }

    class LANIAKEA_API Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        constexpr virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual EventCategory GetCategoryFlags() const = 0;
        virtual std::string ToString() const;

        bool IsInCategory(EventCategory category);
    };
} // end namespace lk