#include "EntityRegistry.h"
#include "Entity.h"

namespace Talon
{
	EntityRegistry::EntityRegistry()
	{
		
	}

	EntityRegistry::~EntityRegistry()
	{
		m_Registry.clear();
	}

	entt::entity EntityRegistry::CreateEntity()
	{
		return m_Registry.create();
	}

	void EntityRegistry::DestroyEntity(entt::entity entityHandle)
	{
		m_Registry.destroy(entityHandle);
	}
}