#include "EntityRegistry.h"

namespace Talon
{
	EntityRegistry::EntityRegistry()
	{
		entt::entity entity = m_Registry.create();
	}

	EntityRegistry::~EntityRegistry()
	{

	}

	entt::entity EntityRegistry::CreateEntity()
	{
		return m_Registry.create();
	}
}