#include "Laniakea/AssetManager/Core.h"
#include <exception>
#include <string>

namespace lk {
namespace am {


class LANIAKEA_ASSET_MANAGER_API AssetManagerException : public std::exception
{
public:
	AssetManagerException ( const std::string & msg );

	AssetManagerException ( std::string && msg );

	const char * what() const noexcept override;
private:
	std::string m_Msg;
};

}
}



