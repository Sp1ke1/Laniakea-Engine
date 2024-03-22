#include <vector>
#include "Core.h"

namespace lk
{
namespace gfx
{

class  IndexBuffer
{
public:
	IndexBuffer ();
	~IndexBuffer ();
	IndexBuffer ( const IndexBuffer & ) = delete;
	IndexBuffer & operator = ( const IndexBuffer & ) = delete;

	void Set ( unsigned int * Array, unsigned int Length );
	void Set (  std::vector <unsigned int> & Array );

	unsigned int GetCount () const;
	unsigned int GetHandle () const;

private:
	unsigned int m_Handle;
	unsigned int m_Count;
};

} // lk
} // gfx
