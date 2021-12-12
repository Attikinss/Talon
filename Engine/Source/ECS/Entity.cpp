#include "Entity.h"

namespace Talon
{
	Entity::Entity(EntityRegistry* registry)
		: m_Registry(registry), m_EntityHandle(registry->CreateEntity())
	{
		Transform& transform = AddComponent<Transform>();
		transform.m_Entity = this;
	}

	Entity::~Entity()
	{
		m_Registry->DestroyEntity(m_EntityHandle);
	}
}