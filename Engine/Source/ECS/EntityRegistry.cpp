#include "EntityRegistry.h"
#include "Entity.h"

namespace Talon
{
	EntityRegistry::EntityRegistry()
	{
		
	}

	EntityRegistry::~EntityRegistry()
	{

	}

	Entity EntityRegistry::CreateEntity()
	{
		return Entity(this, m_Registry.create());
	}

	void EntityRegistry::DestroyEntity(entt::entity entityHandle)
	{
		m_Registry.destroy(entityHandle);
	}
}