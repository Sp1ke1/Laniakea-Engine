#include "Laniakea/ECS/Entity.h"


Entity::Entity ( EntityHandle id )
: m_Handle ( id )
{

};

EntityHandle Entity::GetHandle () const
{
	return m_Handle;
}

void Entity::AddComponent ( ComponentInfo componentInfo )
{
	m_Components.insert(componentInfo);
}

void Entity::RemoveComponent ( ComponentType type )
{
	m_Components.erase({type, NULL_HANDLE});
}

bool Entity::GetHasComponent ( ComponentType type ) const
{
	return m_Components.count({type, NULL_HANDLE}) != 0;
}

ComponentHandle Entity::GetComponentHandle ( ComponentType type ) const
{
	return m_Components.find({type, NULL_HANDLE})->Handle;
}

const std::set <ComponentInfo> & Entity::GetComponentsInfo () const
{
	return m_Components;
}

Signature Entity::GetSignature () const
{
	Signature out;
	for (const auto &elem: m_Components) {
		out.insert(elem.Type);
	}
	return out;
}

std::optional <ComponentHandle> Entity::GetComponentHandleChecked ( ComponentType type ) const
{
	if (!GetHasComponent(type))
		return std::nullopt;
	return GetComponentHandle(type);
}