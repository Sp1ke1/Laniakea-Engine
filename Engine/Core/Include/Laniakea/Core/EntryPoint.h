#ifdef LANIAKEA_PLATFORM_WINDOWS

using namespace lk;

extern Application * lk::CreateApplication();

int main ( int argc, char ** argv )
{
    auto *app = CreateApplication();
	if ( ! app )
	{
		LK_LOG ( "core", lk::LogMessageType::Error, "Can't initialize application" );
		return EXIT_FAILURE;
	}

    if (!app->Initialize(argc, argv)) {

        lk::Logger::Get()->Log({"core", lk::LogMessageType::Error, "Can't initialize application"});
        delete app;
        return EXIT_FAILURE;
    }
    if ( !app -> StartMainLoop() )
    {
        LK_LOG ( "core", lk::LogMessageType::Error, "main() . Can't start application main loop");
        delete app;
        return EXIT_FAILURE;
    }
    delete app;
    return EXIT_SUCCESS;
}

#else
    #error Laniakea only supports windows
#endif