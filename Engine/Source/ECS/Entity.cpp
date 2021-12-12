#include "Entity.h"

namespace Talon
{
	Entity::Entity(EntityRegistry* registry, entt::entity handle)
		: m_Registry(registry), m_EntityHandle(handle)
	{
		AddComponent<Transform>();
	}

	Entity::~Entity()
	{
		m_Registry->DestroyEntity(m_EntityHandle);
	}
}