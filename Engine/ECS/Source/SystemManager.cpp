#include "Laniakea/ECS/SystemManager.h"

std::weak_ptr <System> SystemManager::GetSystem ( SystemType systemType )
{
	return m_Systems . count ( systemType ) == 0 ? nullptr : m_Systems . at ( systemType );
}

bool SystemManager::GetIsSystemRegistered ( SystemType systemType ) const
{
	return m_Systems . count ( systemType ) != 0;
}

void SystemManager::OnEntitySignatureChanged ( Entity & entity, const Signature & signature )
{
	for ( auto & System : m_Systems ) {
		System . second -> OnEntitySignatureChanged ( entity, signature );
	}
}

void SystemManager::OnEntityRemoved ( Entity & entity )
{
	for ( auto & System : m_Systems ) {
		System . second -> RemoveEntityChecked ( entity );
	}
}