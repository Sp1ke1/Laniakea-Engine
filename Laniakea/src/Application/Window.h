#pragma once

#include "Core.h"
#include "Events/Event.h"
#include <functional>

namespace lk {
    using EventCallbackFn = std::function<void ( Event & )>;
    struct WindowProperties
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        bool VSync;
        EventCallbackFn EventCallback;

        WindowProperties ( const std::string & title = "Laniakea", uint32_t width = 1280, uint32_t height = 720, bool VSync = false )
        : Title ( title ), Width ( width ), Height ( height ), VSync ( VSync )
        {};

        WindowProperties ( const std::string & title, uint32_t width, uint32_t height, bool VSync, EventCallbackFn & eventCallback )
                : Title ( title ), Width ( width ), Height ( height ), VSync ( VSync ), EventCallback( eventCallback )
        {};
    };
    class LANIAKEA_API Window {

    public:
        Window ( const WindowProperties & Properties );

        virtual ~Window ();

        void Update();

        inline uint32_t GetWidth() const;

        inline uint32_t GetHeight() const;

        void SetEventCallback ( const EventCallbackFn & callback );

        void SetVSync ( bool enabled );

        bool IsVSync () const;

    private:
        void Init( const WindowProperties & Properties );
        void Shutdown();

    private:
        GLFWwindow * m_Window;
        WindowProperties m_WindowData;
        static unsigned int s_WindowCount;
    };

} // end namespace lk

