#include "Laniakea/ECS/EntityManager.h"

EntityHandle EntityManager::CreateEntity ()
{
	Entity e ( m_Entities . GetNextHandle () );
	return m_Entities . AddObject ( e );
}

void EntityManager::RemoveEntity ( EntityHandle entityHandle )
{
	m_Entities . RemoveObject ( entityHandle );
}

Entity & EntityManager::GetEntity ( EntityHandle entityHandle )
{
	return m_Entities . GetObject ( entityHandle );
}

void EntityManager::RemoveAllEntities ()
{
	m_Entities . Clear ();
}

bool EntityManager::GetIsValidEntityHandle ( EntityHandle entityHandle ) const
{
	return m_Entities . GetIsValidHandle ( entityHandle );
}

std::optional <std::reference_wrapper <Entity>> EntityManager::GetEntityChecked ( EntityHandle entityHandle )
{
	return m_Entities . GetObjectChecked ( entityHandle );
}

bool EntityManager::RemoveEntityChecked ( EntityHandle entityHandle )
{
	return m_Entities . RemoveObjectChecked ( entityHandle );
}