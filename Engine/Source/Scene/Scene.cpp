#include "Scene.h"
#include "ECS/Entity.h"

namespace Talon
{
	Scene::Scene(const std::string& name)
		: m_Name(name)
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Update()
	{
		m_Registry.Update();
	}

	void Scene::OnEvent(Event& evt)
	{

	}

	Entity Scene::CreateEntity()
	{
		return Entity(this, m_Registry.CreateEntity());
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.DestroyEntity(entity.m_EntityHandle);
	}
}