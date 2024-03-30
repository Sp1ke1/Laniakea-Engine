#include "Laniakea/AssetManager/AssetManagerException.h"

namespace lk
{
	namespace am

	{

		AssetManagerException::AssetManagerException ( std::string && msg )
				: m_Msg ( std::move ( msg ) )
		{

		}

		AssetManagerException::AssetManagerException ( const std::string & msg )
				: m_Msg( msg )
		{
		}

		const char * AssetManagerException::what () const noexcept
		{
			return m_Msg.c_str();
		}

	} // lk
} // gfx