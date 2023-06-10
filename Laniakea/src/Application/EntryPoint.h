#pragma once

#ifdef LANIAKEA_PLATFORM_WINDOWS

extern lk::Application * lk::CreateApplication();

int main ( int argc, char ** argv )
{
    auto *app = lk::CreateApplication();

    if (!app->Initialize(argc, argv)) {
        lk::Logger::Get()->Log({"Application", lk::LogMessageType::Error, "Can't initialize application"});
        delete app;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#else
    #error Laniakea only supports windows
#endif

