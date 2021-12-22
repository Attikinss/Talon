#include "Entity.h"

#include "Scene/Scene.h"

namespace Talon
{
	Entity::Entity(Scene* scene, entt::entity handle)
		: m_Scene(scene), m_EntityHandle(handle)
	{
		AddComponent<Transform>();
	}

	void Entity::Destroy()
	{
		m_Scene->DestroyEntity(*this);
	}
}