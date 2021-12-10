#include "Entity.h"

#include "Transform.h"

namespace Talon
{
	Entity::Entity(EntityRegistry* registry)
		: m_Registry(registry), m_EntityHandle(registry->CreateEntity())
	{
		AddComponent<Transform>();
	}

	Entity::~Entity()
	{

	}
}