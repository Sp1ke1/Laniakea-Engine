#include <vector>
#include "Core.h"

namespace lk
{
namespace gfx
{

class  Uniform
{
	public:
		Uniform() 								 = delete;
		Uniform ( const Uniform & ) 			 = delete;
		Uniform & operator = ( const Uniform & ) = delete;
		~Uniform() 								 = delete;

		template <typename T>
		static void Set ( unsigned int Slot, const T & value );

		template <typename T>
		static void Set ( unsigned int Slot, T * Array, unsigned int Length );

		template <typename T>
		static void Set ( unsigned int Slot, std::vector<T> & Array );
};

}
}