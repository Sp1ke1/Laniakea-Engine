#include "Laniakea/ECS/ECS.h"

EntityHandle ECS::CreateEntity ()
{
	return m_EntityManager . CreateEntity ();
}

void ECS::RemoveEntity ( EntityHandle entityHandle )
{
	Entity & e = m_EntityManager . GetEntity ( entityHandle );
	m_ComponentManager . OnEntityRemoved ( e );
	m_SystemManager . OnEntityRemoved ( e );
	m_EntityManager . RemoveEntity ( entityHandle );
}

Entity & ECS::GetEntity ( EntityHandle entityHandle )
{
	return m_EntityManager . GetEntity ( entityHandle );
}

bool ECS::GetIsValidEntityHandle ( EntityHandle entityHandle ) const
{
	return m_EntityManager . GetIsValidEntityHandle ( entityHandle );

}

std::optional <std::reference_wrapper <Entity>> ECS::GetEntityChecked ( EntityHandle entityHandle )
{
	return m_EntityManager . GetEntityChecked ( entityHandle );
}

bool ECS::RemoveEntityChecked ( EntityHandle entityHandle )
{
	if ( ! GetIsValidEntityHandle ( entityHandle ) )
		return false;
	RemoveEntity ( entityHandle );
	return true;
}