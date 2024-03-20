#include "ComponentManager.h"

bool ComponentManager::GetIsComponentRegistered ( ComponentType componentType ) const
{
	return m_Components . count ( componentType ) != 0;
}

void ComponentManager::OnEntityRemoved ( Entity & entity )
{
	const auto & ComponentInfo = entity . GetComponentsInfo ();
	for ( const auto & info : ComponentInfo ) {
		m_Components . at ( info . Type ) -> RemoveObjectChecked ( info . Handle );
	}
}