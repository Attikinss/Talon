#include "EntityRegistry.h"

namespace Talon
{
	EntityRegistry::EntityRegistry()
	{
		
	}

	EntityRegistry::~EntityRegistry()
	{

	}

	entt::entity EntityRegistry::CreateEntity()
	{
		return m_Registry.create();
	}

	void EntityRegistry::DestroyEntity(entt::entity entityHandle)
	{
		m_Registry.remove_all(entityHandle);
		m_Registry.destroy(entityHandle);
	}
}