#include "ComponentBase.h"

ComponentBase::ComponentBase ( EntityHandle owner )
: m_Owner ( owner ) {

}

EntityHandle ComponentBase::GetOwner () const
{
	return m_Owner;
}