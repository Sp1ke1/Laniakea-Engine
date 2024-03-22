#include "Laniakea/ECS/System.h"

void System::AddEntity ( Entity & entity )
{
	const auto Handle = m_Entities . AddObject (entity . GetHandle () );
	m_EntitiesHandles[ entity . GetHandle () ] = Handle;
}


void System::RemoveEntity ( Entity & entity )
{
	m_Entities . RemoveObject ( m_EntitiesHandles . at (entity . GetHandle () ) );
	m_EntitiesHandles . erase (entity . GetHandle () );
}


void System::OnEntitySignatureChanged ( Entity & entity, const Signature & signature )
{
	const bool Match = std::includes ( signature . begin (), signature . end (), m_Signature . begin (),
									   m_Signature . end () );
	if ( Match )
	{
		AddEntityChecked (entity );
	}
	else
	{
		RemoveEntityChecked (entity );
	}
}

bool System::AddEntityChecked ( Entity & entity )
{
	if (m_EntitiesHandles . count (entity . GetHandle () ) != 0 )
		return false;
	AddEntity (entity );
	return true;
}

bool System::RemoveEntityChecked ( Entity & entity )
{
	if (m_EntitiesHandles . count (entity . GetHandle () ) == 0 )
		return false;
	RemoveEntity (entity );
	return true;
}

void System::SetSignature ( Signature && signature )
{
	m_Signature = std::move ( signature );
}

void System::SetSignature ( const Signature & signature )
{
	m_Signature = signature;
}

