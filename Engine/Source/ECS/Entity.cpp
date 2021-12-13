#include "Entity.h"

namespace Talon
{
	Entity::Entity(EntityRegistry* registry, entt::entity handle)
		: m_Registry(registry), m_EntityHandle(handle)
	{
		AddComponent<Transform>();
	}

	void Entity::Destroy()
	{
		m_Registry->DestroyEntity(m_EntityHandle);
	}
}