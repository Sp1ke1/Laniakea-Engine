#pragma once

#include "Core.h"
#include "GLFW/glfw3.h"
#include "Event.h"
#include "EventDispatcher.h"


namespace lk {
    using EventCallbackFn = std::function<void ( Event & )>;
    struct WindowProperties
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        bool VSync;
        EventDispatcher WindowEventDispatcher;

        WindowProperties ( const std::string & title = "libs", uint32_t width = 1280, uint32_t height = 720, bool VSync = false )
        : Title ( title ), Width ( width ), Height ( height ), VSync ( VSync )
        {};

      /*  WindowProperties ( const std::string & title, uint32_t width, uint32_t height, bool VSync, EventCallbackFn & eventCallback )
                : Title ( title ), Width ( width ), Height ( height ), VSync ( VSync ), EventCallback( eventCallback ) // TODO: delete
        {};*/
    };
    class LANIAKEA_CORE_API Window {

    public:
        Window ( const WindowProperties & Properties );

        virtual ~Window ();

        void Update();

        inline uint32_t GetWidth() const;

        inline uint32_t GetHeight() const;

/*
        void SetEventCallback ( const EventCallbackFn & callback );
*/ // TODO delete

        void SetVSync ( bool enabled );

        bool IsVSync () const;

        GLFWwindow * GetGLFWWindow () const;

        EventDispatcher & GetWindowEventDispatcher ();

    private:
        void Init( const WindowProperties & Properties );
        void Shutdown();

    private:
        GLFWwindow * m_Window;
        WindowProperties m_WindowData;
        static unsigned int s_WindowCount;
    };

} // end namespace lk

